; ---------- MACROS ----------

%macro IO 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

;===========================================
section .data
;===========================================

msg1:	db 0x0A,"Your number is  ",0x0A
len1:	equ $- msg1


msg2:	db 0x0A,"Factorial is  ",0x0A
len2: 	equ $- msg2

onee:   db 0x0A,"Factorial is 00000001",0x0A
onelen:	equ $- onee

count: 	db 0

enter:	db 0x0A

;===========================================
section .bss
;===========================================

num:	resb	1
fact:	resb	8

dispnum resb 16
result resb 4
temp resb 3

;===========================================
section .text
;===========================================

global _start;
_start:

	pop rbx						;POP UNWANTED COMMAND LINE ARGS
	pop rbx
	pop rbx

	mov al,byte[rbx]				;REQUIRED ARGUMENT
	mov [num],al

	IO 1,1,msg1,len1
	IO 1,1,num,1

	cmp byte[num],31h
	je one
	cmp byte[num],30h
	je one

	mov dl,byte[num]
	call A2H


	xor rax, rax
	xor rbx, rbx
	xor rdx, rdx

	mov al, [num]
	
	mov bl, 01h
	call factorial
	call display

	jmp Exit

	one:							;IF INPUT IS ONE or ZERO

	IO 1,1,onee,onelen

	jmp Exit
	
factorial:						;recursive procedure
    cmp rax, 01h
    je retcon1
    push rax			
    dec rax
    
    call factorial

    retcon:
        pop rbx
        mul ebx
        jmp endpr

    retcon1:						;if rax=1 return
        pop rbx
        jmp retcon		
    endpr:
	ret
	
display:					; procedure to convert hex to ascii
        mov rsi,dispnum+15
        xor rcx,rcx
        mov cl,16

    cont:
        xor rdx,rdx
        xor rbx,rbx
        mov bl,10h
        div ebx
        cmp dl,09h
        jbe skip
        add dl,07h
    skip:
        add dl,30h
        mov [rsi],dl
        dec rsi
        loop cont

        IO 1,1,dispnum,16

	ret


A2H:								;ASCII TO HEX

	cmp dl,39h
	jbe down
	sub dl,7h
	down:
	sub dl,30h
	mov [num],dl

	ret

H2A:						;HEX TO ASCII

	mov rax,[fact]
	mov byte[count],8

	up:
	rol eax,4
	mov dl,al
	and dl,0Fh
	cmp dl,09h
	jbe d1
	add dl,07h
	d1:
	add dl,30h
	mov [temp],dl
	push rax
	IO 1,1,temp,1
	pop rax
	dec byte[count]
	jnz up

	IO 1,1,enter,1
	ret

Exit:

	mov rax,60
	mov rdi,0
	syscall


