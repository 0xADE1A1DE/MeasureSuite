export const width = 1;
export const numArgsIn = 1;
export const numArgsOut = 1;

// both of those function do
// void increment(long *d, const long *s) {
//     *d = *s + 1;
// }

// functionA is rather quick
// functionB determines '1' a bit more complicated.

export const functionA = [
  "function_A:",
  "    mov rax, [rsi]",
  "    inc rax",
  "    mov [rdi], rax",
  "    ret",
].join("\n");

export const functionB = [
  "function_B:",
  "    push r9",
  "    push r12",
  "    push rcx",
  "",
  "    mov r9, 0x1",
  "    mov r12, 0xa", // 10
  "",
  "    shl r12, 1", // 20
  "    lea r9, [r9 + r9] ", // 2
  "    lea r9, [r9 + r9] ", // 4
  "    lea r9, [r9 + r9] ", // 8
  "    lea r9, [r9 + r9] ", // 16
  "    lea r9, [r9 + r9] ", // 32
  "",
  "    lea r9, [r9 + r9] ", // 64
  "    lea r9, [r9 + r9] ", // 128
  "    lea r9, [r9 + r9] ", // 256
  "    lea r9, [r9 + r9] ", // 512
  "    lea r9, [r9 + r9] ", // 1024
  "",
  "    shr r12, 2", // 5
  "    mov rcx, r12",
  "    mov r12, 0x1", // 1
  "    sub r9, r12", // 1023
  "    and r9, rcx", // 5
  "    sub r9, 4", // 1
  "",
  "    mov rax, [rsi]",
  "    add rax, r9",
  "    mov [rdi], rax",
  "",
  "    pop rcx",
  "    pop r12",
  "    pop r9",
  "    ret",
].join("\n");
