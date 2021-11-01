org 100h
            
main: 
; input param1
   lea si, param1
   call writeLine        
   lea di, param1_val
   call readLine 
   call newLine   
; input param2   
   lea si, param2
   call writeLine           
   lea di, param2_val
   call readLine
   call newLine   
; calc sum     
   call fun_add
; convert to ascii chars
   lea si, summ_val
   xor cx, cx
   call toStr
; show summ   
   lea si, summ
   call writeLine
   lea si, summ_val
   xor cx, cx   
   call writeLine
; exit
   call end
; end main prog

; functions ------------
writeLine:
    lodsb
    cmp al, 0xff
    jz writeLine_end
    mov ah, 0x0E
    int 10h
    jmp writeLine
writeLine_end:
    ret 
; end writeLine_end
        
; bx counter size input number
readLine:     
   mov ah, 0x0
   int 16h
   cmp al, 0xd ; enter eiiao aaiaa
   jz readln_end
   stosb
   call showKey
   jmp readLine
readln_end:
   ret 
; end readLine   

; show al
showKey:
   mov ah, 0xE
   int 10h
   ret
; end showKey

newLine:
    mov al, 0x0D
    call showKey
    mov al, 0xA
    call showKey
    ret
 ; end newLine

; add by bytes   
fun_add:
; prapare param 1    
   lea si, param1_val
   xor cx, cx
   call reverseStr
   lea si, param1_val
; convert to number by bytes
   xor cx, cx
   call toNumber
; prapare param 2   
   lea si, param2_val
   call reverseStr
   lea si, param2_val
; convert to number by bytes
   call toNumber
   
; main calculation   
   lea si, param1_val
   lea di, param2_val 
   xor cx, cx ; number counter
   xor bx, bx ; temp var 
; simple add - example
; ff + ff
;  1e - bh = 0x1 bl = 0xe
; 1e  - bh = 0x1 bl = 0xe 
; 1fe - bl = 0x1
fun_add_calc:
   xor ax, ax
   mov al, byte ptr [di]
   add al, byte ptr [si]
   
   add bl, al ;
   shl bx, 4  ; split byte
   
   mov ah, bh ; save higth half
   mov bh, 0
   shr bx, 4
   push bx
             
   shr ax, 8
   mov bx, ax      
         
   inc si
   inc di
   inc cx
   
   cmp byte ptr [di], 0xff
   jz fun_add_test_end
   cmp byte ptr [si], 0xff
   jnz fun_add_calc
   mov byte ptr [si], 0                                    
   jmp fun_add_calc
          
fun_add_test_end:
    mov al, byte ptr [di]
    cmp al, byte ptr [si]          
    jz fun_add_pre_end
    mov byte ptr [di], 0
    jmp fun_add_calc

fun_add_pre_end:
   cmp bx, 0
   jz fun_add_end
   push bx
   inc cx 
         
fun_add_end:   
   lea di, summ_val
fun_add_end_loop:
   pop ax   
   mov byte ptr [di], al
   inc di
   dec cx
   cmp cx, 0
   jnz fun_add_end_loop
   ret
 ; end fun_add

reverseStr:
    lodsb
    cmp al, 0xff
    jz reverseStr_back
    push ax
    inc cx
    jmp reverseStr
reverseStr_back:
    sub si, cx 
    mov di, si
    sub di, 1    
reverseStr_end:   
    pop ax
    mov byte ptr [di], al
    inc di
    dec cx
    cmp cx, 0
    jnz reverseStr_end
    ret
; end reverseStr

toNumber:
    mov di, si
toNumber_loop:
    lodsb
    cmp al, 0xff
    jz toNumber_end
    
    cmp     al, '0'
    jl      Lbl2
    cmp     al, '9'
    jg      Lbl2
    sub     ax, 0x30
    jmp     Lbl3
Lbl2:
     cmp     al, 'a'
     jl      Lbl4
     cmp     al, 'f'
     jg      Lbl4
     sub     ax, 0x57
     jmp     Lbl3
Lbl4:
     cmp     al, 'A'
     jl      Lbl5
     cmp     al, 'F'
     jg      Lbl5
     sub     ax, 0x37
     jmp     Lbl3
Lbl5:
    lea si, error_bad_input
    call writeLine
    call end

Lbl3:        
    mov byte ptr [di], al
    inc di
    jmp toNumber_loop
toNumber_end:
    ret 
; end toNumber

toStr:
    mov di, si
toStr_Loop:
    lodsb
    cmp al, 0xff
    jz toStr_end
       
    cmp     al, 0
    jl      toStr_Lbl2
    cmp     al, 9
    jg      toStr_Lbl2
    add     ax, 0x30
    jmp     toStr_Lbl3
toStr_Lbl2:
    cmp     al, 0xA
    jl      toStr_Lbl4
    cmp     al, 0xF
    jg      toStr_Lbl4
    add     ax, 0x37
    jmp     toStr_Lbl3
toStr_Lbl4:
    lea si, error_bad_input
    call writeLine
    call end

toStr_Lbl3:           
    mov byte ptr [di], al
    inc di
    jmp toStr_Loop 
toStr_end:
    ret
; end toStr

; end of prog
end:
    ret                             
           
; const strings                   
; 0x0D, 0xA, 0 
; new line, return carriage, FF terminate 
param1 db 'Slag1 = ', 0xff
param1_val db 10 DUP (0xff)

param2 db 'Slag2 = ', 0xff
param2_val db 10 DUP (0xff)

summ db 'Summa = ', 0xff
summ_val db 11 DUP (0xff)

error_big_num db 'Max number is FFFF. Input new value.', 0x0D, 0xA, 0xff
error_bad_input db 'Bad input value. Input only in hex.', 0x0D, 0xA, 0xff
error_bad_result db 'Bad resul value. Internal error!', 0x0D, 0xA, 0xff

ret
