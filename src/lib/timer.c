/**
 * Copyright 2022 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "timer.h"
#include <linux/perf_event.h> // PERF_*
#include <stdio.h>            // NULL
#include <sys/ioctl.h>        // ioctl
#include <sys/mman.h>         // mmap
#include <sys/syscall.h>      // __NR_perf_event_open
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h> // syscall, sysconf, _SC_PAGESIZE

static void init_fdperf(struct measuresuite *ms) {
  struct perf_event_attr attr = {
      .type = PERF_TYPE_HARDWARE,
      .config = PERF_COUNT_HW_CPU_CYCLES,
      .exclude_kernel = 1,
  };

  ms->timer.fdperf = (int)syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
  if (ms->timer.fdperf == -1) {
    return;
  }
  ms->timer.buf = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ, MAP_SHARED,
                       ms->timer.fdperf, 0);
  // NOLINTNEXTLINE (mmap - api)
  if (ms->timer.buf == MAP_FAILED) {
    ms->timer.fdperf = -1;
  }
}

static uint64_t measuresuite_time_pmc(struct measuresuite *ms) {
  // eax: low 32
  // edx: high 32
#if defined(__x86_64__) || defined(__amd64__)
  long long result = 0;
  unsigned int seq = 0;
  long long offset = 0;

  do {
    seq = ms->timer.buf->lock;
    // barrier for cc
    asm volatile("" ::: "memory");
    offset = ms->timer.buf->offset;
    // barrier for cpu
    asm volatile("lfence;\n\t"
                 "cpuid;\n\t" ::
                     : "rax", "rbx", "rcx", "rdx");
    asm volatile("rdpmc;shlq $32,%%rdx;orq %%rdx,%%rax"
                 : "=a"(result)
                 : "c"(ms->timer.buf->index - 1)
                 : "%rdx");

    // barrier for cpu
    asm volatile("lfence;\n\t"
                 "cpuid;\n\t" ::
                     : "rax", "rbx", "rcx", "rdx");

    // barrier for cc
    asm volatile("" ::: "memory");
  } while (ms->timer.buf->lock != seq);

  return result + offset;

  // ARM on Darwin does not support mrc p15.
  // clang complains with:
  // unrecognized instruction mnemonic, did you mean: mrs, msr, smc
  // TODO: have a look here:
  // https://lemire.me/blog/2021/03/24/counting-cycles-and-instructions-on-the-apple-m1-processor/
  // https://github.com/lemire/Code-used-on-Daniel-Lemire-s-blog/blob/master/2021/03/24/benchmark.cpp
  // or here
  // https://github.com/google/benchmark/blob/v1.1.0/src/cycleclock.h#L116
#elif (__linux__ &&                                                            \
       __ARM_ARCH >=                                                           \
           6) // V6 is the earliest arch that has a standard cyclecount
  uint32_t pmccntr = 0;
  uint32_t pmuseren = 0;
  uint32_t pmcntenset = 0;
  // Read the user mode perf monitor counter access permissions. (__ARM_ARCH >=
  // 6)
  asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
  if (pmuseren & 1) { // Allows reading perfmon counters for user mode code.
    asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
    if (pmcntenset & 0x80000000ul) { // Is it counting?
      asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
      // The counter is set up to count every 64th cycle
      return (uint64_t)(pmccntr)*64; // Should optimize to << 6
    }
  }
#else
  // fallback
  return ms_current_timestamp();
#endif
}

uint64_t current_timestamp() {
  struct timeval time = {0};
  gettimeofday(&time, NULL); // get current time

  const long long millisonds_per_second = 1000LL;
  const long long microseconds_per_millisecond = 1000LL;
  uint64_t milliseconds =
      time.tv_sec * millisonds_per_second +
      time.tv_usec / microseconds_per_millisecond; // calculate milliseconds

  return milliseconds;
}

// NOLINTNEXTLINE (the inlineasm is not analyzed with clang tidy)
static uint64_t measuresuite_time_rdtscp() {

  uint64_t result = 0;
  // barrier for cc
  asm volatile("" ::: "memory");
  __asm__ __volatile__("LFENCE;\n\t"
                       "RDTSCP;\n\t"
                       "shl $0x20, %%rdx; \n\t"
                       "or %%rdx, %%rax; \n\t"
                       "mov %%rax, %[time]; \n\t"
                       "CPUID; \n\t"
                       : [time] "=&m"(result)::"rax", "rbx", "rcx", "rdx");
  // barrier for cc
  asm volatile("" ::: "memory");
  return result;
}

/**
 * This function checks if we use PMC or fall back to something different
 */
int init_timer(struct measuresuite *ms) {

  // try to initialize
  init_fdperf(ms);

  if (ms->timer.fdperf == -1) {
    // if that  failed, we need to resort to RDTSCP
    ms->timer.timer_function = measuresuite_time_rdtscp;
  } else {
    // otherwise we'd use pmc
    ms->timer.timer_function = measuresuite_time_pmc;
  }

  return 0;
}

void start_timer(struct measuresuite *ms, uint64_t *start) {
  // we need to reset the PMC if we are using them.
  if (ms->timer.timer_function == measuresuite_time_pmc) {
    ioctl(ms->timer.fdperf, PERF_EVENT_IOC_RESET, 0);
  }
  *start = ms->timer.timer_function(ms);
}

uint64_t stop_timer(struct measuresuite *ms, uint64_t start) {

  uint64_t now = ms->timer.timer_function(ms);

  uint64_t delta = now - start;

  return delta;
}
