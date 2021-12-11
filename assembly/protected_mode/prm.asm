use16
org 7c00h

base equ 0x7c00 ; address at which bios will load mbr

main:
;********************************************************************;
;*                         prepare registers                        *;
;********************************************************************;
cld            ; clear direction flag

mov ax, cs
mov ds, ax

;********************************************************************;
;*                           clear screen                           *;
;********************************************************************;
mov ax, 0x03
int 0x10

;********************************************************************;
;*                  copy data from floppy to RAM                    *;
;********************************************************************;
read:
mov ax, 0x1000
mov es, ax
xor bx, bx     ; destination to write to, in es:bx
mov ah, 0x2    ; select 'drive read' function
mov al, 0x5    ; number of sectors to read at a time
mov dl, 0x0    ; the external drive's id
mov cl, 0x2    ; the sector to start reading from
mov dh, 0x0    ; the head to read from
mov ch, 0x0    ; the cylinder number to read
int 0x13       ; drive services interrupt
jc read

; disables the interrupts
cli             ; clear Interrupt-Enable Flag

; disables Non-maskable interrupt, NMI
in al, 0x70     ; port 70h = 112
or al, 0x80
out 0x70, al

; unlock address line A20
in al, 0x92     ; input byte from port 92h = 146
or al, 2
out 0x92, al    ; output byte to port 92h = 146

;load gdt address in register GDTR
lgdt [gdt]

; switch to PM
mov eax, cr0
or al, 1
mov cr0, eax

; selector #1 - code descriptor in kernel :
; 0x08 = 0000000000001 00 0 ; first segment in gdt CODE_descr
; shift = 0x10000
jmp pword 0x0008:0x10000 ; jump to protected mode code

;********************************************************************;
;*                     global descriptor table                      *;
;********************************************************************;
align 8        ; align descriptor table for 8 bytes
gdt:    dw     gdt_size  ; GDT table
        dd     gdt
gdt_l:
            dw 0x0000
CODE_descr  db 0FFh,0FFh,00h,00h,00h,10011010b,11001111b,00h
DATA_descr  db 0FFh,0FFh,00h,00h,00h,10010010b,11001111b,00h
VIDEO_descr db 0FFh,0FFh,00h,80h,0Bh,10010010b,01000000b,00h
gdt_size db gdt_size - gdt_l   ; gdt size

x db (510 - x + main) dup (0)
db 055h, 0aah

;********************************************************************;
;*                   protected mode entry point                     *;
;********************************************************************;
use32
org 0x10000

pm_entry:
mov eax,0x10
mov es, ax
mov ds, ax
mov fs, ax
mov ss, ax           ; set segment registers
mov esp, base        ; initialize stack

mov edi, 0xB8000     ; write to video segment
mov esi, pm_message  ; succesfull
call writeline

hlt
jmp $                ; $ — current instruction address.

;********************************************************************;
;*                          functions                               *;
;********************************************************************;
writeline:
pusha
cld
writeline_l:
lodsb
cmp al, 0x0
jz writeline_end
stosb
mov al, 0x07
stosb
jmp writeline_l
writeline_end:
popa
ret
; end writeline_end  ------------

;********************************************************************;
;*                               data                               *;
;********************************************************************;
pm_message db 'Welocome to protected mode on x86!', 0
