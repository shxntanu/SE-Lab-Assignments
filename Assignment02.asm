; ---------- MACROS ----------

%macro print 2
mov  rax , 01  ; sys_write
mov  rdi , 01  ; stdout - file descriptor
mov  rsi , %1  ; address of string to print
mov  rdx , %2  ; no. of bytes to print
syscall
%endmacro

%macro read  2
mov  rax , 00  ; sys_read
mov  rdi , 00  ; stdin - file descriptor
mov  rsi , %1  ; address where bytes are to be stored
mov  rdx , %2  ; no. of bytes to read
syscall
%endmacro

%macro exit  0
mov  rax , 60   ; sys_exit
mov  rdx , 00   
syscall 
%endmacro

; ---------- DATA ----------

section .data
msg1  db  "Enter string: " , 0xA
len1  equ  $-msg1

; ---------- BSS ----------

section .bss
string resb  100   ; Allocate max. 100 bytes for the string
length resb  2     ; Length is printed in two bytes

; ---------- TEXT ----------

section .text
global _start
_start:

print msg1   , len1
read  string , 100

; length of input string is stored in al

dec  al                ; Decrement al to compensate for trailing null character
mov  bl  , al          ; Copy contents of al to bl
mov  rsi , length      ; mov 'length' base address to rsi
mov  rcx , 02h         ; reset counter to 0x02

hextoascii:
rol  bl  , 04          ; rotate left 4 times (i.e. swap nibbles)
mov  dl  , bl          ; copy byte from bl to dl
and  dl  , 0Fh         ; perform AND to 0x0F ( 0000 1111 in binary )
cmp  dl  , 09h         ; compare with 09h
jbe  copydigit         ; Jump to label 'next1' if result of cmp was below or equal
add  dl  , 07h         ; Add 07h if greater than 09h

copydigit:
add  dl  , 30h         ; Add 30h always
mov  [rsi]  ,  dl      ; copy byte from dl to location specified by rsi
inc  rsi               ; increment rsi index
dec  rcx               ; decrement counter
jnz  hextoascii        ; Go to 'up' hextoascii if rcx is not zero

print length , 02      ; Print the 'ans' array upto 2 bytes

exit
