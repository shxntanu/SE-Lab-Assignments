section .data

global msg6,len6,scount,ncount,chacount,new,new_len

fname: db 'abc.txt',0

msg: db "File opened successfully",0x0A
len: equ $-msg

msg1: db "File closed successfully",0x0A
len1: equ $-msg1

msg2: db "Error in opening file",0x0A
len2: equ $-msg2

msg3: db "Spaces:",0x0A
len3: equ $-msg3

msg4: db "NewLines:",0x0A
len4: equ $-msg4

msg5: db "Enter character",0x0A
len5: equ $-msg5

msg6: db "No of occurances:",0x0A
len6: equ $-msg6

new: db "",0x0A
new_len: equ $-new

scount: db 0
ncount: db 0
ccount: db 0
chacount: db 0

section .bss

global cnt,cnt2,cnt3,buffer

fd: resb 17
buffer: resb 200
buf_len: resb 17
cnt: resb 2
cnt2: resb 2
cnt3: resb 2
cha: resb 2

%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

section .text
global _start
_start:

extern spaces,enters,occ

mov rax,2
mov rdi,fname
mov rsi,2
mov rdx,0777
syscall

mov qword[fd],rax
BT rax,63
jc next
scall 1,1,msg,len
jmp next2
next:
scall 1,1,msg2,len2


next2:
scall 0,[fd],buffer, 200
mov qword[buf_len],rax
mov qword[cnt],rax
mov qword[cnt2],rax
mov qword[cnt3],rax



scall 1,1,msg3,len3
call spaces

scall 1,1,msg4,len4
call enters

scall 1,1,msg5,len5
scall 0,1,cha,2
mov bl, byte[cha]
call occ
jmp exit



exit:
mov rax,60
mov rdi,0
syscall

;========== To Execute ==============

; nasm -f elf64 mp09_1.asm
; nasm -f elf64 mp09_2.asm
; ld -o mp09 mp09_1.o mp09_2.o
; ./mp09

; nasm -f elf64 mp09_1.asm && nasm -f elf64 mp09_2.asm && ld -o mp09 mp09_1.o mp09_2.o && ./mp09