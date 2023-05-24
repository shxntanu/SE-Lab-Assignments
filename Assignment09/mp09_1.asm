; ---------- MACROS ----------

%macro IO 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

; ---------- DATA ----------

section .data

global msg6,len6,scount,ncount,chacount,new,new_len

fname: db 'abc.txt',0                       ; Define a filename variable 'abc.txt'

msg: db "File opened successfully",0x0A     ; Define a message string for successful file opening
len: equ $-msg                              ; Calculate the length of the message string

msg1: db "File closed successfully",0x0A    ; Define a message string for successful file closing
len1: equ $-msg1                            ; Calculate the length of the message string

msg2: db "Error in opening file",0x0A       ; Define a message string for error in file opening
len2: equ $-msg2                            ; Calculate the length of the message string

msg3: db "Spaces:",0x0A                     ; Define a message string for displaying spaces
len3: equ $-msg3                            ; Calculate the length of the message string

msg4: db "NewLines:",0x0A                   ; Define a message string for displaying newlines
len4: equ $-msg4                            ; Calculate the length of the message string

msg5: db "Enter character",0x0A             ; Define a message string for prompting user to enter a character
len5: equ $-msg5                            ; Calculate the length of the message string

msg6: db "No of occurrences:",0x0A          ; Define a message string for displaying the number of occurrences
len6: equ $-msg6                            ; Calculate the length of the message string

new: db "",0x0A                             ; Define an empty string for storing user input
new_len: equ $-new                          ; Calculate the length of the string

scount: db 0                                ; Variable for spaces count
ncount: db 0                                ; Variable for newlines count
ccount: db 0                                ; Variable for character count
chacount: db 0                              ; Variable for character occurrence count

; ---------- BSS ----------

section .bss

global cnt,cnt2,cnt3,buffer

fd: resb 17                                 ; Reserve memory for file descriptor
buffer: resb 200                            ; Reserve memory for buffer to read file contents
buf_len: resb 17                            ; Reserve memory for buffer length

cnt: resb 2                                 ; Reserve memory for counting variables
cnt2: resb 2
cnt3: resb 2

cha: resb 2                                 ; Reserve memory for user input character

; ---------- TEXT ----------

section .text
global _start
_start:

extern spaces,enters,occ

mov rax,2                                   ; Open the file 'abc.txt' in read-only mode
mov rdi,fname
mov rsi,2
mov rdx,0777
syscall

mov qword[fd],rax

BT rax,63                                   ; Check if the file descriptor is negative (error occurred during opening)
jc next
IO 1,1,msg,len                           ; Print the success message for file opening
jmp next2
next:
IO 1,1,msg2,len2                         ; Print the error message for file opening

next2:                                      ; Read the contents of the file into the buffer
IO 0,[fd],buffer, 200

mov qword[buf_len],rax                      ; Store the length of the buffer

mov qword[cnt],rax                          ; Initialize counting variables with the buffer length
mov qword[cnt2],rax
mov qword[cnt3],rax

IO 1,1,msg3,len3                         ; Print the message for spaces

call spaces                                 ; Call the 'spaces' function to count the number of spaces in the buffer

IO 1,1,msg4,len4                         ; Print the message for newlines

call enters                                 ; Call the 'enters' function to count the number of newlines in the buffer

IO 1,1,msg5,len5                         ; Print the message for prompting user to enter a character
IO 0,1,cha,2                             ; Read a character from the user and store it in 'cha'

mov bl, byte[cha]                           ; Move the character to 'bl' register

call occ                                    ; Call the 'occ' function to count the number of occurrences of the character in the buffer

jmp exit                                    ; Jump to the exit label

exit:                                       ; Exit the program
mov rax,60
mov rdi,0
syscall

; ---------- To Execute ----------

; nasm -f elf64 mp09_1.asm
; nasm -f elf64 mp09_2.asm
; ld -o mp09 mp09_1.o mp09_2.o
; ./mp09

; nasm -f elf64 mp09_1.asm && nasm -f elf64 mp09_2.asm && ld -o mp09 mp09_1.o mp09_2.o && ./mp09
