org 7c00h

base equ 0x7c00    ; address at which bios will load mbr
dest equ 0x0600    ; address at which mbr should be copied
size equ 512       ; mbr sector size (default: 512 bytes)
max_pwd equ 4

main:
;********************************************************************;
;*                         prepare registers                        *;
;********************************************************************;

xor ax, ax         ; zero out the accumulator register
mov ss, ax         ; zero out stack segment register
mov sp, base       ; set stack pointer to base
mov es, ax         ; zero out extra segment register
mov ds, ax         ; zero out data segment register

;********************************************************************;
;*                  copy mbr to dest and jump there                 *;
;********************************************************************;

mov si, base       ; source index to copy code from
mov di, dest       ; destination index to copy code to
mov cx, size       ; number of bytes to be copied

cld                ; clear direction flag (move forward)
rep movsb          ; repeat movsb instruction for cx times

push ax            ; push continuation address to stack
push skip + dest   ;  to jump to skip in the copied code
retf               ; jump to copied code skipping part above

skip = $ - $$      ; go here in copied code

;********************************************************************;
;*                         enter password                           *;
;********************************************************************;

enter_pwd:
mov si, str_label ; show input label
call writeline

mov di, buffer    ; read client password
call readline

; calc password crc
call crc16_f
mov bx, [pwd16]

cmp ax, bx       ; compare crc
jz _ok
mov si, msgerror ; fail
call writeline
jmp _end

_ok:
mov si, msgok

mov ah, 0x2    ; select 'drive read' function
mov al, 0x1    ; number of sectors to read at a time
mov bx, 0x7c00 ; destination to write to, in es:bx
mov dl, 0x80   ; the external drive's id
mov cl, 0x1    ; the sector to start reading from
mov dh, 0x0    ; the head to read from
mov ch, 0x0    ; the cylinder number to read
int 0x13       ; drive services interrupt

jc _end        ; jump to error handler on cf set
jnc _success

_success:
mov  ax, 0x07c0 ; how segmentation works!
mov  ds, ax
mov  es, ax
jmp  fword 0x07c0:0x0000 ; jump to native mbr

_end:          ; end - reboot or load os
call enter_pwd

;********************************************************************;
;*                         functions                                *;
;********************************************************************;

writeline:
pusha
cld
writeline_l:
lodsb
cmp al, 0x0
jz writeline_end
mov ah, 0x0e
int 0x10
jmp writeline_l
writeline_end:
popa
ret
; end writeline_end  ------------

; bx counter size input number  ------------
readline:
mov ah, 0x0
int 0x16
cmp al, 0xd ; enter key
jz readln_end
stosb
jmp readline
readln_end:
ret
; end readline  ------------

;clrscr funciton  ------------
clrscr:
pusha
mov ah, 0x3
int 0x10
popa
ret
;end clrscr:  ------------

; compare string  ------------
cmpstr:
xor ax, ax
push cx
push si
push di

xor cx, cx
mov cx, [buf_size]

repz cmpsb
cmp cx, 0
jnz notequal
mov ax, 0
jmp exit

notequal:
mov ax, 1

exit:
pop di
pop si
pop cx
ret
; end cmpstr:  ------------


; crc16 function ------------
crc16_f:
push    ebx ecx edx esi
mov     esi, buffer
mov     cx, [buf_size]

xor     eax,eax
@@:
xor     ebx,ebx
mov     bl,al

lodsb
xor     bl,al

push    ecx
mov     ecx,8
crc16_nl:
shr     bx,1
jae     crc16_noxor
; magic number!
xor     bx,0a001h
crc16_noxor:
loop    crc16_nl
pop     ecx

xor     bl,ah
mov     ax,bx
loop    @b

pop     esi edx ecx ebx
ret
; end crc32 function ------------

int 19h ; reboot

;********************************************************************;
;*                               data                               *;
;********************************************************************;
buffer db max_pwd + 1 dup(0)
buf_size dw max_pwd

pwd16 dw  0x4d66
dflag  db 1

str_label db 'Enter password for unlock your computer: ', 0
msgerror db 'Wrong password', 0x0d, 0xa, 0
msgok db 'Ok', 0x0d, 0xa, 0x0

x db (510 - x + main) dup (0)
db 055h, 0aah                              