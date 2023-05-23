; ---------- QUESTION ----------

; Write X86/64 ALP to perform overlapped block transfer with string
; specific instructions. Block containing data can be defined in the data
; segment

; ---------- MACROS ----------

%macro print 2
    mov rax, 1       			  ; System call number for write
    mov rdi, 1       			  ; File descriptor for standard output (stdout)
    mov rsi, %1      			  ; Address of the string to print
    mov rdx, %2      			  ; Length of the string
    syscall          			  ; Invoke the system call
%endmacro

; ---------- DATA ----------

section .data

    array db 10h, 20h, 30h, 40h, 50h      ; Array of bytes

    msg1: db 'Before overlapped :', 0xa   ; Message to print
    len1: equ $ - msg1                    ; Length of msg1

    msg2: db 'After overlapped :', 0xa    ; Message to print
    len2: equ $ - msg2                    ; Length of msg2

    msg3: db ' ', 0xa                     ; Message to print
    len3: equ $ - msg3                    ; Length of msg3

    msg4: db ' : '                        ; Message to print
    len4: equ $ - msg4                    ; Length of msg4

    count db 0                            ; Counter for loops
    count1 db 0                           ; Counter for HtoA1 conversion
    count2 db 0                           ; Counter for HtoA2 conversion
    count3 db 0                           ; Counter for loop10
    count4 db 0                           ; Counter for up10
    count5 db 0                           ; Counter for loop11
   
; ---------- BSS ----------
 
section .bss
    addr resb 16                          ; Buffer to store converted hexadecimal address
    num1 resb 2                           ; Buffer to store converted hexadecimal number
    
; ---------- TEXT ----------

section .text
global _start

_start:
    print msg1, len1                      ; Print "Before overlapped :" message

    xor rsi, rsi                          ; Clear rsi register (initialize array index)

    mov rsi, array                        ; Set rsi to the start of the array
    mov byte[count], 05                   ; Initialize count to 5 (array length)

up:
    mov rbx, rsi                          ; Store current array index in rbx for printing
    push rsi                              ; Push rsi onto the stack
    mov rdi, addr                         ; Set rdi to the address buffer
    call HtoA1                            ; Convert the hexadecimal address and print
    pop rsi                               ; Pop rsi from the stack

    mov dl, [rsi]                         ; Move the byte from the array to dl
    push rsi                              ; Push rsi onto the stack
    mov rdi, num1                         ; Set rdi to the num1 buffer
    call HtoA2                            ; Convert the hexadecimal number and print
    pop rsi                               ; Pop rsi from the stack

    inc rsi                               ; Increment rsi to point to the next byte in the array

    dec byte[count]                       ; Decrement count
    jnz up                                ; Jump to up if count is not zero (continue the loop)

    mov rsi, array                        ; Set rsi back to the start of the array
    mov rdi, array+0Ah                    ; Set rdi to the destination address for overlapped copying
    mov byte[count3], 05h                 ; Initialize count3 to 5

loop10:
    mov dl, 00h                           ; Move null byte to dl
    movsb                                 ; Move a byte from rsi to rdi (overlapped copying)
    dec byte[count3]                      ; Decrement count3
    jnz loop10                            ; Jump to loop10 if count3 is not zero (continue the loop)

    xor rsi, rsi                          ; Clear rsi register

    mov rsi, array+3h                     ; Set rsi to the third byte in the array
    mov rdi, array+0Ah                     ; Set rdi to the destination address for overlapped copying
    mov byte[count5], 05h                 ; Initialize count5 to 5

loop11:
    mov dl, byte[rdi]                     ; Move a byte from rdi to dl
    mov byte[rsi], dl                     ; Move the byte from dl to rsi (overlapped copying)
    inc rsi                               ; Increment rsi
    inc rdi                               ; Increment rdi
    dec byte[count5]                      ; Decrement count5
    jnz loop11                            ; Jump to loop11 if count5 is not zero (continue the loop)

    print msg2, len2                      ; Print "After overlapped :" message

    xor rsi, rsi                          ; Clear rsi register
    mov rsi, array                        ; Set rsi to the start of the array
    mov byte[count4], 08h                 ; Initialize count4 to 8

up10:
    mov rbx, rsi                          ; Store current array index in rbx for printing
    push rsi                              ; Push rsi onto the stack
    mov rdi, addr                         ; Set rdi to the address buffer
    call HtoA1                            ; Convert the hexadecimal address and print
    pop rsi                               ; Pop rsi from the stack

    mov dl, [rsi]                         ; Move the byte from the array to dl
    push rsi                              ; Push rsi onto the stack
    mov rdi, num1                         ; Set rdi to the num1 buffer
    call HtoA2                            ; Convert the hexadecimal number and print
    pop rsi                               ; Pop rsi from the stack

    inc rsi                               ; Increment rsi to point to the next byte in the array

    dec byte[count4]                      ; Decrement count4
    jnz up10                              ; Jump to up10 if count4 is not zero (continue the loop)

Exit:
    mov rax, 60                           ; Exit system call number
    xor rdi, rdi                          ; Exit with code 0
    syscall

; ---------- PROCEDURES ----------

HtoA1:
    mov byte[count1], 16                  ; Set count1 to 16 (number of hexadecimal digits)

dup1:
    rol rbx, 4                            ; Rotate the bits in rbx left by 4 (get the next hexadecimal digit)
    mov al, bl                            ; Move the least significant byte of rbx to al
    and al, 0fh                           ; Mask the upper nibble (clear the upper 4 bits)
    cmp al, 09                            ; Compare al with 9
    jg p3                                 ; Jump to p3 if al is greater than 9
    add al, 30h                           ; Convert the hexadecimal digit to ASCII (numeric digit)
    jmp p4                                ; Jump to p4

p3:
    add al, 37h                           ; Convert the hexadecimal digit to ASCII (letter)
    
p4:
    mov [rdi], al                         ; Store the ASCII digit in the address buffer
    inc rdi                               ; Increment rdi to point to the next position in the buffer
    dec byte[count1]                      ; Decrement count1
    jnz dup1                              ; Jump to dup1 if count1 is not zero (continue the loop)

    print addr, 16                        ; Print the converted hexadecimal address

    print msg4, len4                      ; Print " : " message

    ret                                   ; Return from the subroutine

HtoA2:
    mov byte[count2], 02                  ; Set count2 to 2 (number of hexadecimal digits)

dup2:
    rol dl, 4                             ; Rotate the bits in dl left by 4 (get the next hexadecimal digit)
    mov al, dl                            ; Move the least significant byte of dl to al
    and al, 0fh                           ; Mask the upper nibble (clear the upper 4 bits)
    cmp al, 09h                           ; Compare al with 9h
    jg p31                                ; Jump to p31 if al is greater than 9h
    add al, 30h                           ; Convert the hexadecimal digit to ASCII (numeric digit)
    jmp p41                               ; Jump to p41

p31:
    add al, 37h                           ; Convert the hexadecimal digit to ASCII (letter)
    
p41:
    mov [rdi], al                         ; Store the ASCII digit in the num1 buffer
    inc rdi                               ; Increment rdi to point to the next position in the buffer
    dec byte[count2]                      ; Decrement count2
    jnz dup2                              ; Jump to dup2 if count2 is not zero (continue the loop)

    print num1, 02                        ; Print the converted hexadecimal number

    print msg3, len3                      ; Print a newline character

    ret                                   ; Return from the subroutine
