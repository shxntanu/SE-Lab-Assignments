; MACROS

%macro IO 4                           ; Macro for Input and Output
mov rax , %1
mov rdi , %2
mov rsi , %3
mov rdx , %4
syscall
%endmacro

%macro convert 2                      ; Macro for Hex to ASCII Conversion
cmp byte[%1], 9
jbe next%2
add byte[%1], 07H
next%2:
add byte[%1], 30H
%endmacro

; -----------------------------------------------

section .data

; array: dq 0x8023451234121619, 0x0214532459658452, 0x1234587965423157,0x8259631478932516, 0x8452136758963250, 0x1254698736521458, 0x6547893256987452, 0x5478963215489632, 0x3256987456321548, 0x8523697412583690
array: dq -64, -38, 66, 89, -90, 70, 33, -50, 29, 111
pos: db 0
neg: db 0
count: db 10
msg1: db 'Positive numbers:'
len1: equ $ - msg1
msg2: db 10,'Negative numbers:'
len2: equ $ - msg2

; -----------------------------------------------

section .bss

; -----------------------------------------------

section .text

global _start
_start:

mov rsi,array                       ; Store pointer of array's first index in rsi register

up:

mov rax, qword[rsi]                 ; Move content at current position of rsi in accumulator
CMP rax, 0
JGE positive                        ; If number is positive jump to positive label

negative:                           ; Else negative number
inc byte[neg]
add rsi,8
dec byte[count]
JNZ up

positive:
inc byte[pos]                       ; Negative Number
add rsi,8
dec byte[count]
JNZ up
jmp HtoA                            ; When counter hits zero, convert positive and negative counter to ASCII

HtoA:

convert pos,2
convert neg,3

IO 1, 1, msg1, len1
IO 1, 1, pos, 1
IO 1, 1, msg2,len2
IO 1, 1, neg,1

mov rax,60
mov rdi,1
syscall
