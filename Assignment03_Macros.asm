; ---------- MACROS ----------

%macro IO 4
    mov rax, %1           ;system write call
    mov rdi, %2           ;standard output descriptor
    mov rsi, %3           ;source register where data is stored
    mov rdx, %4           ;size of output
    Syscall
%endmacro

%macro hex_ascii 2
    mov rcx, 02            ;counter
    mov rbp, %1            ;converted data stored here
    mov bl, %2             ;data stored to be be converted register

    %%label1:              ;hex to ascii conversion step 1
    rol bl, 04             ;rotate by 4 bits to exchange positions of the digits
    mov dl, bl             ;mov this rotated content to dl
    and dl, 0Fh            ;and with 0F(0000 1111) to clear the ten's place
    cmp dl, 09h            ;compare with 09 and add accordingly
    jbe %%label2
    add dl, 07h            ;if dl is greater than 09 add 37, else add only 30
    
    %%label2:              ;hex to ascii conversion step 2
    add dl, 30h        
    mov [rbp], dl          ;mov the converted ascii nos to data of rbp i.e storage variable
    inc rbp                ;increment the pointer to storage variable
    dec rcx                ;decrement counter
    jnz %%label1           ;do again if counter not 0
%endmacro

; ---------- DATA ----------

section .data
    arr db 11h ,  12h , 15h , 20h , 10h             ;static array of 5 elements
    M1 db "The given array is....." , 10
    L1 equ $-M1
    M2 db 10 , "The largest no in array is...." , 10
    L2 equ $-M2

; ---------- BSS ----------

section .bss
    ans resb 2                   ;a variable of 2 bytes 
    counter resb 1               ;a variable of 1 byte

; ---------- TEXT ----------

section .text
global _start
_start:
    IO 1,1,M1,L1

    mov byte[counter], 05         ;set counter to 5 as there are 5 nos in the array
    mov rsi, arr                  ;move arr base address to rsi

    label3:                       ;displaying the array elements in new line
    mov al, [rsi]                 ;mov data of rsi to al
    push rsi                      ;save register data into the stack
    hex_ascii ans,al              ;hex to ascii conversion of data in al and store it in ans variable
    IO 1,1,ans,2                  ;print the converted data
    mov byte[ans] , 10            ;store a nextline character in ans
    IO 1,1,ans,1                  ;print 1 character of ans
    pop rsi                       ;restore the top of the stack
    inc rsi                       ;increment rsi
    dec byte[counter]             ;decrement counter
    jnz label3                    ;jump to label3 if counter not 0
    
    mov rsi,  arr                 ;mov base address of arr to rsi
    mov al, 00h                   ;set al to 00h
    mov byte[counter] ,04         ;set counter to 4 as 4 comparisons
    
    start_compare:                ;start comparisons      
    cmp [rsi], al                 ;compare data of rsi with accumulator(al)
    jbe ahead                     ;if small or equal jump to label ahead
    mov al, [rsi]                 ;else move rsi contents to al
    
    ahead:                        ;iterate the array
    inc rsi                       ;increment rsi
    dec byte[counter]             ;decrement counter
    jnz start_compare             ;jump to comparison label if counter no 0
    
    IO 1,1,M2,L2 
    hex_ascii ans,al              ;do the hex to ascii conversion of accumulator contents and store in ans
    IO 1,1,ans,2                  ;print the ans
    
    mov rax, 60                   ;system exit call
    mov rdx, 0                    ;standard exit descriptor
    Syscall
