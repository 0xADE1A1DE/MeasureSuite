SECTION .text
GLOBAL add_two_numbers
add_two_numbers:
; [rdi]= [rsi] + [rdx]
mov rax, [rsi]
add rax, [rdx]
mov [rdi], rax
ret
