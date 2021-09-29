; mul - unsigned
; imul - signed
; div - unsigned
; idiv - signed

; mul [reg/mem] 
; imul [reg/mem]

; imul [reg], [reg/mem] - op1 = op1 * op2
; imul [reg], [reg/mem], [imm] - op1 = op2 * op3

; oper1		oper2		answer
; byte		al			ax
; word		ax			dx:ax
; dword		eax			edx:eax
; qword		rax			rdx:rax

; -----------------------------------------------

; div [reg/mem] 
; idiv [reg/mem] 

; x (dividend) / y (divisor) = quotient, remainder

; diviser		dividend	quotient	remainder
; byte			ax			al			ah
; word			dx:ax		ax			dx
; dword			edx:eax		eax			edx
; qword			rdx:rax		rax			rdx

.code
;int Multiply(int a, int b);
Multiply proc
	; mov eax, ecx	; b
	; imul edx		; a
	imul ecx, edx	; Multiply the operands
	mov eax, ecx	; Move the answer into eax to return
	ret
Multiply endp

; int Divide(int a ecx, int b edx);
; return a/b
; Dividing with 32 bit integers so 
; the implied dividend will be edx:eax, 64 bit pair
Divide proc
	; we need ot free edx
	mov r8d, edx	; r8d is now the divisor
	
	mov eax, ecx

	cdq				; Convert to sign extended, fills edx 
					; with sign bit of eax
	idiv r8d		; Prefome the division
	; The answer will be placed into eax
	ret
Divide endp


; int Remainder(int a, int b);
Remainder proc
	; we need ot free edx
	mov r8d, edx	; r8d is now the divisor
	; we need edx to be it's sign!
	mov eax, ecx	; move the dividend into eax

	cdq				; Convert to sign extended, fills edx 
					; with sign bit of eax
	idiv r8d		; Prefome the division
	; The remainder will be placed into edx 
	mov eax, edx	; chuck it into eax to return
	ret
Remainder endp

end