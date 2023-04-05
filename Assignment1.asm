section .data
hello: db "Enter 5 hexadecimal digits: ", 0xA
len: equ $-hello
idk: db "The 5 numbers are: ", 0xA
len2: equ $-idk

cnt1: db 05h
cnt2: db 05h

section .bss
arr resb 85

section .text
global _start
_start:

mov rax, 01
mov rdx, 01
mov rsi, hello
mov rdx, len
syscall

mov r8, arr
l1: 
mov rax, 00
mov rdi, 00
mov rsi, r8
mov rdx, 17
syscall
add r8, 17
dec byte[cnt1]
JNZ l1

mov rax, 01
mov rdx, 01
mov rsi, idk
mov rdx, len2
syscall

mov r8, arr

l2:
mov rax, 01
mov rdi, 01
mov rsi, r8
mov rdx, 17
syscall

add r8, 17
dec byte[cnt2]
JNZ l2

mov rax, 60
mov rdi, 00
syscall
ret
