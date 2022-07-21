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
