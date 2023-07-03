/**
 * Copyright 2023 University of Adelaide
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
#include "assert.h"
#include "debug.h"
#include "measuresuite.h"
#include <linux/perf_event.h> // PERF_*
#include <stdio.h>            // NULL
#include <string.h>           // memset
#include <sys/ioctl.h>        // ioctl
#include <sys/mman.h>         // mmap
#include <sys/syscall.h>      // SYS_perf_event_open
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

static int get_fdperf(volatile struct perf_event_attr *attr) {

  const pid_t pid = 0;
  const int cpu = -1;
  const int group_fd = -1;
  const unsigned long flags = 0;
  /**
   * To use this we'd need to #define _GNU_SOURCE, which I don't know the
   * sideffects of:
   * return (int)syscall(SYS_perf_event_open, attr, pid, cpu, group_fd, flags);
   */

  long long ret = -1;

  /** https://man7.org/linux/man-pages/man2/syscall.2.html */
  __asm volatile("mov %[groupfd], %%r10\n\t"
                 "mov %[flags], %%r8\n\t"
                 "syscall\n\t"
                 : "=a"(ret)
                 : "a"(SYS_perf_event_open), "D"(attr), "S"(pid),
                   "d"(cpu), [groupfd] "rmi"(group_fd), [flags] "rmi"(flags)
                 : "memory", "r8", "r10", "r11", "rcx", "cc");
  return (int)ret;
}

static void init_fdperf(volatile struct measuresuite *ms) {
  struct perf_event_attr attr = {
      .type = PERF_TYPE_HARDWARE,
      .config = PERF_COUNT_HW_CPU_CYCLES,
      .exclude_kernel = 1,
      .size = sizeof(struct perf_event_attr),
      .exclude_hv = 1,
  };

  ms->timer.fdperf = get_fdperf(&attr);
  DEBUG("fdperf for the PERF Event page: %d.\n", ms->timer.fdperf);

  if (ms->timer.fdperf == -1) {
    return;
  }
  ms->timer.buf = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ, MAP_SHARED,
                       ms->timer.fdperf, 0);
  // NOLINTNEXTLINE (mmap - api)
  if (ms->timer.buf == MAP_FAILED) {
    ms->timer.fdperf = -1;
    perror("mmap (for performance counter) failed");
  }
}

static uint64_t measuresuite_time_pmc(struct measuresuite *ms) {
#if defined(__x86_64__) || defined(__amd64__)
  long long result = 0;
  unsigned int seq = 0;
  long long offset = 0;
  long long index = 0;
  struct perf_event_mmap_page *buf = ms->timer.buf;

  do {
    seq = buf->lock;
    // barrier for cc
    __asm volatile("" ::: "memory");
    offset = buf->offset;
    index = buf->index;
    if (buf->cap_user_rdpmc && index) {
      DEBUG("The index is %lld, offset: %lld, result %lld\n", index, offset,
            result);

      __asm__ volatile("lfence\n\t"
                       "cpuid\n\t"
                       "mov %q0,%%rcx\n\t"
                       "dec %%rcx\n\t"
                       "rdpmc\n\t"
                       "shlq $32,%%rdx\n\t"
                       "orq %%rdx,%%rax\n\t"
                       "mov %%rax, %q1\n\t"
                       "lfence\n\t"
                       "cpuid\n\t"
                       : "=&m"(index), "=&m"(result)
                       :
                       : "rax", "rbx", "rcx", "rdx", "memory", "cc");
    }
  } while (buf->lock != seq);

  DEBUG("The index is %lld, offset: %lld, result %lld\n", index, offset,
        result);
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
  __asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
  if (pmuseren & 1) { // Allows reading perfmon counters for user mode code.
    __asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
    if (pmcntenset & 0x80000000ul) { // Is it counting?
      __asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
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
  // eax: low 32
  // edx: high 32
  uint64_t result = 0;
  __asm__ __volatile__("lfence;\n\t"
                       "rdtscp;\n\t"
                       "shl $0x20, %%rdx; \n\t"
                       "or %%rdx, %%rax; \n\t"
                       "mov %%rax, %[time]; \n\t"
                       "cpuid; \n\t"
                       : [time] "=&m"(result)::"rax", "rbx", "rcx", "rdx",
                         "memory");
  return result;
}

/**
 * This function checks if we use PMC or fall back to something different
 */
int init_timer(struct measuresuite *ms) {

  // init timer struct
  memset(&ms->timer, 0, sizeof(ms->timer));

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

/**
 * This function checks if we used PMC and will then free the mmapped region
 */
int end_timer(struct measuresuite *ms) {

  if (ms_get_timer(ms) == RDTSCP) {
    return 0;
  }

  // otherwise we used pmc
  assert(ms->timer.buf != NULL); // and  the buffer shall not be NULL

  if (munmap(ms->timer.buf, sysconf(_SC_PAGESIZE)) == 0) {
    ms->timer.buf = NULL;
    ioctl(ms->timer.fdperf, PERF_EVENT_IOC_DISABLE, 0);
    close(ms->timer.fdperf);
    return 0;
  }
  perror("munmap of timer buffer (pmc) failed.");
  return 1;
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
