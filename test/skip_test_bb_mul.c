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

// bitcoin-core mul
#include "helper.h"
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char symbol[] = {"secp256k1_fe_mul_inner"};
const char lib[] = {"./bbc/bbc.so"};
const int arg_width = 4;
const int arg_num_in = 2;
// those are the bounds from the JSON file
const uint64_t bounds[] = {
    0xffffffffffffffff,
    0xffffffffffffffff,
    0xffffffffffffffff,
    0xffffffffffffffff,

};

int main() {
  SIGILL_SETUP();

  char fa[] = {"SECTION .text\n"
               "	GLOBAL secp256k1_fe_mul_inner\n"
               "secp256k1_fe_mul_inner:\n"

               "sub rsp, 400\n"
               "mov rax, rdx\n"
               "mov rdx, [ rdx + 0x18 ]\n"
               "mulx r11, r10, [ rsi + 0x0 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mulx r8, rcx, [ rax + 0x20 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0x0 ], rbx\n"
               "mulx rbx, r9, [ rsi + 0x20 ]\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x8 ], rbp\n"
               "mov [ rsp + 0x10 ], r12\n"
               "mulx r12, rbp, [ rax + 0x0 ]\n"
               "mov rdx, [ rsi + 0x10 ]\n"
               "mov [ rsp + 0x18 ], r13\n"
               "mov [ rsp + 0x20 ], r14\n"
               "mulx r14, r13, [ rax + 0x18 ]\n"
               "mov rdx, [ rsi + 0x10 ]\n"
               "mov [ rsp + 0x28 ], r15\n"
               "mov [ rsp + 0x30 ], rdi\n"
               "mulx rdi, r15, [ rax + 0x0 ]\n"
               "mov rdx, [ rsi + 0x18 ]\n"
               "mov [ rsp + 0x38 ], r12\n"
               "mov [ rsp + 0x40 ], rbp\n"
               "mulx rbp, r12, [ rax + 0x20 ]\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x48 ], r8\n"
               "mov [ rsp + 0x50 ], rcx\n"
               "mulx rcx, r8, [ rax + 0x8 ]\n"
               "mov rdx, [ rax + 0x18 ]\n"
               "mov [ rsp + 0x58 ], rcx\n"
               "mov [ rsp + 0x60 ], r8\n"
               "mulx r8, rcx, [ rsi + 0x18 ]\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mov [ rsp + 0x68 ], rdi\n"
               "mov [ rsp + 0x70 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x10 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0x78 ], r15\n"
               "mov [ rsp + 0x80 ], rdi\n"
               "mulx rdi, r15, [ rsi + 0x0 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0x88 ], rdi\n"
               "mov [ rsp + 0x90 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x0 ]\n"
               "mov rdx, [ rsi + 0x18 ]\n"
               "mov [ rsp + 0x98 ], rbp\n"
               "mov [ rsp + 0xa0 ], r12\n"
               "mulx r12, rbp, [ rax + 0x0 ]\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mov [ rsp + 0xa8 ], r12\n"
               "mov [ rsp + 0xb0 ], rbp\n"
               "mulx rbp, r12, [ rsi + 0x20 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0xb8 ], r14\n"
               "mov [ rsp + 0xc0 ], r13\n"
               "mulx r13, r14, [ rsi + 0x10 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0xc8 ], r13\n"
               "mov [ rsp + 0xd0 ], r14\n"
               "mulx r14, r13, [ rax + 0x0 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0xd8 ], r15\n"
               "mov [ rsp + 0xe0 ], rdi\n"
               "mulx rdi, r15, [ rsi + 0x18 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0xe8 ], rdi\n"
               "mov [ rsp + 0xf0 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x10 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0xf8 ], r15\n"
               "mov [ rsp + 0x100 ], rdi\n"
               "mulx rdi, r15, [ rsi + 0x8 ]\n"
               "mov rdx, 0x40 \n"
               "mov [ rsp + 0x108 ], r14\n"
               "bzhi r14, r12, rdx\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0x110 ], r13\n"
               "mulx r13, r12, [ rax + 0x18 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0x118 ], r13\n"
               "mov [ rsp + 0x120 ], r12\n"
               "mulx r12, r13, [ rax + 0x8 ]\n"
               "mov rdx, [ rax + 0x0 ]\n"
               "mov [ rsp + 0x128 ], r12\n"
               "mov [ rsp + 0x130 ], r13\n"
               "mulx r13, r12, [ rsi + 0x0 ]\n"
               "mov rdx, 0x1000003d10 \n"
               "mov [ rsp + 0x138 ], r13\n"
               "mov [ rsp + 0x140 ], r12\n"
               "mulx r12, r13, r14\n"
               "\n"
               "\n"
               "adox rcx, r9\n"
               "adox rbx, r8\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mulx r8, r9, [ rsi + 0x18 ]\n"
               "\n"
               "\n"
               "xor rdx, rdx\n"
               "adox r10, r15\n"
               "adox rdi, r11\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mulx r15, r11, [ rsi + 0x0 ]\n"
               "\n"
               "\n"
               "mov rdx, [ rsp + 0x110 ]\n"
               "mov r14, rdx\n"
               "adcx r14, [ rsp + 0xe0 ]\n"
               "mov [ rsp + 0x148 ], r15\n"
               "mov r15, [ rsp + 0x108 ]\n"
               "adcx r15, [ rsp + 0xd8 ]\n"
               "\n"
               "\n"
               "mov rdx, r9\n"
               "mov [ rsp + 0x150 ], r15\n"
               "xor r15, r15\n"
               "adox rdx, [ rsp + 0xc0 ]\n"
               "adox r8, [ rsp + 0xb8 ]\n"
               "\n"
               "\n"
               "mov r9, r10\n"
               "adcx r9, [ rsp + 0x100 ]\n"
               "adcx rdi, [ rsp + 0xf8 ]\n"
               "mov r10, rdx\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x158 ], r14\n"
               "mulx r14, r15, [ rax + 0x18 ]\n"
               "\n"
               "\n"
               "xor rdx, rdx\n"
               "adox r15, [ rsp + 0xa0 ]\n"
               "adox r14, [ rsp + 0x98 ]\n"
               "\n"
               "\n"
               "mov [ rsp + 0x160 ], r14\n"
               "mov r14, [ rsp + 0x130 ]\n"
               "mov [ rsp + 0x168 ], r15\n"
               "mov r15, r14\n"
               "adcx r15, [ rsp + 0x90 ]\n"
               "mov [ rsp + 0x170 ], r11\n"
               "mov r11, [ rsp + 0x128 ]\n"
               "adcx r11, [ rsp + 0x88 ]\n"
               "\n"
               "\n"
               "mov r14, r15\n"
               "mov [ rsp + 0x178 ], r12\n"
               "xor r12, r12\n"
               "adox r14, [ rsp + 0x70 ]\n"
               "adox r11, [ rsp + 0x68 ]\n"
               "\n"
               "\n"
               "mov rdx, [ rsp + 0x120 ]\n"
               "adcx rdx, [ rsp + 0xd0 ]\n"
               "mov r15, [ rsp + 0x118 ]\n"
               "adcx r15, [ rsp + 0xc8 ]\n"
               "\n"
               "\n"
               "mov [ rsp + 0x180 ], r11\n"
               "mov r11, rcx\n"
               "mov [ rsp + 0x188 ], r14\n"
               "xor r14, r14\n"
               "adox r11, [ rsp + 0x80 ]\n"
               "adox rbx, [ rsp + 0x78 ]\n"
               "mov r12, 0x1000003d10000 \n"
               "xchg rdx, r12\n"
               "mulx r14, rcx, rbp\n"
               "\n"
               "\n"
               "mov rbp, r9\n"
               "adcx rbp, [ rsp + 0xb0 ]\n"
               "adcx rdi, [ rsp + 0xa8 ]\n"
               "\n"
               "\n"
               "mov r9, r10\n"
               "add r9, [ rsp + 0x60 ]\n"
               "adcx r8, [ rsp + 0x58 ]\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r13, rbp\n"
               "adox rdi, [ rsp + 0x178 ]\n"
               "\n"
               "\n"
               "mov r10, r9\n"
               "adcx r10, [ rsp + 0x50 ]\n"
               "adcx r8, [ rsp + 0x48 ]\n"
               "mov rbp, r13\n"
               "shrd rbp, rdi, 0x34\n"
               "shr rdi, 0x34\n"
               "\n"
               "\n"
               "mov r9, r12\n"
               "xor rdx, rdx\n"
               "adox r9, [ rsp + 0xf0 ]\n"
               "adox r15, [ rsp + 0xe8 ]\n"
               "mov r12, 0xfffffffffffff \n"
               "and r13, r12\n"
               "\n"
               "\n"
               "mov r12, r9\n"
               "adox r12, [ rsp + 0x40 ]\n"
               "adox r15, [ rsp + 0x38 ]\n"
               "\n"
               "\n"
               "mov r9, r12\n"
               "adcx r9, [ rsp + 0x170 ]\n"
               "adcx r15, [ rsp + 0x148 ]\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox rcx, r9\n"
               "adox r15, r14\n"
               "\n"
               "\n"
               "adcx rbp, rcx\n"
               "adcx r15, rdi\n"
               "mov r14, 0x30 \n"
               "bzhi rdi, rbp, r14\n"
               "mov r12, rbp\n"
               "shr r12, 0x30\n"
               "shrd rbp, r15, 0x34\n"
               "mov r9, 0x34\n"
               "sarx r9, r15, r9\n"
               "\n"
               "\n"
               "add rbp, r10\n"
               "adcx r8, r9\n"
               "mov r10, 0xf \n"
               "and r12, r10\n"
               "mov rcx, rbp\n"
               "shrd rbp, r8, 0x34\n"
               "mov r15, 0x34\n"
               "sarx r15, r8, r15\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox rbp, r11\n"
               "adox rbx, r15\n"
               "mov r11, 0x34 \n"
               "bzhi r9, rbp, r11\n"
               "shrd rbp, rbx, 0x34\n"
               "mov r8, 0x34\n"
               "sarx r8, rbx, r8\n"
               "mov r15, 0x1000003d10 \n"
               "mov rdx, r15\n"
               "mulx rbx, r15, r9\n"
               "\n"
               "\n"
               "add r15, [ rsp + 0x158 ]\n"
               "adcx rbx, [ rsp + 0x150 ]\n"
               "\n"
               "\n"
               "add rbp, [ rsp + 0x168 ]\n"
               "adcx r8, [ rsp + 0x160 ]\n"
               "imul r9, rcx, 0x10\n"
               "mov rcx, 0x40 \n"
               "bzhi r10, rbp, rcx\n"
               "mov rbp, 0xfffffffffffff0 \n"
               "and r9, rbp\n"
               "or r9, r12\n"
               "mov r12, 0x1000003d1 \n"
               "mov rdx, r12\n"
               "mulx rcx, r12, r9\n"
               "\n"
               "\n"
               "mov r9, r12\n"
               "adox r9, [ rsp + 0x140 ]\n"
               "adox rcx, [ rsp + 0x138 ]\n"
               "mov r12, r9\n"
               "shrd r12, rcx, 0x34\n"
               "shr rcx, 0x34\n"
               "mov rdx, 0x1000003d10000 \n"
               "mulx r14, rbp, r8\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r13, rbp\n"
               "mov r8, 0x0 \n"
               "adox r14, r8\n"
               "\n"
               "\n"
               "adcx r12, r15\n"
               "adcx rbx, rcx\n"
               "mov r15, 0x1000003d10 \n"
               "mov rdx, r15\n"
               "mulx rcx, r15, r10\n"
               "bzhi r10, r9, r11\n"
               "mov rbp, r12\n"
               "shrd rbp, rbx, 0x34\n"
               "shr rbx, 0x34\n"
               "\n"
               "\n"
               "add r15, [ rsp + 0x188 ]\n"
               "adcx rcx, [ rsp + 0x180 ]\n"
               "\n"
               "\n"
               "add rbp, r15\n"
               "adcx rcx, rbx\n"
               "bzhi r9, r12, r11\n"
               "mov rbx, [ rsp + 0x30 ]\n"
               "mov [ rbx + 0x8 ], r9\n"
               "mov r15, rbp\n"
               "bzhi r12, r15, r11\n"
               "shrd rbp, rcx, 0x34\n"
               "shr rcx, 0x34\n"
               "mov [ rbx + 0x0 ], r10\n"
               "\n"
               "\n"
               "add rbp, r13\n"
               "adcx r14, rcx\n"
               "mov r13, rbp\n"
               "bzhi r10, r13, r11\n"
               "mov [ rbx + 0x10 ], r12\n"
               "shrd rbp, r14, 0x34\n"
               "shr r14, 0x34\n"
               "mov [ rbx + 0x18 ], r10\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox rdi, rbp\n"
               "adox r14, r8\n"
               "mov [ rbx + 0x20 ], rdi\n"
               "mov rbx, [ rsp + 0x0 ]\n"
               "mov rbp, [ rsp + 0x8 ]\n"
               "mov r12, [ rsp + 0x10 ]\n"
               "mov r13, [ rsp + 0x18 ]\n"
               "mov r14, [ rsp + 0x20 ]\n"
               "mov r15, [ rsp + 0x28 ]\n"
               "add rsp, 400\n"
               "ret\n"};

  char fb[] = {"SECTION .text\n"
               "GLOBAL secp256k1_fe_mul_inner\n"
               "secp256k1_fe_mul_inner:\n"
               "sub rsp, 400\n"
               "mov rax, rdx\n"
               "mov rdx, [ rdx + 0x18 ]\n"
               "mulx r11, r10, [ rsi + 0x0 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mulx r8, rcx, [ rax + 0x20 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0x0 ], rbx\n"
               "mulx rbx, r9, [ rsi + 0x20 ]\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x8 ], rbp\n"
               "mov [ rsp + 0x10 ], r12\n"
               "mulx r12, rbp, [ rax + 0x0 ]\n"
               "mov rdx, [ rsi + 0x10 ]\n"
               "mov [ rsp + 0x18 ], r13\n"
               "mov [ rsp + 0x20 ], r14\n"
               "mulx r14, r13, [ rax + 0x18 ]\n"
               "mov rdx, [ rsi + 0x10 ]\n"
               "mov [ rsp + 0x28 ], r15\n"
               "mov [ rsp + 0x30 ], rdi\n"
               "mulx rdi, r15, [ rax + 0x0 ]\n"
               "mov rdx, [ rsi + 0x18 ]\n"
               "mov [ rsp + 0x38 ], r12\n"
               "mov [ rsp + 0x40 ], rbp\n"
               "mulx rbp, r12, [ rax + 0x20 ]\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x48 ], r8\n"
               "mov [ rsp + 0x50 ], rcx\n"
               "mulx rcx, r8, [ rax + 0x8 ]\n"
               "mov rdx, [ rax + 0x18 ]\n"
               "mov [ rsp + 0x58 ], rcx\n"
               "mov [ rsp + 0x60 ], r8\n"
               "mulx r8, rcx, [ rsi + 0x18 ]\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mov [ rsp + 0x68 ], rdi\n"
               "mov [ rsp + 0x70 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x10 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0x78 ], r15\n"
               "mov [ rsp + 0x80 ], rdi\n"
               "mulx rdi, r15, [ rsi + 0x0 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0x88 ], rdi\n"
               "mov [ rsp + 0x90 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x0 ]\n"
               "mov rdx, [ rsi + 0x18 ]\n"
               "mov [ rsp + 0x98 ], r15\n"
               "mov [ rsp + 0xa0 ], rdi\n"
               "mulx rdi, r15, [ rax + 0x0 ]\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mov [ rsp + 0xa8 ], rdi\n"
               "mov [ rsp + 0xb0 ], r15\n"
               "mulx r15, rdi, [ rsi + 0x20 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0xb8 ], rbp\n"
               "mov [ rsp + 0xc0 ], r12\n"
               "mulx r12, rbp, [ rsi + 0x10 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0xc8 ], r12\n"
               "mov [ rsp + 0xd0 ], rbp\n"
               "mulx rbp, r12, [ rax + 0x0 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0xd8 ], rbp\n"
               "mov [ rsp + 0xe0 ], r12\n"
               "mulx r12, rbp, [ rsi + 0x18 ]\n"
               "mov rdx, [ rax + 0x8 ]\n"
               "mov [ rsp + 0xe8 ], r12\n"
               "mov [ rsp + 0xf0 ], rbp\n"
               "mulx rbp, r12, [ rsi + 0x10 ]\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mov [ rsp + 0xf8 ], rbp\n"
               "mov [ rsp + 0x100 ], r12\n"
               "mulx r12, rbp, [ rsi + 0x8 ]\n"
               "mov rdx, 0x40 \n"
               "mov [ rsp + 0x108 ], r14\n"
               "bzhi r14, rdi, rdx\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0x110 ], r13\n"
               "mulx r13, rdi, [ rax + 0x18 ]\n"
               "mov rdx, [ rsi + 0x8 ]\n"
               "mov [ rsp + 0x118 ], r13\n"
               "mov [ rsp + 0x120 ], rdi\n"
               "mulx rdi, r13, [ rax + 0x8 ]\n"
               "mov rdx, [ rax + 0x0 ]\n"
               "mov [ rsp + 0x128 ], rdi\n"
               "mov [ rsp + 0x130 ], r13\n"
               "mulx r13, rdi, [ rsi + 0x0 ]\n"
               "mov rdx, 0x1000003d10 \n"
               "mov [ rsp + 0x138 ], r13\n"
               "mov [ rsp + 0x140 ], rdi\n"
               "mulx rdi, r13, r14\n"
               "\n"
               "\n"
               "adox rcx, r9\n"
               "adox rbx, r8\n"
               "mov rdx, [ rax + 0x10 ]\n"
               "mulx r8, r9, [ rsi + 0x18 ]\n"
               "\n"
               "\n"
               "xor rdx, rdx\n"
               "adox r10, rbp\n"
               "adox r12, r11\n"
               "mov rdx, [ rax + 0x20 ]\n"
               "mulx rbp, r11, [ rsi + 0x0 ]\n"
               "\n"
               "\n"
               "mov rdx, r9\n"
               "adcx rdx, [ rsp + 0x110 ]\n"
               "adcx r8, [ rsp + 0x108 ]\n"
               "\n"
               "\n"
               "mov r14, r10\n"
               "xor r9, r9\n"
               "adox r14, [ rsp + 0x100 ]\n"
               "adox r12, [ rsp + 0xf8 ]\n"
               "mov r10, rdx\n"
               "mov rdx, [ rsi + 0x20 ]\n"
               "mov [ rsp + 0x148 ], rbp\n"
               "mulx rbp, r9, [ rax + 0x18 ]\n"
               "\n"
               "\n"
               "adcx r9, [ rsp + 0xc0 ]\n"
               "adcx rbp, [ rsp + 0xb8 ]\n"
               "\n"
               "\n"
               "mov rdx, [ rsp + 0xe0 ]\n"
               "mov [ rsp + 0x150 ], rbp\n"
               "mov rbp, rdx\n"
               "mov [ rsp + 0x158 ], r9\n"
               "xor r9, r9\n"
               "adox rbp, [ rsp + 0xa0 ]\n"
               "mov [ rsp + 0x160 ], r11\n"
               "mov r11, [ rsp + 0xd8 ]\n"
               "adox r11, [ rsp + 0x98 ]\n"
               "\n"
               "\n"
               "mov rdx, [ rsp + 0x130 ]\n"
               "mov [ rsp + 0x168 ], r11\n"
               "mov r11, rdx\n"
               "adcx r11, [ rsp + 0x90 ]\n"
               "mov [ rsp + 0x170 ], rbp\n"
               "mov rbp, [ rsp + 0x128 ]\n"
               "adcx rbp, [ rsp + 0x88 ]\n"
               "\n"
               "\n"
               "mov rdx, r11\n"
               "mov [ rsp + 0x178 ], rdi\n"
               "xor rdi, rdi\n"
               "adox rdx, [ rsp + 0x70 ]\n"
               "adox rbp, [ rsp + 0x68 ]\n"
               "\n"
               "\n"
               "mov r9, [ rsp + 0x120 ]\n"
               "adcx r9, [ rsp + 0xd0 ]\n"
               "mov r11, [ rsp + 0x118 ]\n"
               "adcx r11, [ rsp + 0xc8 ]\n"
               "\n"
               "\n"
               "mov [ rsp + 0x180 ], rbp\n"
               "mov rbp, rcx\n"
               "mov [ rsp + 0x188 ], rdx\n"
               "xor rdx, rdx\n"
               "adox rbp, [ rsp + 0x80 ]\n"
               "adox rbx, [ rsp + 0x78 ]\n"
               "mov rdi, 0x1000003d10000 \n"
               "mov rdx, rdi\n"
               "mulx rcx, rdi, r15\n"
               "\n"
               "\n"
               "mov r15, r14\n"
               "adcx r15, [ rsp + 0xb0 ]\n"
               "adcx r12, [ rsp + 0xa8 ]\n"
               "\n"
               "\n"
               "mov r14, r10\n"
               "add r14, [ rsp + 0x60 ]\n"
               "adcx r8, [ rsp + 0x58 ]\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r13, r15\n"
               "adox r12, [ rsp + 0x178 ]\n"
               "\n"
               "\n"
               "mov r10, r14\n"
               "adcx r10, [ rsp + 0x50 ]\n"
               "adcx r8, [ rsp + 0x48 ]\n"
               "mov r15, r13\n"
               "shrd r15, r12, 0x34\n"
               "shr r12, 0x34\n"
               "\n"
               "\n"
               "mov r14, r9\n"
               "xor rdx, rdx\n"
               "adox r14, [ rsp + 0xf0 ]\n"
               "adox r11, [ rsp + 0xe8 ]\n"
               "mov r9, 0xfffffffffffff \n"
               "and r13, r9\n"
               "\n"
               "\n"
               "mov r9, r14\n"
               "adox r9, [ rsp + 0x40 ]\n"
               "adox r11, [ rsp + 0x38 ]\n"
               "\n"
               "\n"
               "mov r14, r9\n"
               "adcx r14, [ rsp + 0x160 ]\n"
               "adcx r11, [ rsp + 0x148 ]\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox rdi, r14\n"
               "adox r11, rcx\n"
               "\n"
               "\n"
               "adcx r15, rdi\n"
               "adcx r11, r12\n"
               "mov rcx, 0x30 \n"
               "bzhi r12, r15, rcx\n"
               "mov r9, r15\n"
               "shr r9, 0x30\n"
               "shrd r15, r11, 0x34\n"
               "mov r14, 0x34\n"
               "sarx r14, r11,r14\n"
               "\n"
               "\n"
               "add r15, r10\n"
               "adcx r8, r14\n"
               "mov r10, 0xf \n"
               "and r9, r10\n"
               "mov rdi, r15\n"
               "shrd r15, r8, 0x34\n"
               "mov r11, 0x34\n"
               "sarx r11, r8, r11\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r15, rbp\n"
               "adox rbx, r11\n"
               "mov rbp, 0x34 \n"
               "bzhi r14, r15, rbp\n"
               "shrd r15, rbx, 0x34\n"
               "mov r8, 0x34\n"
               "sarx r8, rbx, r8\n"
               "mov r11, 0x1000003d10 \n"
               "mov rdx, r11\n"
               "mulx rbx, r11, r14\n"
               "\n"
               "\n"
               "add r11, [ rsp + 0x170 ]\n"
               "adcx rbx, [ rsp + 0x168 ]\n"
               "\n"
               "\n"
               "add r15, [ rsp + 0x158 ]\n"
               "adcx r8, [ rsp + 0x150 ]\n"
               "imul r14, rdi, 0x10\n"
               "mov rdi, 0x40 \n"
               "bzhi r10, r15, rdi\n"
               "mov r15, 0xfffffffffffff0 \n"
               "and r14, r15\n"
               "or r14, r9\n"
               "mov r9, 0x1000003d1 \n"
               "mov rdx, r9\n"
               "mulx rdi, r9, r14\n"
               "\n"
               "\n"
               "mov r14, r9\n"
               "adox r14, [ rsp + 0x140 ]\n"
               "adox rdi, [ rsp + 0x138 ]\n"
               "mov r9, r14\n"
               "shrd r9, rdi, 0x34\n"
               "shr rdi, 0x34\n"
               "mov rdx, 0x1000003d10000 \n"
               "mulx rcx, r15, r8\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r13, r15\n"
               "mov r8, 0x0 \n"
               "adox rcx, r8\n"
               "\n"
               "\n"
               "adcx r9, r11\n"
               "adcx rbx, rdi\n"
               "mov r11, 0x1000003d10 \n"
               "mov rdx, r11\n"
               "mulx rdi, r11, r10\n"
               "bzhi r10, r14, rbp\n"
               "mov r15, r9\n"
               "shrd r15, rbx, 0x34\n"
               "shr rbx, 0x34\n"
               "\n"
               "\n"
               "add r11, [ rsp + 0x188 ]\n"
               "adcx rdi, [ rsp + 0x180 ]\n"
               "\n"
               "\n"
               "add r15, r11\n"
               "adcx rdi, rbx\n"
               "bzhi r14, r9, rbp\n"
               "mov rbx, [ rsp + 0x30 ]\n"
               "mov [ rbx + 0x8 ], r14\n"
               "mov r11, r15\n"
               "bzhi r9, r11, rbp\n"
               "shrd r15, rdi, 0x34\n"
               "shr rdi, 0x34\n"
               "mov [ rbx + 0x0 ], r10\n"
               "\n"
               "\n"
               "add r15, r13\n"
               "adcx rcx, rdi\n"
               "mov r13, r15\n"
               "bzhi r10, r13, rbp\n"
               "mov [ rbx + 0x10 ], r9\n"
               "shrd r15, rcx, 0x34\n"
               "shr rcx, 0x34\n"
               "mov [ rbx + 0x18 ], r10\n"
               "\n"
               "\n"
               "test al, al\n"
               "adox r12, r15\n"
               "adox rcx, r8\n"
               "mov [ rbx + 0x20 ], r12\n"
               "mov rbx, [ rsp + 0x0 ]\n"
               "mov rbp, [ rsp + 0x8 ]\n"
               "mov r12, [ rsp + 0x10 ]\n"
               "mov r13, [ rsp + 0x18 ]\n"
               "mov r14, [ rsp + 0x20 ]\n"
               "mov r15, [ rsp + 0x28 ]\n"
               "add rsp, 400\n"
               "ret\n"

  };
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  const int num_batches = 10;
  const int batch_size = 20;

  // INIT
  int arg_num_out = 1;
  int chunksize = 0;
  measuresuite_t ms = NULL;
  printf("strlen fa / fb %lu, %lu\n", strlen(fa), strlen(fb));
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
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