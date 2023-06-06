; ---------- QUESTION ----------

; Write an x86/64 ALP to accept five 64 bit hexadecimal numbers from the user and store them in an array and display the accepted numbers.

; ---------- DATA ----------

section .data
hello: db "Enter 5 hexadecimal digits: ", 0xA   ; Message for user input
len: equ $-hello                                ; Length of the message

idk: db "The 5 numbers are: ", 0xA              ; Message for displaying the numbers
len2: equ $-idk                                 ; Length of the message

cnt1: db 05h                                    ; Counter for input loop
cnt2: db 05h                                    ; Counter for output loop

; ---------- BSS ----------

section .bss
arr resb 85                                     ; Buffer to store the input digits

; ---------- TEXT ----------

section .text
global _start
_start:

; Print "Enter 5 hexadecimal digits: " message
mov rax, 01
mov rdi, 01
mov rsi, hello
mov rdx, len
syscall

mov r8, arr                                     ; Set r8 to point to the start of the buffer

l1:
; Read 17 characters (16 digits + newline) from stdin into the buffer
mov rax, 00
mov rdi, 00
mov rsi, r8
mov rdx, 17
syscall

add r8, 17                                      ; Move to the next set of characters in the buffer
dec byte[cnt1]                                  ; Decrement the counter
JNZ l1                                          ; Jump to l1 if counter is not zero

; Print "The 5 numbers are: " message
mov rax, 01
mov rdi, 01
mov rsi, idk
mov rdx, len2
syscall

mov r8, arr                                     ; Set r8 to point to the start of the buffer

l2:
; Print 17 characters (16 digits + newline) from the buffer to stdout
mov rax, 01
mov rdi, 01
mov rsi, r8
mov rdx, 17
syscall

add r8, 17                                      ; Move to the next set of characters in the buffer
dec byte[cnt2]                                  ; Decrement the counter
JNZ l2                                          ; Jump to l2 if counter is not zero

; Exit the program
mov rax, 60                                     ; System call number for exit
mov rdi, 00                                     ; Exit status
syscall
ret                                             ; Return from the _start function
