section .data

array: dq 0x8023451234121619, 0x0214532459658452, 0x1234587965423157,0x8259631478932516, 0x8452136758963250, 0x1254698736521458, 0x6547893256987452, 0x5478963215489632, 0x3256987456321548, 0x8523697412583690
pos: db 0
neg: db 0
count: db 10
msg1: db 'Positive numbers:'
len1: equ $ - msg1
msg2: db 10,'Negative numbers:'
len2: equ $ - msg2

section .bss

%macro print 2
mov rax,1
mov rdi,1
mov rsi,%1
mov rdx,%2
syscall
%endmacro

%macro convert 2
cmp byte[%1], 9
jbe next%2
add byte[%1],07H
next%2:
add byte[%1],30H
%endmacro

section .text

global _start
_start:

mov rsi,array

up:

mov rax,qword[rsi]
BT rax,63
jc next
inc byte[pos]
add rsi,8
dec byte[count]
JNZ up
jmp next1

next:

inc byte[neg]
add rsi,8
dec byte[count]
JNZ up

next1:

convert pos,2
convert neg,3

print msg1,len1
print pos,1
print msg2,len2
print neg,1

mov rax,60
mov rdi,1
syscall




