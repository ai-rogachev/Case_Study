.code

; 1)
; store string = stos
; stos [mem] byte / word / double word / quadro word
; stos dword ptr [rcx]
; [rdi] - destination index
; [rsi] - source index

; mov rdi, rcx
; mov al, 'a'
; stosb  = 
;			mov byte ptr [rdi], al 
;			add rdi, 1
; 2)
; repeat prefix = rep stosb
; repeat while rcx > 0 / sub rcx, 1
;
; 3)
; scan string = scas
; scas [mem] b / w / d / q
; scasb  = 
;			cmp al, byte ptr [rdi] 
;			add rdi, 1
;  
; 
; 4) 
; repeat while zerp flag = 1 and rcx != 0 = repe /repz
; repeat while zerp flag = 0 and rcx != 0 = repne /repnz
; 
; 5)
; load string = lods
;  lods [mem] byte / word / double word / quadro word
;
; mov eax, dword ptr [rsi]
; add rsi, 4
; MyLoop:
;	lodsb
;	...
;	dec rcx
;	jnz MyLoop
; 6) 
; compare string = cmps
; cmps byte / word / double word / quadro word
; 
; cmp ptr [rsi] [rdi]
; add rsi, 1
; add rdi, 1
; 7) 
; move string = movs
; movs byte / word / double word / quadro word
; 
; lea rdi, arrA
; lea rsi, arrB
; 
; mov rcx, 100
; rep movsd

ToUpperCase proc
	ret
ToUpperCase endp

LoadE proc
	mov rdi, rcx
	mov al, 'e'
	stosb
	stosb
	stosb
	stosb
	stosb
	ret
LoadE endp

LoadE5 proc
	mov rdi, rcx
	mov al, 'e'
	mov rcx, 5
	rep stosb
	ret
LoadE5 endp

FoundChar proc

; while (rcx != 0) {
; 	dec rcx
; 	cmp al, byte prt [rdi]
; 	add rdi, 1
; 	jz breakLoop
; }
; breakLoop

	mov rdi, rcx
	mov al, dl
	mov rcx, 10
	repnz scasb
	mov rax, 10
	sub rax, rcx
	sub rax, 1
	ret
FoundChar endp

CompareString proc
	mov rdi, rcx
	mov rsi, rdx
	mov rcx, r8 
	repz cmpsb
	cmp rcx, 0
	jnz NotEqual
	mov rax, 1
	ret
NotEqual:
	mov rax, 0
	ret
CompareString endp


InitArray proc
	lea rdi, [rcx]
	lea rsi, [rdx]
	mov rcx, r8
	rep movsd
	ret
InitArray endp

end