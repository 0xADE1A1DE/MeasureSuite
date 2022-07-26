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

#include <stdint.h>
/**
 * prints the given number in binary to stdout
 */
void printbin_single_number(uint64_t);

/**
 * prints two numbers if they are the same in green and red if they are
 * diffeerent
 */
void printbin(uint64_t const *a, uint64_t const *b, int len, int l);
/**
 * same but in hex
 */
void printhex(uint64_t const *a, uint64_t const *b, int len, int l);
