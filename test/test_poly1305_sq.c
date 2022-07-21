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

const char symbol[] = {"fiat_poly1305_carry_square"};
const int arg_width = 3;
const int arg_num_in = 1;

int main() {
  SIGILL_SETUP();

  char fa[] = {
      "SECTION .text\n"
      "	GLOBAL square_poly1305\n"
      "square_poly1305:\n"
      "sub rsp, 0x20\n"
      "imul rax, [ rsi + 0x10 ], 0x2; x3 <- arg1[2] * 0x2\n"
      "imul r10, [ rsi + 0x8 ], 0x2; x4 <- arg1[1] * 0x2\n"
      "imul r11, [ rsi + 0x10 ], 0x5; x1 <- arg1[2] * 0x5\n"
      "imul rdx, [ rsi + 0x8 ], 0x2; x10001 <- arg1[1] * 0x2\n"
      "mulx r8, rcx, [ rsi + 0x8 ]; x7_1, x7_0<- arg1[1] * x10001 (_0*_0)\n"
      "mov rdx, rax; x3 to rdx\n"
      "mulx r9, rax, [ rsi + 0x0 ]; x8_1, x8_0<- arg1[0] * x3 (_0*_0)\n"
      "mov rdx, [ rsi + 0x10 ]; arg1[2] to rdx\n"
      "mov [ rsp + 0x0 ], r15; spilling calSv-r15 to mem\n"
      "mov [ rsp + 0x8 ], r14; spilling calSv-r14 to mem\n"
      "mulx r14, r15, r11; x5_1, x5_0<- arg1[2] * x1 (_0*_0)\n"
      "mov rdx, r9;x14_1, copying x8_1 here, cause x8_1 is needed in a reg. It "
      "has those deps: "
      ", current hard deps: "
      "\n"
      "test al, al\n"
      "adox rcx, rax\n"
      "adox rdx, r8\n"
      "mov r8, rdx; preserving value of x14_1 into a new reg\n"
      "mov rdx, [ rsi + 0x0 ]; saving arg1[0] in rdx.\n"
      "mulx r9, rax, rdx; x10_1, x10_0<- arg1[0]^2\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mov [ rsp + 0x10 ], r13; spilling calSv-r13 to mem\n"
      "mov [ rsp + 0x18 ], r12; spilling calSv-r12 to mem\n"
      "mulx r12, r13, r10; x9_1, x9_0<- arg1[0] * x4 (_0*_0)\n"
      "mov rdx, r12;x15_1, copying x9_1 here, cause x9_1 is needed in a reg. "
      "It "
      "has those deps: "
      ", current hard deps: "
      "\n"
      "adcx r15, r13\n"
      "adcx rdx, r14\n"
      "imul r10, r11, 0x2; x2 <- x1 * 0x2\n"
      "imul r11, r10, 0x2; x10000 <- x2 * 0x2\n"
      "mov r14, rdx; preserving value of x15_1 into a new reg\n"
      "mov rdx, [ rsi + 0x8 ]; saving arg1[1] in rdx.\n"
      "mulx r12, r13, r11; x6_1, x6_0<- arg1[1] * x10000 (_0*_0)\n"
      "mov rdx, r9;x11_1, copying x10_1 here, cause x10_1 is needed in a reg. "
      "It "
      "has those deps: "
      ", current hard deps: 0_1\n"
      "add r13, rax; could be done better, if r0 has been u8 as well\n"
      "adcx rdx, r12\n"
      "mov rax, 0x2c ; moving imm to reg\n"
      "bzhi r9, r13, rax; x13 <- x11_0 (only least 0x2c bits)\n"
      "shrd r13, rdx, 44; x12 <- x11_1||x11_0 >> 44\n"
      "add r15, r13; could be done better, if r0 has been u8 as well\n"
      "adc r14, 0x0\n"
      "mov r10, r15;x17, copying x16_0 here, cause x16_0 is needed in a reg. "
      "It "
      "has those deps: \"x17, x18, size: 2\", current hard deps: "
      "\n"
      "shrd r10, r14, 43; x17 <- x16_1||x16_0 >> 43\n"
      "mov r11, 0x7ffffffffff ; moving imm to reg\n"
      "and r15, r11; x18 <- x16_0&0x7ffffffffff\n"
      "mov r12, 0x0 ; moving imm to reg\n"
      "adox rcx, r10\n"
      "adox r8, r12\n"
      "mov rdx, rcx;x21, copying x19_0 here, cause x19_0 is needed in a reg. "
      "It "
      "has those deps: \"x20, x21, size: 2\", current hard deps: "
      "\n"
      "and rdx, r11; x21 <- x19_0&0x7ffffffffff\n"
      "shrd rcx, r8, 43; x20 <- x19_1||x19_0 >> 43\n"
      "imul r13, rcx, 0x5; x22 <- x20 * 0x5\n"
      "lea r9, [ r9 + r13 ]\n"
      "mov r14, r9;x24, copying x23 here, cause x23 is needed in a reg. It has "
      "those deps: \"x24, x25, size: 2\", current hard deps: "
      "\n"
      "shr r14, 44; x24 <- x23>> 44\n"
      "lea r14, [ r14 + r15 ]\n"
      "mov r10, 0x2b ; moving imm to reg\n"
      "bzhi r15, r14, r10; x28 <- x26 (only least 0x2b bits)\n"
      "shr r14, 43; x27 <- x26>> 43\n"
      "mov [ rdi + 0x8 ], r15; out1[1] = x28\n"
      "bzhi r8, r9, rax; x25 <- x23 (only least 0x2c bits)\n"
      "lea r14, [ r14 + rdx ]\n"
      "mov [ rdi + 0x0 ], r8; out1[0] = x25\n"
      "mov [ rdi + 0x10 ], r14; out1[2] = x29\n"
      "mov r15, [ rsp + 0x0 ] ; pop\n"
      "mov r14, [ rsp + 0x8 ] ; pop\n"
      "mov r13, [ rsp + 0x10 ] ; pop\n"
      "mov r12, [ rsp + 0x18 ] ; pop\n"
      "add rsp, 0x20 \n"
      "ret\n"
      "; cpu Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz\n"
      "; ratio 1.0298\n"
      "; seed 3115468088012173 \n"
      "; CC / CFLAGS gcc / -march=native -mtune=native -O3 \n"
      "; time needed: 434 ms / 15 evals=> 28.933333333333334ms/eval\n"
      "; Time spent for assembling and measureing (initial batch_size=310, "
      "initial num_batches=31): 41 ms\n"
      "; number of used evaluations: 15\n"
      "; Ratio (time for assembling + measure)/(total runtime for 15 evals): "
      "0.0944700460829493\n"
      "; number reverted permutation/ tried permutation: 4 / 10 =40.000%\n"
      "; number reverted decision/ tried decision: 2 / 5 =40.000%\n"};

  char fb[] = {
      "SECTION .text\n"
      "	GLOBAL square_poly1305\n"
      "square_poly1305:\n"
      "sub rsp, 0x18\n"
      "imul rax, [ rsi + 0x8 ], 0x2; x10001 <- arg1[1] * 0x2\n"
      "imul r10, [ rsi + 0x10 ], 0x2; x3 <- arg1[2] * 0x2\n"
      "imul r11, [ rsi + 0x10 ], 0x5; x1 <- arg1[2] * 0x5\n"
      "mov rdx, rax; x10001 to rdx\n"
      "mulx rcx, rax, [ rsi + 0x8 ]; x7_1, x7_0<- arg1[1] * x10001 (_0*_0)\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mulx r9, r8, rdx; x10_1, x10_0<- arg1[0]^2\n"
      "mov rdx, [ rsi + 0x0 ]; arg1[0] to rdx\n"
      "mov [ rsp + 0x0 ], r15; spilling calSv-r15 to mem\n"
      "mov [ rsp + 0x8 ], r14; spilling calSv-r14 to mem\n"
      "mulx r14, r15, r10; x8_1, x8_0<- arg1[0] * x3 (_0*_0)\n"
      "mov rdx, r14;x14_1, copying x8_1 here, cause x8_1 is needed in a reg. "
      "It "
      "has those deps: "
      ", current hard deps: \"x8_0, x8_1\"\n"
      "test al, al\n"
      "adox rax, r15\n"
      "adox rdx, rcx\n"
      "mov r10, rdx; preserving value of x14_1 into a new reg\n"
      "mov rdx, [ rsi + 0x10 ]; saving arg1[2] in rdx.\n"
      "mulx r15, rcx, r11; x5_1, x5_0<- arg1[2] * x1 (_0*_0)\n"
      "imul rdx, [ rsi + 0x8 ], 0x2; x4 <- arg1[1] * 0x2\n"
      "imul r14, r11, 0x2; x2 <- x1 * 0x2\n"
      "mov [ rsp + 0x10 ], r13; spilling calSv-r13 to mem\n"
      "mulx r13, r11, [ rsi + 0x0 ]; x9_1, x9_0<- arg1[0] * x4 (_0*_0)\n"
      "mov rdx, r13;x15_1, copying x9_1 here, cause x9_1 is needed in a reg. "
      "It "
      "has those deps: "
      ", current hard deps: \"x9_0, x9_1\"\n"
      "add rcx, r11; could be done better, if r0 has been u8 as well\n"
      "adcx rdx, r15\n"
      "imul r15, r14, 0x2; x10000 <- x2 * 0x2\n"
      "xchg rdx, r15; x10000, swapping with x15_1, which is currently in rdx\n"
      "mulx r11, r14, [ rsi + 0x8 ]; x6_1, x6_0<- arg1[1] * x10000 (_0*_0)\n"
      "mov r13, r9;x11_1, copying x10_1 here, cause x10_1 is needed in a reg. "
      "It "
      "has those deps: "
      ", current hard deps: \"x10_0, x10_1\"\n"
      "test al, al\n"
      "adox r14, r8\n"
      "adox r13, r11\n"
      "mov r8, 0xfffffffffff ; moving imm to reg\n"
      "mov r9, r14;x13, copying x11_0 here, cause x11_0 is needed in a reg. It "
      "has those deps: \"x12, x13, size: 2\", current hard deps: "
      "\n"
      "and r9, r8; x13 <- x11_0&0xfffffffffff\n"
      "shrd r14, r13, 44; x12 <- x11_1||x11_0 >> 44\n"
      "xor rdx, rdx\n"
      "adox rcx, r14\n"
      "adox r15, rdx\n"
      "mov r11, 0x2b ; moving imm to reg\n"
      "bzhi r13, rcx, r11; x18 <- x16_0 (only least 0x2b bits)\n"
      "shrd rcx, r15, 43; x17 <- x16_1||x16_0 >> 43\n"
      "add rax, rcx; could be done better, if r0 has been u8 as well\n"
      "adc r10, 0x0\n"
      "mov r14, rax;x20, copying x19_0 here, cause x19_0 is needed in a reg. "
      "It "
      "has those deps: \"x20, x21, size: 2\", current hard deps: "
      "\n"
      "shrd r14, r10, 43; x20 <- x19_1||x19_0 >> 43\n"
      "imul r15, r14, 0x5; x22 <- x20 * 0x5\n"
      "bzhi rcx, rax, r11; x21 <- x19_0 (only least 0x2b bits)\n"
      "lea r9, [ r9 + r15 ]\n"
      "mov rax, 0x2c ; moving imm to reg\n"
      "bzhi r10, r9, rax; x25 <- x23 (only least 0x2c bits)\n"
      "shr r9, 44; x24 <- x23>> 44\n"
      "mov [ rdi + 0x0 ], r10; out1[0] = x25\n"
      "lea r9, [ r9 + r13 ]\n"
      "mov r13, 0x7ffffffffff ; moving imm to reg\n"
      "mov r14, r9;x28, copying x26 here, cause x26 is needed in a reg. It has "
      "those deps: \"x27, x28, size: 2\", current hard deps: "
      "\n"
      "and r14, r13; x28 <- x26&0x7ffffffffff\n"
      "shr r9, 43; x27 <- x26>> 43\n"
      "mov [ rdi + 0x8 ], r14; out1[1] = x28\n"
      "lea r9, [ r9 + rcx ]\n"
      "mov [ rdi + 0x10 ], r9; out1[2] = x29\n"
      "mov r15, [ rsp + 0x0 ] ; pop\n"
      "mov r14, [ rsp + 0x8 ] ; pop\n"
      "mov r13, [ rsp + 0x10 ] ; pop\n"
      "add rsp, 0x18 \n"
      "ret\n"
      "; cpu Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz\n"
      "; ratio 1.0776\n"
      "; seed 1164610135001796 \n"
      "; CC / CFLAGS gcc / -march=native -mtune=native -O3 \n"
      "; time needed: 1042 ms / 40 evals=> 26.05ms/eval\n"
      "; Time spent for assembling and measureing (initial batch_size=315, "
      "initial num_batches=31): 63 ms\n"
      "; number of used evaluations: 40\n"
      "; Ratio (time for assembling + measure)/(total runtime for 40 evals): "
      "0.060460652591170824\n"
      "; number reverted permutation/ tried permutation: 11 / 19 =57.895%\n"
      "; number reverted decision/ tried decision: 18 / 21 =85.714%\n"};
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
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, "./liball_fiat.so", symbol)) {
    err(ms, "Failed to measure_init. Reason: %s.");
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
    ms_measure_end(ms);
    return 1;
  }
  // END
  if (ms_measure_end(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return 0;
}
