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

#ifdef __linux__
#include <linux/perf_event.h> // PERF_*
#endif

#include <stdio.h>       // NULL
#include <sys/ioctl.h>   // ioctl
#include <sys/mman.h>    // mmap
#include <sys/syscall.h> // __NR_perf_event_open
#include <sys/time.h>
#include <unistd.h> // syscall, sysconf, _SC_PAGESIZE

// declaration
static void measuresuite_time_pmc(uint64_t *t);

// prefer pmc
// NOLINTNEXTLINE (state)
static void (*timer_function)(uint64_t *) = measuresuite_time_pmc;

// NOLINTNEXTLINE (state)
static int fdperf = -1;

#ifdef __linux__

// NOLINTNEXTLINE (state)
static struct perf_event_mmap_page *buf = 0;

static void init() {
  struct perf_event_attr attr;
  attr.type = PERF_TYPE_HARDWARE;
  attr.config = PERF_COUNT_HW_CPU_CYCLES;
  attr.exclude_kernel = 1;
  fdperf = (int)syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
  if (fdperf == -1) {
    return;
  }
  buf = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ, MAP_SHARED, fdperf, 0);
  // NOLINTNEXTLINE (mmap - api)
  if (buf == MAP_FAILED) {
    fdperf = -1;
  }
}

#elif __APPLE__
// arm on darwin
#include "m1cycles.h"

static void init() { m1_setup_performance_counters(); }

#endif // __linux__/__APPLE__

static void measuresuite_time_pmc(uint64_t *t) {
#if __linux__
#if defined(__x86_64__) || defined(__amd64__)
  long long result = 0;
  unsigned int seq = 0;
  long long offset = 0;

  do {
    seq = buf->lock;
    // barrier for cc
    asm volatile("" ::: "memory");
    offset = buf->offset;
    // barrier for cpu
    asm volatile("lfence;\n\t"
                 "cpuid;\n\t" ::
                     : "rax", "rbx", "rcx", "rdx");
    asm volatile("rdpmc;shlq $32,%%rdx;orq %%rdx,%%rax"
                 : "=a"(result)
                 : "c"(buf->index - 1)
                 : "%rdx");

    // barrier for cpu
    asm volatile("lfence;\n\t"
                 "cpuid;\n\t" ::
                     : "rax", "rbx", "rcx", "rdx");

    // barrier for cc
    asm volatile("" ::: "memory");
  } while (buf->lock != seq);

  *t = (result + offset);

  // ARM on Darwin does not support mrc p15.
  // clang complains with:
  // unrecognized instruction mnemonic, did you mean: mrs, msr, smc
  // TODO: have a look here:
  // https://lemire.me/blog/2021/03/24/counting-cycles-and-instructions-on-the-apple-m1-processor/
  // https://github.com/lemire/Code-used-on-Daniel-Lemire-s-blog/blob/master/2021/03/24/benchmark.cpp
  // or here
  // https://github.com/google/benchmark/blob/v1.1.0/src/cycleclock.h#L116

#elif __ARM_ARCH >= 6 // V6 is the earliest arch that has a standard cyclecount
  uint32_t pmccntr;
  uint32_t pmuseren;
  uint32_t pmcntenset;
  // Read the user mode perf monitor counter access permissions. (__ARM_ARCH >=
  // 6)
  asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
  if (pmuseren & 1) { // Allows reading perfmon counters for user mode code.
    asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
    if (pmcntenset & 0x80000000ul) { // Is it counting?
      asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
      // The counter is set up to count every 64th cycle
      *t = (uint64_t)(pmccntr)*64; // Should optimize to << 6
    }
  }
#endif                // x86 or arm linux
#elif __APPLE__       // i.e. not __linux__
  *t = m1_get_cycles();
#else
  // fallback
  *t = ms_current_timestamp();
#endif
}

uint64_t ms_current_timestamp() {
  struct timeval time;
  gettimeofday(&time, NULL); // get current time

  const long long millisonds_per_second = 1000LL;
  const long long microseconds_per_millisecond = 1000LL;
  uint64_t milliseconds =
      time.tv_sec * millisonds_per_second +
      time.tv_usec / microseconds_per_millisecond; // calculate milliseconds

  return milliseconds;
}

#if __linux__
// NOLINTNEXTLINE (the inlineasm is not analyzed with clang tidy)
static void measuresuite_time_rdtscp(uint64_t *t) {
  // eax: low 32
  // edx: high 32
  // barrier for cc
  asm volatile("" ::: "memory");
  __asm__ __volatile__("LFENCE;\n\t"
                       "RDTSCP;\n\t"
                       "shl $0x20, %%rdx; \n\t"
                       "or %%rdx, %%rax; \n\t"
                       "mov %%rax, %[time]; \n\t"
                       "CPUID; \n\t"
                       : [time] "=&m"(*t)::"rax", "rbx", "rcx", "rdx");
  // barrier for cc
  asm volatile("" ::: "memory");
}
#endif

/**
 * This function checks if we use PMC or fall back to something different
 */
void ms_init_timer() {

  // try to initialize (will internally handle __APPLE__ // __linux__ arch's)
  init();

  // If we are on linx and x86, we can also fallback to RDTSCP
#if __linux__ && (defined(__x86_64__) || defined(__amd64__))
  if (fdperf == -1) {
    // if that  failed, we need to resort to RDTSCP
    timer_function = measuresuite_time_rdtscp;
  }
#endif
}

// exposed
void ms_start_timer(uint64_t *start) {
#if __linux__
  // we need to reset the PMC if we are using them on linnux
  if (timer_function == measuresuite_time_pmc) {
    ioctl(fdperf, PERF_EVENT_IOC_RESET, 0);
  }
#endif
  timer_function(start);
}

uint64_t ms_stop_timer(uint64_t start) {

  uint64_t now = 0;
  timer_function(&now);
  uint64_t delta = now - start;

  return delta;
}
