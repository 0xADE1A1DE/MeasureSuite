global add_two_numbers

add_two_numbers:
	mov rax, [rsi]
	add rax, [rdx]

	add rax, [rdx]
	sub rax, [rdx]

	add rax, [rdx]
	sub rax, [rdx]

	add rax, [rdx]
	sub rax, [rdx]

	mov [rdi], rax
	ret
