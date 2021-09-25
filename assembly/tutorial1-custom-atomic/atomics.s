;#if(APPLE)
;  #define FUNCTION_NAME(name) _##name
;#else
;  #define FUNCTION_NAME(name) name
;#endif

;.globl FUNCTION_NAME(AtomicLoad)
;.globl FUNCTION_NAME(AtomicStore)
;.globl FUNCTION_NAME(AtomicExchange)

;# Solution starts here

	.code
AtomicLoad proc
    mov [rcx], rax  
AtomicLoad endp

AtomicStore proc
    mov rdx, [rcx]
    ret
AtomicStore endp

AtomicExchange proc
    mov rax, [rcx]
    xchg [rcx], rdx
    ret
AtomicExchange endp
    end