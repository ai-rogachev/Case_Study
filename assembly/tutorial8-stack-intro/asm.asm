.code
; The Intel x86 and AMD64 / x86-64 series of processors use the little-endian format. 
; Solely big-endian architectures include the IBM z/Architecture, 
; Freescale ColdFire (which is Motorola 68000 series-based), Atmel AVR32,
; and OpenRISC. The IBM AIX and Oracle Solaris operating systems on 
; bi-endian Power ISA and SPARC run in big-endian mode

; This procedure demonstrates pushing and poping
; 16 and 64 bit word from the stack
PushAndPopTest proc
	mov ax, 1	; push 16 bit registars
	mov rcx, 2	; and 64 bit registars

	; The first push here make the stackc misalligned.
	; That is, RSP is not divisible by 4 (doesn't end
	; with 0, 4, 8 or C). This doesn't cause in the 
	; future when 32 bit backwards compatability is removed
	; this might crash the program.
	; Plus pushing and poping from a misalligned stack is slower.
	push ax		; Move AX to [RSP-2], RSP -= 2
	push rcx	; Move RCX to [RSP-8], RCP -= 8
	push 3		; Move 3 to [RSP-8], RSP -= 8

	pop rcx		; Move [RSP] to RCX, RSP += 8
	pop rcx		; Move [RSP] to RCX, RSP += 8

	; Make stack stable again!
	pop ax		; Move [RSP] to AX, RSP += 2

	; Example of pushing the Stack Pointer itself
	push rsp	; The stack pointer's pushed, then decremented.
	pop rax		; Clear all pushed items or you've 
				; corrupted the stack!

	; You can push and pop the flags register
	pushf
	popf
	ret
PushAndPopTest endp

BasicCallTest proc
	call TestFuction1		; Call function using lable

	lea rax, TestFuction1	; Call function using register
	call rax
	ret
BasicCallTest endp

; Change stack with call function
TestFuction1 proc
	ret
TestFuction1 endp


; This procedure illustrates the Call instruction
; It is nothing but PUSH for the IP but the value
; that is pushed is not the couuent IP but the IP
; of the following instruction!
CallTestFunction proc
	lea r8, Label1		; Load address of Label1
	lea r9, Label2		; Load address of Label2

Label1:
	call TestFuction	; call pushes the return
						; address, so here
						; it won;t push Label1
						; it will push Label2
Label2:
	ret
CallTestFunction endp

; This is the test function used to see what value is actualy
; pushed into the stack when use the 'call' instruction.
TestFuction proc
	ret
TestFuction endp

end