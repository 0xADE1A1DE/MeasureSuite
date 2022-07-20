#ifndef TIMER_H
#define TIMER_H

#include <linux/perf_event.h> // PERF_*
#include <stdint.h>
#include <sys/ioctl.h>   //ioctl
#include <sys/mman.h>    //mmap
#include <sys/syscall.h> // __NR_perf_event_open
#include <unistd.h>      // syscall, sysconf, _SC_PAGESIZE

void ms_start_timer(uint64_t *start);
void ms_init_timer();
uint64_t ms_stop_timer(uint64_t start);
uint64_t ms_current_timestamp();

#endif
