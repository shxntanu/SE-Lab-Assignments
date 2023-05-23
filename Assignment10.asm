; --------- MACROS ---------

%macro IO 4						; Macro for Input / Output
    mov rax, %1	
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

; --------- DATA ---------
section .data

msg1: db 0x0A, "Your number is ", 0x0A   		; Message to prompt for number input
len1: equ $ - msg1                     			; Length of msg1

msg2: db 0x0A, "Factorial is ", 0x0A   			; Message to display the factorial result
len2: equ $ - msg2                     			; Length of msg2

onee: db 0x0A, "Factorial is 00000001", 0x0A 		; Message for factorial 1 or 0
onelen: equ $ - onee                         		; Length of onee

count: db 0                         			; Counter for loop iteration
enter: db 0x0A                      			; New line character

; --------- BSS ---------
section .bss

num: resb 1                         			; Buffer to store the input number
fact: resb 8                        			; Buffer to store the factorial result
temp: resb 1                        			; Temporary buffer for conversion

; --------- TEXT ---------
section .text

global _start
_start:

pop rbx                             			; Pop unwanted command line args
pop rbx
pop rbx

mov al, byte[rbx]                   			; Required Argument
mov [num], al                       			; Store the input number in num buffer

IO 1, 1, msg1, len1                 			; Display "Your number is" message
IO 1, 1, num, 1                     			; Display the input number

cmp byte[num], 31h                  			; Compare the input number with '1'
je one                              			; Jump to one if equal
cmp byte[num], 30h                  			; Compare the input number with '0'
je one                              			; Jump to one if equal

mov dl, byte[num]                   			; Move the input number to dl (convert ASCII to decimal)
call A2H                            			; Convert ASCII to hexadecimal (dl contains the result)

xor rax, rax                        			; Clear rax register
xor rbx, rbx                        			; Clear rbx register
mov al, byte[num]                   			; Move the input number to al (decimal)

up1:
    push rax                        			; Preparing Stack
    inc byte[count]                 			; Increment count
    dec rax                         			; Decrement al (decrease the input number)
    cmp rax, 1                      			; Compare al with 1
    jne up1                         			; Jump to up1 if not equal

push rax                            			; Push rax onto the stack
xor rax, rax                        			; Clear rax register

pop rax                            			; Pop rax from the stack (contains the original input number)

facto:                             			; Recursive Multiplication
    pop rbx                         			; Pop rbx from the stack (contains the current value of al)
    mul rbx                         			; Multiply rax by rbx (accumulate the factorial result)
    dec byte[count]                 			; Decrement count
    jnz facto                       			; Jump to facto if count is not zero (continue the factorial calculation)

mov qword[fact], rax                			; Move the factorial result from rax to fact buffer

IO 1, 1, msg2, len2                 			; Display "Factorial is" message
call H2A                            			; Convert hexadecimal to ASCII and display the result

jmp exit                            			; Jump to exit

one:                               			; If Input is 1 or 0
IO 1, 1, onee, onelen               			; Display the message for factorial 1 or 0

jmp exit                            			; Jump to exit

; --------- PROCEDURES ---------

A2H:                               			; ASCII TO HEX
cmp dl, 39h                        			; Compare dl with '9'
jbe down                           			; Jump to down if below or equal
sub dl, 7h                         			; Adjust dl for letters 'A' to 'F'
down:
sub dl, 30h                        			; Convert ASCII to hexadecimal
mov [num], dl                      			; Store the result in num buffer
ret

H2A:                               			; HEX TO ASCII
mov rax, [fact]                    			; Move the factorial result from fact buffer to rax
mov byte[count], 8                			; Set count to 8

up:
    rol eax, 4                      			; Rotate left by 4 bits (get the next hexadecimal digit)
    mov dl, al                      			; Move the least significant byte of eax to dl
    and dl, 0Fh                     			; Mask the upper nibble (clear the upper 4 bits)
    cmp dl, 09h                     			; Compare dl with '9'
    jbe d1                          			; Jump to d1 if below or equal
    add dl, 07h                     			; Adjust dl for letters 'A' to 'F'
d1:
    add dl, 30h                     			; Convert the hexadecimal digit to ASCII
    mov [temp], dl                 			; Store the result in temp buffer
    push rax                        			; Push rax onto the stack
    IO 1, 1, temp, 1                			; Display the current digit
    pop rax                         			; Pop rax from the stack
    dec byte[count]                 			; Decrement count
    jnz up                          			; Jump to up if count is not zero (continue displaying digits)

IO 1, 1, enter, 1                   			; Display a new line
ret

exit:
mov rax, 60                        			; Exit system call
mov rdi, 0                         			; Exit with code 0
syscall
