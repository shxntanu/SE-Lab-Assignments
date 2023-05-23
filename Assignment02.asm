; ---------- DATA ----------

section .data
msg: db "Largest Value: "	; Exit message
len equ $-msg
array: db 23h, 07h, 34h, 50h, 0xF8
cnt: db 04h

; ---------- BSS ----------

section .bss
ans resb 2

; ---------- TEXT ----------

section .text

global _start
_start:

mov r8, array		; Store pointer to first address of array in R8
mov al, byte[r8]	; Store first value of array in Accumulator
inc r8			; Move to the next address of array

compare:
mov bl, byte[r8]	; Store value at current address of array in bl
cmp bl, al		; Compare al and bl
JA copyvalue		; Jump if value of bl > al and copy value of bl in accumulator
JMP nextstep		; Else do nothing and move forward

copyvalue:
mov al, bl		; Copy contents of bl in al

nextstep:
inc r8			; Increment pointer to go to next location of array
dec byte[cnt]		; Decrement counter
JNZ compare		; Jump to compare block till entire array has been traversed

			; Now accumulator al has the largest number in the array

mov rsi, ans        	; Store pointer to base address of al in rsi
mov rcx, 02h        	; Reset counter to 0x02

hextoascii:
rol  al  , 04       	; Swap nibbles          
mov  dl  , al       	; Store rotated nibble in dl register
and  dl  , 0Fh      	; AND with 0F (Binary: 0000 1111) to get the last nibble
cmp  dl  , 09h      	; Check if it is a digit
jbe  copydigit      	; If it is a digit, jump to copy the digit
add  dl  , 07h      	; If it is a character, add 07h and 30h --> 37h

copydigit:
add  dl  , 30h      
mov  [rsi]  ,  dl   	; Store the nibble in the corresponding address of rsi
inc  rsi            	; Increment rsi to next address
dec  rcx            	; Decrement Counter
jnz  hextoascii

mov rax, 01		; Print exit message
mov rdi, 01
mov rsi, msg
mov rdx, len
syscall

mov rax, 01         	; Print Largest digit in hex
mov rdi, 01
mov rsi, ans
mov rdx, 03
syscall

mov rax, 60		; Exit syscall
mov rdi, 00
syscall
