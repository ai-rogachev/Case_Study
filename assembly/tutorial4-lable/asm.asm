.code

LoopTest proc
	mov ecx, 10

MainLoop:
	dec ecx
	jnz MainLoop ; zero flag will set to 1

	lea rax, MainLoop  ; load to rax - address label MainLoop
	lea rdx, [ecx + 1] ; load to rdx - calc address [ecx + 1]
	
	ret
LoopTest endp

JumpTest proc

	; Uncondtional Jump
	; jmp [reg/mem/label+offset]

	jmp MyLabel

	; Compare Instruction
	; cmp [reg/mem], [reg/mem/imm]
	mov ecx, 39
	mov ebx, 32
	cmp ecx, ebx
	jg MyLabel

	; Conditional Jumps
	; jxx [label+offset]
	; je/jz - Jump equal
	; jne/jnz - Jump if not equal
	; jl/jb - Jump if less
	; jle - Jump if less or equal
	; jg/ja - Jump if greate
	; jge - Jump if greater or equal

	mov eax, 90

MyLabel:
	ret

JumpTest endp


end