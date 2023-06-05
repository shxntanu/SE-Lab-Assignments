; --------- QUESTION ---------

; Write X86/64 ALP to convert 4-digit Hex number into its equivalent BCD number 
; and 5- digit BCD number into its equivalent HEX number. 
; Make your program user friendly to accept the choice from user for: (a) HEX to BCD b) BCD to HEX (c) EXIT. 
; Display proper strings to prompt the user while accepting the 
; input and displaying the result. (Wherever necessary, use 64-bit registers)

; ---------- MACROS ----------

%macro IO 4
mov rax, %1
mov rdi, %2
mov rsi, %3
mov rdx, %4
syscall
%endmacro

; ---------- DATA ----------

section .data

arr dw 2710h,03E8H,0064h,000Ah,0001h                  ; arr: 10000, 1000, 100, 10, 1
cnt db 05                                             ; Counter for loop iterations
cnt1 db 05                                            ; Counter for another loop iterations

menu: db "MENU for conversion: ",10
      db "1. BCD to Hex",10
      db "2. Hex to BCD",10
      db "3. Exit",10
menulen equ $-menu

cho: db "Enter your choice: "
lenc equ $-cho

msg: db " ",10
len equ $-msg

msg1: db "Enter the number: "
len1 equ $-msg1

res1: db "Result: "
lres equ $-res1

; ---------- BSS ----------

section .bss

disparr resb 02                                       ; Buffer for displaying results
choice resb 02                                        ; Buffer for user's choice
num resb 03                                           ; Buffer for user's input number
no1 resb 02                                           ; Buffer for storing a value
no2 resb 02                                           ; Buffer for storing another value
t1 resb 02                                            ; Buffer for temporary storage
rem resb 01                                           ; Buffer for remainder
res resb 04                                           ; Buffer for the final result

; ---------- TEXT ----------

section .text

global _start
_start:

menu_label:
IO 1,1,menu,menulen                                   ; Display the menu
IO 1,1,cho,lenc                                       ; Prompt for user's choice

IO 0,0,choice,02                                      ; Read the user's choice
mov al, byte [choice]

cmp al, 31h                                           ; Compare user's choice to '1'
je bcd_hex                                            ; If equal, jump to bcd_hex

cmp al, 32h                                           ; Compare user's choice to '2'
je hex_bcd                                            ; If equal, jump to hex_bcd

cmp al, 33h                                           ; Compare user's choice to '3'
je exit                                               ; If equal, jump to exit

bcd_hex:
mov bx, 0000h                                         ; Initialize BX register to zero
mov [res], bx                                         ; Initialize [res] memory location to zero

IO 1,1,msg1,len1                                      ; Display "Enter the number"
mov rsi, arr                                          ; Load the address of 'arr' array into RSI
a3:
push rsi                                              ; Save RSI on the stack for later use
IO 0,0,num,01                                         ; Read a single digit from user's input and store it in [num]
call convert_hex                                      ; Convert the digit to hexadecimal (original number)
pop rsi                                               ; Restore RSI from the stack
mov bx, [rsi]                                         ; Load the value from [rsi] (array element) into BX
mul bx                                                ; Multiply AX by BX
add [res], ax                                         ; Add the result to [res]
add rsi, 02                                           ; Move to the next array element
dec byte [cnt]                                        ; Decrease the loop counter
jnz a3                                                ; Jump to 'a3' if counter is not zero

IO 1,1,res1,lres                                      ; Display "Result: "
mov ax, [res]                                         ; Load the final result into AX
call display_hex                                      ; Display the hexadecimal output
IO 1,1,msg,len                                        ; Display a new line
IO 0,0,num,01                                         ; Read a single digit from user's input (clearing the buffer)
jmp menu_label                                        ; Jump to 'menu_label' to display the menu again

hex_bcd:
IO 1,1,msg1,len1                                      ; Display "Enter the number"
IO 0,0,num,02                                         ; Read two digits from user's input
call convert                                          ; Convert the first digit to the original form
mov [no1], al                                         ; Store the converted value in [no1]

IO 0,0,num,03                                         ; Read the third digit from user's input
call convert                                          ; Convert the third digit to the original form
mov [no2], al                                         ; Store the converted value in [no2]

mov rsi, arr                                          ; Load the address of 'arr' array into RSI
mov ah, [no1]                                         ; Load the converted value of the first digit into AH
mov al, [no2]                                         ; Load the converted value of the third digit into AL

r2:
mov bx, [rsi]                                         ; Load the value from [rsi] (array element) into BX
mov dx, 0                                             ; Clear DX register
div bx                                                ; Divide AX by BX, quotient in AL, remainder in AH
mov [rem], dx                                         ; Store the remainder in [rem]
mov [t1], al                                          ; Store the quotient in [t1]

push rsi                                              ; Save RSI on the stack for later use
call display_bcd                                      ; Display the BCD output from [t1]
pop rsi                                               ; Restore RSI from the stack
mov ax, [rem]                                         ; Load the remainder from [rem] into AX
add rsi, 2                                            ; Move to the next array element
dec byte [cnt1]                                       ; Decrease the loop counter
jnz r2                                                ; Jump to 'r2' if counter is not zero

IO 1,1,msg,len                                        ; Display a new line
jmp menu_label                                        ; Jump to 'menu_label' to display the menu again

exit:
mov rax, 60                                           ; Exit system call number
mov rdi, 0                                            ; Exit with code 0
syscall

; ---------- PROCEDURES ----------

convert:
mov rsi, num                                          ; Load the address of 'num' buffer into RSI
mov al, [rsi]                                         ; Load the first digit from [num] into AL
cmp al, 39h                                           ; Compare AL to '9'
jle a1                                                ; If less than or equal, jump to 'a1'
sub al, 07h                                           ; Subtract 7 to adjust for letters (A-F)
a1:
sub al, 30h                                           ; Convert ASCII digit to numeric value
rol al, 04                                            ; Rotate the 4-bit value to the left
mov bl, al                                            ; Move the value to BL for later use
inc rsi                                               ; Move to the next digit in [num]

mov al, [rsi]                                         ; Load the second digit from [num] into AL
cmp al, 39h                                           ; Compare AL to '9'
jle a2                                                ; If less than or equal, jump to 'a2'
sub al, 07h                                           ; Subtract 7 to adjust for letters (A-F)
a2:
sub al, 30h                                           ; Convert ASCII digit to numeric value
add al, bl                                            ; Add the value from BL to AL
ret                                                   ; Return from the subroutine

display_hex:
mov rsi, disparr+03                                   ; Set RSI to the address where the result will be stored
mov rcx, 04                                           ; Set the loop counter to 4 (four hexadecimal digits)
l4:
mov rdx, 0                                            ; Clear RDX register
mov rbx, 10h                                          ; Set RBX to 16 (hexadecimal base)
div rbx                                               ; Divide RDX:RAX by RBX, quotient in RAX, remainder in RDX
cmp dl, 09h                                           ; Compare the remainder to '9'
jbe add30                                             ; If less than or equal, jump to 'add30'
add dl, 07h                                           ; Add 7 to adjust for letters (A-F)

add30:
add dl, 30h                                           ; Convert the value to ASCII character
mov [rsi], dl                                         ; Store the character in [rsi]
dec rsi                                               ; Move to the previous position in [rsi]
dec rcx                                               ; Decrease the loop counter
jnz l4                                                ; Jump to 'l4' if counter is not zero

mov rax, 1                                            ; Set RAX to 1 (file descriptor for standard output)
mov rdx, 1                                            ; Set RDX to 1 (length of the string to be displayed)
mov rsi, disparr                                      ; Load the address of the result string into RSI
mov rdx, 04                                           ; Set RDX to 4 (length of the result string)
syscall                                               ; Perform system call to display the result
ret                                                   ; Return from the subroutine

display_bcd:
mov al, [t1]                                          ; Load the BCD digit from [t1] into AL
add al, 30h                                           ; Convert the value to ASCII character
mov [t1], al                                          ; Store the character back in [t1]
IO 1,1,t1,01                                          ; Display the BCD digit
ret                                                   ; Return from the subroutine

convert_hex:
mov al, [num]                                         ; Load the ASCII digit from [num] into AL
sub al, 30h                                           ; Convert ASCII digit to numeric value
ret                                                   ; Return from the subroutine
