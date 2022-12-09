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

// fiat_curve25519_carry_square
#include "helper.h"
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char symbol[] = {"fiat_curve25519_carry_square"};
const char lib[] = {"./liball_fiat.so"};
const int arg_width = 5;
const int arg_num_in = 1;

// those are the bounds from the JSON file
const uint64_t bounds[] = {
    0x18000000000000 - 1, 0x18000000000000 - 1, 0x18000000000000 - 1,
    0x18000000000000 - 1, 0x18000000000000 - 1,
};
int main() {
  SIGILL_SETUP();

  char fa[] = {
      "sub rsp, 0x38 \n"
      "mov [ rsp + 0x0 ], rbx; saving to stack \n"
      "mov [ rsp + 0x8 ], rbp; saving to stack \n"
      "mov [ rsp + 0x10 ], r12; saving to stack \n"
      "mov [ rsp + 0x18 ], r13; saving to stack \n"
      "mov [ rsp + 0x20 ], r14; saving to stack \n"
      "mov [ rsp + 0x28 ], r15; saving to stack \n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx \n"
      "mulx r8, rbp, [ rsi + 0x0 ]; x38, x37<- arg1[0] * arg1[0] \n"
      "imul r14, [ rsi + 0x20 ], 0x13; x1 <- arg1[4] * 0x13 \n"
      "imul r13, r14, 0x2; x2 <- x1 * 0x2 \n"
      "mov rdx, r13; x2 to rdx \n"
      "mulx rcx, r10, [ rsi + 0x8 ]; x22, x21<- arg1[1] * x2 \n"
      "imul r15, [ rsi + 0x18 ], 0x13; x4 <- arg1[3] * 0x13 \n"
      "imul r11, r15, 0x2; x5 <- x4 * 0x2 \n"
      "xchg rdx, r11; x5, swapping with x2, which is currently in rdx \n"
      "mulx rdx, r9, [ rsi + 0x10 ]; x18, x17<- arg1[2] * x5 \n"
      "xor r12, r12 \n"
      "adox r9, r10 \n"
      "adcx r9, rbp \n"
      "adox rcx, rdx \n"
      "mov r13, 0x7ffffffffffff ; moving imm to reg \n"
      "setc al; spill CF x44 to reg (rax) \n"
      "mov rbx, r9; x48, copying x43 here, cause x43 is needed in a reg "
      "for other than x48, namely all: , x48, x47, size: 2 \n"
      "and rbx, r13; x48 <- x43& 0x7ffffffffffff \n"
      "sar  al, 1 \n"
      "adcx r8, rcx \n"
      "shrd r9, r8, 51; x47 <- x45||x43 >> 51 \n"
      "imul rbp, [ rsi + 0x8 ], 0x2; x8 <- arg1[1] * 0x2 \n"
      "mov rdx, [ rsi + 0x18 ]; arg1[3] to rdx \n"
      "mulx r15, r10, r15; x14, x13<- arg1[3] * x4 \n"
      "mov rdx, r11; x2 to rdx \n"
      "mulx r11, rax, [ rsi + 0x10 ]; x16, x15<- arg1[2] * x2 \n"
      "xchg rdx, rbp; x8, swapping with x2, which is currently in rdx \n"
      "mulx rdx, rcx, [ rsi + 0x0 ]; x36, x35<- arg1[0] * x8 \n"
      "xor r8, r8 \n"
      "adox r10, rax \n"
      "adox r11, r15 \n"
      "adcx r10, rcx \n"
      "mov r12, -0x2 ; moving imm to reg \n"
      "inc r12; OF<-0x0, preserve CF (workaround, load -2, increa it, "
      "and dont save it. I this a hack?) \n"
      "adox r10, r9 \n"
      "adcx rdx, r11 \n"
      "adox rdx, r8 \n"
      "mov r12, r10; x84, copying x81 here, cause x81 is needed in a "
      "reg for other than x84, namely all: , x84, x85, size: 2 \n"
      "shrd r12, rdx, 51; x84 <- x83||x81 >> 51 \n"
      "imul r9, [ rsi + 0x10 ], 0x2; x7 <- arg1[2] * 0x2 \n"
      "mov rdx, r9; x7 to rdx \n"
      "mulx r9, r15, [ rsi + 0x0 ]; x34, x33<- arg1[0] * x7 \n"
      "mov rax, rdx; preserving value of x7 into a new reg \n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx. \n"
      "mulx rcx, r11, [ rsi + 0x8 ]; x28, x27<- arg1[1] * arg1[1] \n"
      "mov rdx, [ rsi + 0x18 ]; arg1[3] to rdx \n"
      "mulx rbp, r8, rbp; x12, x11<- arg1[3] * x2 \n"
      "xor rdx, rdx \n"
      "adox r8, r11 \n"
      "adcx r8, r15 \n"
      "adox rcx, rbp \n"
      "adcx r9, rcx \n"
      "xor r15, r15 \n"
      "adox r8, r12 \n"
      "adox r9, r15 \n"
      "mov rdx, r8; x89, copying x86 here, cause x86 is needed in a reg "
      "for other than x89, namely all: , x90, x89, size: 2 \n"
      "shrd rdx, r9, 51; x89 <- x88||x86 >> 51 \n"
      "imul r12, [ rsi + 0x18 ], 0x2; x6 <- arg1[3] * 0x2 \n"
      "mov r11, rdx; preserving value of x89 into a new reg \n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx. \n"
      "mulx rax, rbp, rax; x26, x25<- arg1[1] * x7 \n"
      "mov rdx, r12; x6 to rdx \n"
      "mulx r12, rcx, [ rsi + 0x0 ]; x32, x31<- arg1[0] * x6 \n"
      "mov r9, rdx; preserving value of x6 into a new reg \n"
      "mov rdx, [ rsi + 0x20 ]; saving arg1[4] in rdx. \n"
      "mulx r14, r15, r14; x10, x9<- arg1[4] * x1 \n"
      "test al, al \n"
      "adox r15, rbp \n"
      "adcx r15, rcx \n"
      "setc dl; spill CF x62 to reg (rdx) \n"
      "clc; \n"
      "adcx r15, r11 \n"
      "adox rax, r14 \n"
      "movzx rdx, dl \n"
      "lea r12, [ r12 + rax ] \n"
      "lea r12, [ r12 + rdx ] \n"
      "adc r12, 0x0 \n"
      "mov r11, r15; x94, copying x91 here, cause x91 is needed in a "
      "reg for other than x94, namely all: , x95, x94, size: 2 \n"
      "shrd r11, r12, 51; x94 <- x93||x91 >> 51 \n"
      "imul rbp, [ rsi + 0x20 ], 0x2; x3 <- arg1[4] * 0x2 \n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx \n"
      "mulx rbp, rcx, rbp; x30, x29<- arg1[0] * x3 \n"
      "mov rdx, [ rsi + 0x10 ]; arg1[2] to rdx \n"
      "mulx r14, rax, [ rsi + 0x10 ]; x20, x19<- arg1[2] * arg1[2] \n"
      "mov rdx, [ rsi + 0x8 ]; arg1[1] to rdx \n"
      "mulx r9, r12, r9; x24, x23<- arg1[1] * x6 \n"
      "xor rdx, rdx \n"
      "adox rax, r12 \n"
      "adox r9, r14 \n"
      "adcx rax, rcx \n"
      "adcx rbp, r9 \n"
      "xor rcx, rcx \n"
      "adox rax, r11 \n"
      "adox rbp, rcx \n"
      "mov rdx, rax; x99, copying x96 here, cause x96 is needed in a "
      "reg for other than x99, namely all: , x99, x100, size: 2 \n"
      "shrd rdx, rbp, 51; x99 <- x98||x96 >> 51 \n"
      "imul rdx, rdx, 0x13; x101 <- x99 * 0x13 \n"
      "lea rbx, [ rbx + rdx ] \n"
      "and r15, r13; x95 <- x91& 0x7ffffffffffff \n"
      "mov r11, rbx; x103, copying x102 here, cause x102 is needed in a "
      "reg for other than x103, namely all: , x103, x104, size: 2 \n"
      "shr r11, 51; x103 <- x102>> 51 \n"
      "and r10, r13; x85 <- x81& 0x7ffffffffffff \n"
      "lea r11, [ r11 + r10 ] \n"
      "mov r14, r11; x107, copying x105 here, cause x105 is needed in a "
      "reg for other than x107, namely all: , x106, x107, size: 2 \n"
      "and r14, r13; x107 <- x105& 0x7ffffffffffff \n"
      "mov [ rdi + 0x8 ], r14; out1[1] = x107 \n"
      "mov [ rdi + 0x18 ], r15; out1[3] = x95 \n"
      "shr r11, 51; x106 <- x105>> 51 \n"
      "and r8, r13; x90 <- x86& 0x7ffffffffffff \n"
      "lea r11, [ r11 + r8 ] \n"
      "mov [ rdi + 0x10 ], r11; out1[2] = x108 \n"
      "and rbx, r13; x104 <- x102& 0x7ffffffffffff \n"
      "mov [ rdi + 0x0 ], rbx; out1[0] = x104 \n"
      "and rax, r13; x100 <- x96& 0x7ffffffffffff \n"
      "mov [ rdi + 0x20 ], rax; out1[4] = x100 \n"
      "mov rbx, [ rsp + 0x0 ]; restoring from stack \n"
      "mov rbp, [ rsp + 0x8 ]; restoring from stack \n"
      "mov r12, [ rsp + 0x10 ]; restoring from stack \n"
      "mov r13, [ rsp + 0x18 ]; restoring from stack \n"
      "mov r14, [ rsp + 0x20 ]; restoring from stack \n"
      "mov r15, [ rsp + 0x28 ]; restoring from stack \n"
      "add rsp, 0x38  \n"
      "ret\n"};

  char fb[] = {
      "sub rsp, 0x38  \n"
      "mov [ rsp + 0x0 ], rbx; saving to stack \n"
      "mov [ rsp + 0x8 ], rbp; saving to stack \n"
      "mov [ rsp + 0x10 ], r12; saving to stack \n"
      "mov [ rsp + 0x18 ], r13; saving to stack \n"
      "mov [ rsp + 0x20 ], r14; saving to stack \n"
      "mov [ rsp + 0x28 ], r15; saving to stack \n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx \n"
      "mulx r13, rcx, [ rsi + 0x0 ]; x38, x37<- arg1[0] * arg1[0] \n"
      "imul rax, [ rsi + 0x18 ], 0x13; x4 <- arg1[3] * 0x13 \n"
      "imul rbx, [ rsi + 0x20 ], 0x13; x1 <- arg1[4] * 0x13 \n"
      "imul rbp, rax, 0x2; x5 <- x4 * 0x2 \n"
      "imul r10, rbx, 0x2; x2 <- x1 * 0x2 \n"
      "mov rdx, [ rsi + 0x8 ]; arg1[1] to rdx \n"
      "mulx r9, r15, r10; x22, x21<- arg1[1] * x2 \n"
      "mov rdx, rbp; x5 to rdx \n"
      "mulx rdx, r8, [ rsi + 0x10 ]; x18, x17<- arg1[2] * x5 \n"
      "test al, al \n"
      "adox r8, r15 \n"
      "adcx r8, rcx \n"
      "adox r9, rdx \n"
      "adcx r13, r9 \n"
      "mov r14, 0x7ffffffffffff ; moving imm to reg \n"
      "mov r12, r8; x48, copying x43 here, cause x43 is needed in a reg for "
      "other than x48, namely all: , x47, x48, size: 2 \n"
      "and r12, r14; x48 <- x43& 0x7ffffffffffff \n"
      "shrd r8, r13, 51; x47 <- x45||x43 >> 51 \n"
      "imul r11, [ rsi + 0x8 ], 0x2; x8 <- arg1[1] * 0x2 \n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx \n"
      "mulx r11, rbp, r11; x36, x35<- arg1[0] * x8 \n"
      "mov rdx, rax; x4 to rdx \n"
      "mulx rdx, rax, [ rsi + 0x18 ]; x14, x13<- arg1[3] * x4 \n"
      "xchg rdx, r10; x2, swapping with x14, which is currently in rdx \n"
      "mulx rcx, r15, [ rsi + 0x10 ]; x16, x15<- arg1[2] * x2 \n"
      "xor r9, r9 \n"
      "adox rax, r15 \n"
      "adox rcx, r10 \n"
      "adcx rax, rbp \n"
      "mov r13, -0x2 ; moving imm to reg \n"
      "inc r13; OF<-0x0, preserve CF (workaround, load -2, increa it, and dont "
      "save it. I this a hack?) \n"
      "adox rax, r8 \n"
      "adcx r11, rcx \n"
      "adox r11, r9 \n"
      "mov r13, rax; x84, copying x81 here, cause x81 is needed in a reg for "
      "other than x84, namely all: , x84, x85, size: 2 \n"
      "shrd r13, r11, 51; x84 <- x83||x81 >> 51 \n"
      "imul r8, [ rsi + 0x10 ], 0x2; x7 <- arg1[2] * 0x2 \n"
      "mov rbp, rdx; preserving value of x2 into a new reg \n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx. \n"
      "mulx r10, r15, [ rsi + 0x8 ]; x28, x27<- arg1[1] * arg1[1] \n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx \n"
      "mulx rcx, r11, r8; x34, x33<- arg1[0] * x7 \n"
      "mov rdx, [ rsi + 0x18 ]; arg1[3] to rdx \n"
      "mulx rbp, r9, rbp; x12, x11<- arg1[3] * x2 \n"
      "test al, al \n"
      "adox r9, r15 \n"
      "adox r10, rbp \n"
      "adcx r9, r11 \n"
      "mov rdx, -0x2 ; moving imm to reg \n"
      "inc rdx; OF<-0x0, preserve CF (workaround, load -2, increa it, and dont "
      "save it. I this a hack?) \n"
      "adox r9, r13 \n"
      "adcx rcx, r10 \n"
      "mov rdx, 0x0 ; moving imm to reg \n"
      "adox rcx, rdx \n"
      "mov r13, r9; x89, copying x86 here, cause x86 is needed in a reg for "
      "other than x89, namely all: , x90, x89, size: 2 \n"
      "shrd r13, rcx, 51; x89 <- x88||x86 >> 51 \n"
      "imul r15, [ rsi + 0x18 ], 0x2; x6 <- arg1[3] * 0x2 \n"
      "xchg rdx, rbx; x1, swapping with 0x0, which is currently in rdx \n"
      "mulx rdx, r11, [ rsi + 0x20 ]; x10, x9<- arg1[4] * x1 \n"
      "xchg rdx, r15; x6, swapping with x10, which is currently in rdx \n"
      "mulx rbp, r10, [ rsi + 0x0 ]; x32, x31<- arg1[0] * x6 \n"
      "mov rcx, rdx; preserving value of x6 into a new reg \n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx. \n"
      "mulx r8, rbx, r8; x26, x25<- arg1[1] * x7 \n"
      "xor rdx, rdx \n"
      "adox r11, rbx \n"
      "adox r8, r15 \n"
      "adcx r11, r10 \n"
      "adcx rbp, r8 \n"
      "test al, al \n"
      "adox r11, r13 \n"
      "adox rbp, rdx \n"
      "mov r13, r11; x94, copying x91 here, cause x91 is needed in a reg for "
      "other than x94, namely all: , x95, x94, size: 2 \n"
      "shrd r13, rbp, 51; x94 <- x93||x91 >> 51 \n"
      "imul r15, [ rsi + 0x20 ], 0x2; x3 <- arg1[4] * 0x2 \n"
      "xchg rdx, r15; x3, swapping with 0x0, which is currently in rdx \n"
      "mulx rdx, r10, [ rsi + 0x0 ]; x30, x29<- arg1[0] * x3 \n"
      "mov rbx, rdx; preserving value of x30 into a new reg \n"
      "mov rdx, [ rsi + 0x10 ]; saving arg1[2] in rdx. \n"
      "mulx r8, rbp, [ rsi + 0x10 ]; x20, x19<- arg1[2] * arg1[2] \n"
      "mov rdx, [ rsi + 0x8 ]; arg1[1] to rdx \n"
      "mulx rcx, r15, rcx; x24, x23<- arg1[1] * x6 \n"
      "xor rdx, rdx \n"
      "adox rbp, r15 \n"
      "adox rcx, r8 \n"
      "adcx rbp, r10 \n"
      "mov r10, -0x2 ; moving imm to reg \n"
      "inc r10; OF<-0x0, preserve CF (workaround, load -2, increa it, and dont "
      "save it. I this a hack?) \n"
      "adox rbp, r13 \n"
      "adcx rbx, rcx \n"
      "adox rbx, rdx \n"
      "mov r10, rbp; x99, copying x96 here, cause x96 is needed in a reg for "
      "other than x99, namely all: , x99, x100, size: 2 \n"
      "shrd r10, rbx, 51; x99 <- x98||x96 >> 51 \n"
      "imul r10, r10, 0x13; x101 <- x99 * 0x13 \n"
      "lea r12, [ r12 + r10 ] \n"
      "and rax, r14; x85 <- x81& 0x7ffffffffffff \n"
      "mov r13, r12; x103, copying x102 here, cause x102 is needed in a reg "
      "for "
      "other than x103, namely all: , x103, x104, size: 2 \n"
      "shr r13, 51; x103 <- x102>> 51 \n"
      "lea r13, [ r13 + rax ] \n"
      "mov r8, r13; x107, copying x105 here, cause x105 is needed in a reg for "
      "other than x107, namely all: , x106, x107, size: 2 \n"
      "and r8, r14; x107 <- x105& 0x7ffffffffffff \n"
      "mov [ rdi + 0x8 ], r8; out1[1] = x107 \n"
      "shr r13, 51; x106 <- x105>> 51 \n"
      "and r9, r14; x90 <- x86& 0x7ffffffffffff \n"
      "and rbp, r14; x100 <- x96& 0x7ffffffffffff \n"
      "mov [ rdi + 0x20 ], rbp; out1[4] = x100 \n"
      "and r12, r14; x104 <- x102& 0x7ffffffffffff \n"
      "lea r13, [ r13 + r9 ] \n"
      "and r11, r14; x95 <- x91& 0x7ffffffffffff \n"
      "mov [ rdi + 0x0 ], r12; out1[0] = x104 \n"
      "mov [ rdi + 0x18 ], r11; out1[3] = x95 \n"
      "mov [ rdi + 0x10 ], r13; out1[2] = x108 \n"
      "mov rbx, [ rsp + 0x0 ]; restoring from stack \n"
      "mov rbp, [ rsp + 0x8 ]; restoring from stack \n"
      "mov r12, [ rsp + 0x10 ]; restoring from stack \n"
      "mov r13, [ rsp + 0x18 ]; restoring from stack \n"
      "mov r14, [ rsp + 0x20 ]; restoring from stack \n"
      "mov r15, [ rsp + 0x28 ]; restoring from stack \n"
      "add rsp, 0x38  \n"
      "ret \n"};
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  const int num_batches = 10;
  const int batch_size = 20;

  // INIT
  int arg_num_out = 1;
  int chunksize = 0;
  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fb, batch_size, num_batches)) {
    err(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  const char *output = NULL;
  size_t jsonlen = 0;
  ms_getJson(ms, &output, &jsonlen);
  printf("%s\n", output);

  // Require to have true in the string but not false
  if (strstr(output, "true") == NULL && strstr(output, "false") != NULL) {
    fprintf(stderr, "should have been a correct result\n");
    ms_terminate(ms);
    return 1;
  }
  // END
  if (ms_terminate(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return 0;
}
