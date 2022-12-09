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

#include "helper.h"
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char symbol[] = {"fiat_poly1305_carry_mul"};
const char lib[] = {"./liball_fiat.so"};
const int arg_width = 3;
const int arg_num_in = 2;

int main() {
  SIGILL_SETUP();

  char fa[] = {

      "SECTION .text\n"
      "	GLOBAL mul_poly1305\n"
      "mul_poly1305:\n"
      "sub rsp, 0x40\n"
      "imul rax, [ rdx + 0x10 ], 0xa; x10002 <- arg2[2] * 0xa\n"
      "imul r10, [ rdx + 0x10 ], 0x5; x10000 <- arg2[2] * 0x5\n"
      "mov r11, rdx; preserving value of arg2 into a new reg\n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx.\n"
      "mulx r8, rcx, [ r11 + 0x0 ]; x6_1, x6_0<- arg1[1] * arg2[0] (_0*_0)\n"
      "mov rdx, [ rsi + 0x8 ]; arg1[1] to rdx\n"
      "mov [ rsp + 0x0 ], r15; spilling calSv-r15 to mem\n"
      "mulx r15, r9, rax; x3_1, x3_0<- arg1[1] * x10002 (_0*_0)\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mov [ rsp + 0x8 ], r14; spilling calSv-r14 to mem\n"
      "mulx r14, rax, [ r11 + 0x0 ]; x9_1, x9_0<- arg1[0] * arg2[0] (_0*_0)\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mov [ rsp + 0x10 ], r13; spilling calSv-r13 to mem\n"
      "mov [ rsp + 0x18 ], r12; spilling calSv-r12 to mem\n"
      "mulx r12, r13, [ r11 + 0x10 ]; x7_1, x7_0<- arg1[0] * arg2[2] (_0*_0)\n"
      "imul rdx, [ r11 + 0x8 ], 0x2; x10003 <- arg2[1] * 0x2\n"
      "mov [ rsp + 0x20 ], rbp; spilling calSv-rbp to mem\n"
      "mov [ rsp + 0x28 ], rbx; spilling calSv-rbx to mem\n"
      "mulx rbx, rbp, [ rsi + 0x8 ]; x5_1, x5_0<- arg1[1] * x10003 (_0*_0)\n"
      "mov rdx, r10; x10000 to rdx\n"
      "mov [ rsp + 0x30 ], rbx; spilling x5_1 to mem\n"
      "mulx rbx, r10, [ rsi + 0x10 ]; x1_1, x1_0<- arg1[2] * x10000 (_0*_0)\n"
      "imul rdx, [ r11 + 0x8 ], 0xa; x10001 <- arg2[1] * 0xa\n"
      "mov [ rsp + 0x38 ], rbp; spilling x5_0 to mem\n"
      "mov rbp, r8;x10006_1, copying x6_1 here, cause x6_1 is needed in a reg. "
      "It has those deps: \"\", current hard deps: \"x6_0, x6_1\"\n"
      "test al, al\n"
      "adox r10, rcx\n"
      "adox rbp, rbx\n"
      "mulx r8, rcx, [ rsi + 0x10 ]; x2_1, x2_0<- arg1[2] * x10001 (_0*_0)\n"
      "mov rbx, r15;x10004_1, copying x3_1 here, cause x3_1 is needed in a "
      "reg. "
      "It has those deps: \"\", current hard deps: \"x3_0, x3_1\"\n"
      "adcx rcx, r9\n"
      "adcx rbx, r8\n"
      "mov r15, r14;x10_1, copying x9_1 here, cause x9_1 is needed in a reg. "
      "It "
      "has those deps: \"\", current hard deps: \"x9_0, x9_1\"\n"
      "xor r9, r9\n"
      "adox rcx, rax\n"
      "adox r15, rbx\n"
      "mov rax, 0x2c ; moving imm to reg\n"
      "bzhi r14, rcx, rax; x12 <- x10_0 (only least 0x2c bits)\n"
      "shrd rcx, r15, 44; x11 <- x10_1||x10_0 >> 44\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mulx rbx, r8, [ r11 + 0x8 ]; x8_1, x8_0<- arg1[0] * arg2[1] (_0*_0)\n"
      "mov r9, rbx;x14_1, copying x8_1 here, cause x8_1 is needed in a reg. It "
      "has those deps: \"\", current hard deps: \"x8_0, x8_1\"\n"
      "xor rdx, rdx\n"
      "adox r10, r8\n"
      "adox r9, rbp\n"
      "adcx r10, rcx\n"
      "adc r9, 0x0\n"
      "mov rbp, 0x2b ; moving imm to reg\n"
      "bzhi r15, r10, rbp; x17 <- x15_0 (only least 0x2b bits)\n"
      "mov rdx, [ r11 + 0x0 ]; arg2[0] to rdx\n"
      "mulx r8, rcx, [ rsi + 0x10 ]; x4_1, x4_0<- arg1[2] * arg2[0] (_0*_0)\n"
      "adox rcx, [ rsp + 0x38 ]\n"
      "adox r8, [ rsp + 0x30 ]\n"
      "shrd r10, r9, 43; x16 <- x15_1||x15_0 >> 43\n"
      "mov rdx, r12;x13_1, copying x7_1 here, cause x7_1 is needed in a reg. "
      "It "
      "has those deps: \"\", current hard deps: \"x7_0, x7_1\"\n"
      "add rcx, r13; could be done better, if r0 has been u8 as well\n"
      "adcx rdx, r8\n"
      "xor r13, r13\n"
      "adox rcx, r10\n"
      "adox rdx, r13\n"
      "bzhi r12, rcx, rbp; x20 <- x18_0 (only least 0x2b bits)\n"
      "shrd rcx, rdx, 43; x19 <- x18_1||x18_0 >> 43\n"
      "imul rbx, rcx, 0x5; x21 <- x19 * 0x5\n"
      "lea r14, [ r14 + rbx ]\n"
      "bzhi r9, r14, rax; x24 <- x22 (only least 0x2c bits)\n"
      "shr r14, 44; x23 <- x22>> 44\n"
      "mov [ rdi + 0x0 ], r9; out1[0] = x24\n"
      "lea r14, [ r14 + r15 ]\n"
      "mov r15, 0x7ffffffffff ; moving imm to reg\n"
      "mov r8, r14;x27, copying x25 here, cause x25 is needed in a reg. It has "
      "those deps: \"x26, x27, size: 2\", current hard deps: \"\"\n"
      "and r8, r15; x27 <- x25&0x7ffffffffff\n"
      "mov [ rdi + 0x8 ], r8; out1[1] = x27\n"
      "shr r14, 43; x26 <- x25>> 43\n"
      "lea r14, [ r14 + r12 ]\n"
      "mov [ rdi + 0x10 ], r14; out1[2] = x28\n"
      "mov r15, [ rsp + 0x0 ] ; pop\n"
      "mov r14, [ rsp + 0x8 ] ; pop\n"
      "mov r13, [ rsp + 0x10 ] ; pop\n"
      "mov r12, [ rsp + 0x18 ] ; pop\n"
      "mov rbp, [ rsp + 0x20 ] ; pop\n"
      "mov rbx, [ rsp + 0x28 ] ; pop\n"
      "add rsp, 0x40 \n"
      "ret\n"
      "; cpu Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz\n"
      "; ratio 1.0698\n"
      "; seed 1785685356 \n"
      "; CC / CFLAGS gcc / -march=native -mtune=native -O3 \n"
      "; time needed: 1103 ms / 35 evals=> 31.514285714285716ms/eval\n"
      "; Time spent for assembling and measureing (initial batch_size=250, "
      "initial num_batches=31): 67 ms\n"
      "; number of used evaluations: 35\n"
      "; Ratio (time for assembling + measure)/(total runtime for 35 evals): "
      "0.06074342701722575\n"
      "; number reverted permutation/ tried permutation: 11 / 16 =68.750%\n"
      "; number reverted decision/ tried decision: 8 / 19 =42.105%\n"};

  char fb[] = {
      "\n"
      "SECTION .text\n"
      "	GLOBAL mul_poly1305\n"
      "mul_poly1305:\n"
      "sub rsp, 0x48\n"
      "imul rax, [ rdx + 0x10 ], 0xa; x10002 <- arg2[2] * 0xa\n"
      "mov r10, rdx; preserving value of arg2 into a new reg\n"
      "mov rdx, [ rsi + 0x10 ]; saving arg1[2] in rdx.\n"
      "mulx rcx, r11, [ r10 + 0x0 ]; x4_1, x4_0<- arg1[2] * arg2[0] (_0*_0)\n"
      "imul rdx, [ r10 + 0x10 ], 0x5; x10000 <- arg2[2] * 0x5\n"
      "mov r8, rdx; preserving value of x10000 into a new reg\n"
      "mov rdx, [ r10 + 0x0 ]; saving arg2[0] in rdx.\n"
      "mov [ rsp + 0x0 ], r15; spilling calSv-r15 to mem\n"
      "mulx r15, r9, [ rsi + 0x8 ]; x6_1, x6_0<- arg1[1] * arg2[0] (_0*_0)\n"
      "mov rdx, rax; x10002 to rdx\n"
      "mov [ rsp + 0x8 ], r14; spilling calSv-r14 to mem\n"
      "mulx r14, rax, [ rsi + 0x8 ]; x3_1, x3_0<- arg1[1] * x10002 (_0*_0)\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mov [ rsp + 0x10 ], r13; spilling calSv-r13 to mem\n"
      "mov [ rsp + 0x18 ], r12; spilling calSv-r12 to mem\n"
      "mulx r12, r13, [ r10 + 0x0 ]; x9_1, x9_0<- arg1[0] * arg2[0] (_0*_0)\n"
      "mov rdx, [ r10 + 0x10 ]; arg2[2] to rdx\n"
      "mov [ rsp + 0x20 ], rbp; spilling calSv-rbp to mem\n"
      "mov [ rsp + 0x28 ], rbx; spilling calSv-rbx to mem\n"
      "mulx rbx, rbp, [ rsi + 0x0 ]; x7_1, x7_0<- arg1[0] * arg2[2] (_0*_0)\n"
      "imul rdx, [ r10 + 0x8 ], 0x2; x10003 <- arg2[1] * 0x2\n"
      "mov [ rsp + 0x30 ], rbx; spilling x7_1 to mem\n"
      "mov [ rsp + 0x38 ], rbp; spilling x7_0 to mem\n"
      "mulx rbp, rbx, [ rsi + 0x8 ]; x5_1, x5_0<- arg1[1] * x10003 (_0*_0)\n"
      "mov [ rsp + 0x40 ], r12; spilling x9_1 to mem\n"
      "mov r12, rbp;x10005_1, copying x5_1 here, cause x5_1 is needed in a "
      "reg. "
      "It has those deps: \"\", current hard deps: \"x5_0, x5_1\"\n"
      "xor rdx, rdx\n"
      "adox r11, rbx\n"
      "adox r12, rcx\n"
      "mov rdx, [ rsi + 0x10 ]; arg1[2] to rdx\n"
      "mulx rbx, rcx, r8; x1_1, x1_0<- arg1[2] * x10000 (_0*_0)\n"
      "adcx r11, [ rsp + 0x38 ]\n"
      "adcx r12, [ rsp + 0x30 ]\n"
      "mov rdx, r15;x10006_1, copying x6_1 here, cause x6_1 is needed in a "
      "reg. "
      "It has those deps: \"\", current hard deps: \"x6_0, x6_1\"\n"
      "test al, al\n"
      "adox rcx, r9\n"
      "adox rdx, rbx\n"
      "imul r8, [ r10 + 0x8 ], 0xa; x10001 <- arg2[1] * 0xa\n"
      "mov r9, rdx; preserving value of x10006_1 into a new reg\n"
      "mov rdx, [ rsi + 0x10 ]; saving arg1[2] in rdx.\n"
      "mulx rbp, r15, r8; x2_1, x2_0<- arg1[2] * x10001 (_0*_0)\n"
      "mov rbx, r14;x10004_1, copying x3_1 here, cause x3_1 is needed in a "
      "reg. "
      "It has those deps: \"\", current hard deps: \"x3_0, x3_1\"\n"
      "xor rdx, rdx\n"
      "adox r15, rax\n"
      "adox rbx, rbp\n"
      "adcx r15, r13\n"
      "adcx rbx, [ rsp + 0x40 ]\n"
      "mov rax, 0xfffffffffff ; moving imm to reg\n"
      "mov r14, r15;x12, copying x10_0 here, cause x10_0 is needed in a reg. "
      "It "
      "has those deps: \"x11, x12, size: 2\", current hard deps: \"\"\n"
      "and r14, rax; x12 <- x10_0&0xfffffffffff\n"
      "shrd r15, rbx, 44; x11 <- x10_1||x10_0 >> 44\n"
      "mov rdx, [ r10 + 0x8 ]; arg2[1] to rdx\n"
      "mulx r8, r13, [ rsi + 0x0 ]; x8_1, x8_0<- arg1[0] * arg2[1] (_0*_0)\n"
      "mov rdx, r8;x14_1, copying x8_1 here, cause x8_1 is needed in a reg. It "
      "has those deps: \"\", current hard deps: \"x8_0, x8_1\"\n"
      "add rcx, r13; could be done better, if r0 has been u8 as well\n"
      "adcx rdx, r9\n"
      "add rcx, r15; could be done better, if r0 has been u8 as well\n"
      "adc rdx, 0x0\n"
      "mov r9, 0x2b ; moving imm to reg\n"
      "bzhi rbp, rcx, r9; x17 <- x15_0 (only least 0x2b bits)\n"
      "shrd rcx, rdx, 43; x16 <- x15_1||x15_0 >> 43\n"
      "xor rbx, rbx\n"
      "adox r11, rcx\n"
      "adox r12, rbx\n"
      "bzhi r15, r11, r9; x20 <- x18_0 (only least 0x2b bits)\n"
      "shrd r11, r12, 43; x19 <- x18_1||x18_0 >> 43\n"
      "imul r13, r11, 0x5; x21 <- x19 * 0x5\n"
      "lea r14, [ r14 + r13 ]\n"
      "mov r8, r14;x24, copying x22 here, cause x22 is needed in a reg. It has "
      "those deps: \"x23, x24, size: 2\", current hard deps: \"\"\n"
      "and r8, rax; x24 <- x22&0xfffffffffff\n"
      "mov [ rdi + 0x0 ], r8; out1[0] = x24\n"
      "shr r14, 44; x23 <- x22>> 44\n"
      "lea r14, [ r14 + rbp ]\n"
      "mov rdx, 0x7ffffffffff ; moving imm to reg\n"
      "mov rbp, r14;x27, copying x25 here, cause x25 is needed in a reg. It "
      "has "
      "those deps: \"x26, x27, size: 2\", current hard deps: \"\"\n"
      "and rbp, rdx; x27 <- x25&0x7ffffffffff\n"
      "mov [ rdi + 0x8 ], rbp; out1[1] = x27\n"
      "shr r14, 43; x26 <- x25>> 43\n"
      "lea r14, [ r14 + r15 ]\n"
      "mov [ rdi + 0x10 ], r14; out1[2] = x28\n"
      "mov r15, [ rsp + 0x0 ] ; pop\n"
      "mov r14, [ rsp + 0x8 ] ; pop\n"
      "mov r13, [ rsp + 0x10 ] ; pop\n"
      "mov r12, [ rsp + 0x18 ] ; pop\n"
      "mov rbp, [ rsp + 0x20 ] ; pop\n"
      "mov rbx, [ rsp + 0x28 ] ; pop\n"
      "add rsp, 0x48 \n"
      "ret\n"
      "; cpu Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz\n"
      "; ratio 1.0240\n"
      "; seed 2025769887375571 \n"
      "; CC / CFLAGS gcc / -march=native -mtune=native -O3 \n"
      "; time needed: 323 ms / 10 evals=> 32.3ms/eval\n"
      "; Time spent for assembling and measureing (initial batch_size=251, "
      "initial num_batches=31): 31 ms\n"
      "; number of used evaluations: 10\n"
      "; Ratio (time for assembling + measure)/(total runtime for 10 evals): "
      "0.09597523219814241\n"
      "; number reverted permutation/ tried permutation: 4 / 6 =66.667%\n"
      "; number reverted decision/ tried decision: 2 / 4 =50.000%\n"};
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  const int num_batches = 40;
  const int batch_size = 10;

  // INIT
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {
      0x300000000000 - 1,
      0x180000000000 - 1,
      0x180000000000 - 1,
  };
  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  // fa causes segfault
  // fb incorrect results

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
