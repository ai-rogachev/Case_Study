extrn MyProc:proc	; Tell MASM there's an external
					; procedure that will be linked

.code

; Calling Convention - fastcall x64
; caller
; callee - subprocedure

; MyProc(int a, int b, int c, int d, int e, int f)
;								 <-------- rigth to left
; align to 64 bits

CallACPPProcedure proc
	sub rsp, 30h					; Allocate shadow space - 10h (5 and 6) +  20h = 32 bytes = 8 * 4
	mov ecx, 1						; Move 1st param
	mov edx, 2						; Move 2nd param
	mov r8d, 3						; Move 3rd param
	mov r9d, 4						; Move 4th param
	mov dword ptr [rsp + 20h], 5	; Move 5th param to stack
	mov dword ptr [rsp + 28h], 6	; Move 6th param to stack
	call MyProc						; Call proc in C++
	add rsp, 30h					; Restore the stack - deallocate shadow space
	ret
CallACPPProcedure endp

end