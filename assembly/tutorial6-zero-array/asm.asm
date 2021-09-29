.code

; void ZeroArray(void* rcx, int edx)
; Set all bytes from *rcx to *rcx+edx to 0
ZeroArray proc
	cmp edx, 0		; check for 0 or less array size
	jle Finished

	cmp edx, 1		; if size is 1
	je SetFinalByte

	mov ax, 0		; set ax to 00
	mov r8d, edx	; save original count - 32 bits

	shr edx, 3		; halve the size because we're using ax, not al

MainLoop:
	mov qword ptr [rcx], rax	; Set 8 bytes to 0
	add rcx, 8				; move rcx to the next 8 bytes
	dec edx					; decrement our counter
	jnz MainLoop			; jump if we've more to set

	and r8d, 1
	jz Finished

SetFinalByte:
	mov byte ptr [rcx], 0	; qword to 0

Finished:
	ret
ZeroArray endp

end