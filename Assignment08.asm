; ---------- QUESTION ----------

; Write X86/64 ALP to perform overlapped block transfer with string
; specific instructions. Block containing data can be defined in the data
; segment.

; ---------- MACROS ----------

%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    Syscall
%endmacro

%macro hex_ascii 2
    mov rcx, 02                     ; counter
    mov rbp, %1                     ; converted data stored here
    mov bl, %2                      ; data stored to be be converted register

    %%label1:                       ; hex to ascii conversion step 1
    rol bl, 04                      ; rotate by 4 bits to exchange positions of the digits
    mov dl, bl                      ; mov this rotated content to dl
    and dl, 0Fh                     ; and with 0F(0000 1111) to clear the ten's place
    cmp dl, 09h                     ; compare with 09 and add accordingly
    jbe %%label2
    add dl, 07h                     ; if dl is greater than 09 add 37, else add only 30
    
    %%label2:                       ; hex to ascii conversion step 2
    add dl, 30h        
    mov [rbp], dl                   ; mov the converted ascii nos to data of rbp i.e storage variable
    inc rbp                         ; increment the pointer to storage variable
    dec rcx                         ; decrement counter
    jnz %%label1                    ; do again if counter not 0
%endmacro

%macro printarray 2                 
    mov rsi, %1                     ; move array base address to rsi
    mov byte[counter], %2           ; set counter to size of array

    %%label:                        ; displaying the array elements in new line
    mov al, [rsi]                   ; mov data of rsi to al
    push rsi                        ; save register data into the stack
    hex_ascii ans,al                ; hex to ascii conversion of data in al and store it in ans variable
    IO 1,1,ans,2                    ; print the converted data
    mov byte[ans] , 10              ; store a nextline character in ans
    IO 1,1,ans,1                    ; print 1 character of ans
    pop rsi                         ; restore the top of the stack
    inc rsi                         ; increment rsi
    dec byte[counter]               ; decrement counter
    jnz %%label                     ; jump till counter is not zero
%endmacro

%macro exit 0
    mov rax, 60
    mov rdx, 00
    Syscall
%endmacro

; ---------- DATA ----------

section .data
srcblk db 01h , 02h , 03h , 04h , 05h
dstblk db 00h , 00h , 00h , 00h , 00h
M1 db "Enter choice..." ,10, "1 ---> Without string" ,10, "2 ---> With string" ,10
L1 equ $-M1
M2 db "The contents of source block is.." , 10
L2 equ $-M2
M3 db "The contents of destination block intially.." , 10
L3 equ $-M3
M4 db "The contents of destination block after block transfer are.." , 10
L4 equ $-M4

; ---------- BSS ----------

section .bss
ans resb 2
counter resb 1

; ---------- TEXT ----------

section .text
global _start:
_start: 
    
    IO 1,1,M2,L2                    ; print the message
    
    printarray srcblk , 5           ; print the source array  

    IO 1,1,M3,L3                    ; print the message
    
    printarray dstblk , 5           ; print the initial destination array
    
    call blktsfwos                  ; call the procedure to perform block transfer without string instructions
    
    IO 1,1,M4,L4                    ; print the message
    
    printarray dstblk , 5           ; print the final destination array
    
    call blktsfws                   ; call the procedure to perform block transfer with string instructions
    
    IO 1,1,M4,L4                    ; print the message
    
    printarray dstblk , 5           ; print the final destination array
    
    exit

; ---------- PROCEDURES ----------

blktsfwos:                          ; block transfer without string instructions
    mov rsi, srcblk                 ; Move the source block address to rsi
    mov rdi, dstblk                 ; Move the destination block address to rdi
    mov byte[counter] ,05           ; Set the counter to 5
    
    again:
    mov bl, [rsi]                   ; Move the data of rsi to bl
    mov [rdi], bl                   ; Move the data of bl to rdi
    inc rsi                         ; Increment rsi
    inc rdi                         ; Increment rdi 
    dec byte[counter]               ; Decrement counter
    jnz again                       ; Jump till counter is not zero
    ret                                                 
    
blktsfws:                            ;block transfer with string instructions
    mov rsi, srcblk                  ; Move the source block address to rsi   
    mov rdi, dstblk                  ; Move the destination block address to rdi
    mov rcx, 05h                     ; Set the counter to 5
    
    cld                              ; Clear the direction flag
    rep movsb                        ; Move the data from rsi to rdi
    ret
