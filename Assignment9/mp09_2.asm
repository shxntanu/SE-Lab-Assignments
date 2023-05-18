%macro scall 4
    mov rax,%1
    mov rdi,%2
    mov rsi,%3
    mov rdx,%4
    syscall
%endmacro

section .data
    extern msg6,len6,scount,ncount,chacount,new,new_len

section .bss
    extern cnt,cnt2,cnt3,scall,buffer

section .text

global main2

main2:


global spaces,enters,occ



spaces:

mov rsi,buffer


up:

mov al, byte[rsi]

cmp al,20H

je next3

inc rsi

dec byte[cnt]

jnz up


jmp next4


next3:

inc rsi

inc byte[scount]

dec byte[cnt]

jnz up


next4:

add byte[scount], 30h

scall 1,1,scount, 2

scall 1,1,new,new_len
ret

enters:

mov rsi,buffer

up2:

mov al, byte[rsi]

cmp al,0AH

je next5

inc rsi

dec byte[cnt2]

jnz up2


jmp next6

next5:

inc rsi

inc byte[ncount]

dec byte[cnt2]

jnz up2


next6:

add byte[ncount], 30h

scall 1,1,ncount, 2

scall 1,1,new,new_len
ret



occ:

mov rsi,buffer

up3:

mov al, byte[rsi]

cmp al,bl


je next7

inc rsi

dec byte[cnt3]

jnz up3

jmp next8


next7:

inc rsi

inc byte[chacount]

dec byte[cnt3]

jnz up3


next8:

add byte[chacount], 30h

scall 1,1,msg6,len6

scall 1,1,chacount, 1

scall 1,1,new,new_len
ret