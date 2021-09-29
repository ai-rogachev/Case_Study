; Microsoft x64 calling convention
; https://en.wikipedia.org/wiki/X86_calling_conventions#Microsoft_x64_calling_convention

; That means RCX, RDX, R8, R9 for integer, struct or pointer arguments (in that order),
; and XMM0, XMM1, XMM2, XMM3 for floating point arguments. 
; Additional arguments are pushed onto the stack (right to left). 
; Integer return values (similar to x86) are returned in RAX if 64 bits or less.
; Floating point return values are returned in XMM0. 
; Parameters less than 64 bits long are not zero extended; 
; the high bits are not zeroed. 

; Args - integer, struct or pointer - RCX, RDX, R8, R9
; Args - floating point - XMM0, XMM1, XMM2, XMM3
; More then 4 -  pushed onto the stack (right to left)
; Return value - int - RAX
; Return value - float point - XMM0

.code
AsmAddInt proc
	; add [reg/mem], [reg, mem, inm]
	add rcx, rdx
	mov rax, rcx
	ret
AsmAddInt endp

AsmSub proc
	; sub [reg/mem], [reg, mem, inm]
	sub rcx, rdx
	mov rax, rcx
	ret
AsmSub endp

AsmNeg proc
	; neg [reg/mem]
	neg rcx
	mov rax, rcx
	ret
AsmNeg endp

end