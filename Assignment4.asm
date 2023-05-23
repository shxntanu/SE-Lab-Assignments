; --------- QUESTION ---------

; Write a switch case driven X86/64 ALP to perform 64-bit hexadecimal arithmetic 
; operations (+,-,*, /) using suitable macros. Define procedure for each operation

; --------- MACROS ---------

%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4 
    syscall        
%endmacro

; --------- DATA ---------

section .data

msg1: db "enter choice (1. +, 2. -, 3. *, 4. /, 5. Exit): ", 0xA
len1 equ $-msg1                               ; Calculate the length of the string

msg2: db "The 2 numbers are: ", 0xA
len2 equ $-msg2

n1: dq 15h                                    ; First number
n2: dq 5h                                     ; Second number

rem_msg: db "Remainder is: ", 0xA
len_rem equ $-rem_msg

quo_msg: db "Quotient is: ", 0xA
len_quo equ $-quo_msg

m_qou db "qoutient is "
m_qou_l equ $-m_qou

m_rem db "remainder is "
m_rem_l equ $-m_rem

; --------- BSS ---------

section .bss

choice resb 2                                 ; Choice input buffer
ans resb 16                                   ; Answer buffer

; --------- TEXT ---------

section .text

global _start
_start:

IO 1, 1, msg1, len1                           ; Print "enter choice" message
IO 0, 0, choice, 2                            ; Read user input into the choice buffer

cmp byte[choice], 34H                         ; Compare choice with '4'
JE divlbl                                     ; Jump to divlbl if equal

cmp byte[choice], 33H                         ; Compare choice with '3'
JE mullbl                                     ; Jump to mullbl if equal

cmp byte[choice], 32H                         ; Compare choice with '2'
JE sublbl                                     ; Jump to sublbl if equal

cmp byte[choice], 31H                         ; Compare choice with '1'
JE addlbl                                     ; Jump to addlbl if equal

sublbl:
mov rax, [n1]                                 ; Move the first number to rax
mov rbx, [n2]                                 ; Move the second number to rbx
sub rax, rbx                                  ; Subtract the second number from the first number
call HtoA                                     ; Convert the result to ASCII
JMP exit                                      ; Jump to exit

addlbl:
mov rax, [n1]                                 ; Move the first number to rax
mov rbx, [n2]                                 ; Move the second number to rbx
add rax, rbx                                  ; Add the first number and the second number
call HtoA                                     ; Convert the result to ASCII
JMP exit                                      ; Jump to exit

mullbl:
xor rdx, rdx                                  ; Clear the rdx register (high bits)
mov rax, [n1]                                 ; Move the first number to rax
mov rbx, [n2]                                 ; Move the second number to rbx
mul rbx                                       ; Multiply the first number and the second number (result in rdx:rax)
push rax                                      ; Save the least significant bits (lower 32 bits) of the result
mov rax, rdx                                  ; Move the most significant bits (higher 32 bits) to rax
xor rdx, rdx                                  ; Clear the rdx register (high bits)
call HtoA                                     ; Convert the result to ASCII
pop rax                                       ; Restore the least significant bits
call HtoA                                     ; Convert the result to ASCII
JMP exit                                      ; Jump to exit

divlbl:
xor rdx, rdx                                  ; Clear the rdx register (high bits)
mov rax, qword[n1]                            ; Move the first number to rax
mov ebx, dword[n2]                            ; Move the second number to ebx
div ebx                                       ; Divide the first number by the second number (quotient in rax, remainder in rdx)
push rax                                      ; Save the quotient
mov rax, rdx                                  ; Move the remainder to rax
IO 1, 1, rem_msg, len_rem                     ; Print "Remainder is: " message
call HtoA                                     ; Convert the remainder to ASCII
pop rax                                       ; Restore the quotient
IO 1, 1, quo_msg, len_quo                     ; Print "Quotient is: " message
call HtoA                                     ; Convert the quotient to ASCII
JMP exit                                      ; Jump to exit

exit:
mov rax, 60                                   ; System call number for exit
mov rdi, 0                                    ; Exit status
syscall                                       ; Invoke the exit system call

; --------- PROCEDURES ---------

HtoA:
mov rsi, ans                                  ; Store the base address of the answer buffer in rsi
mov rcx, 16h                                  ; Set the counter to 16 (number of hex digits)

hextoascii:
rol rax, 04                                   ; Rotate the bits of rax by 4 positions to the left
mov rdx, rax                                  ; Move the rotated value to rdx
and rdx, 0Fh                                  ; Mask the lower 4 bits of rdx to extract the last nibble
cmp rdx, 09h                                  ; Compare the nibble with 9
jbe copydigit                                 ; If the nibble is less than or equal to 9, jump to copydigit
add rdx, 07h                                  ; If the nibble is greater than 9, add 07h to convert it to ASCII character

copydigit:
add rdx, 30h                                  ; Add 30h to convert the nibble to ASCII character
mov [rsi], rdx                                ; Store the ASCII character in the corresponding address of rsi
inc rsi                                       ; Increment rsi to the next address
dec rcx                                       ; Decrement the counter
jnz hextoascii                                ; If the counter is not zero, jump to hextoascii

IO 1, 1, ans, 16                              ; Print the answer buffer as ASCII
ret
