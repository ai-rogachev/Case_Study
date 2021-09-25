; #if (APPLE)
;   #define FUNCTION_NAME(name) _##name
; #else
;   #define FUNCTION_NAME(name) name
; #endif
; 
; # Make symbols visible for linker
; #.globl FUNCTION_NAME(Capture)
; #.globl FUNCTION_NAME(JumpTo)
; 
; # Solution starts here
; # You need just two instructions: 'movq' and 'ret'
; 
; # FUNCTION_NAME(Capture):

	.code
Capture proc
	mov rax, [rsp]
	mov [rcx], rax
    ret

Capture endp

; #FUNCTION_NAME(JumpTo):
JumpTo proc
	mov rax, [rcx]
	mov [rsp], rax
    ret

JumpTo endp
	end

; AT&T
; FUNCTION_NAME(Capture):
;     # Your asm code goes here
;     movq (%rsp), %rax
;     movq %rax, (%rdi)
;     ret
; 
; FUNCTION_NAME(JumpTo):
;     # Your asm code goes here
;     movq (%rdi), %rax
;     movq %rax, (%rsp)
;     ret