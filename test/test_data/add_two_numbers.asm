SECTION .text
GLOBAL add_two_numbers
add_two_numbers:
mov rax, [rsi]
add rax, [rdx]
mov [rdi],rax
ret
