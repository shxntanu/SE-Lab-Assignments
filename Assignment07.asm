; ---------- QUESTION ----------

; Write X86/64 ALP to detect protected mode and display the values of GDTR, LDTR, IDTR, TR and MSW Registers. 
; Also identify CPU type using CPUID instruction.

; ---------- MACROS ----------

%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

; ----------- DATA -----------

section .data

    Prot db "Protected Mode : ",10
    Protlen equ $-Prot
    
    Real db "Real Mode : ",10
    Reallen equ $-Real
    
    msw db "MSW  : "
    mswlen equ $-msw
    
    gdtr db 10,"GDTR : "
    gdtrlen equ $-gdtr
    
    idt db 10,"IDTR : "
    idtlen equ $-idt
    
    tr db 10,"TR : "
    trlen equ $-tr
    
    ld db 10,"LDTR : "
    ldlen equ $-ld

; ----------- BSS -----------
    
section .bss
    gdt resb 8                      ; to hold the value of the base address of GDT
    gdtli resb 2                    ; to hold the value of the limit field of GDT
    msw1 resb 2                     ; to hold msw value
    temp resb 1                     ; to store the value of al register temporarily
    result1 resq 1      
    result2 resw 1
    idt1 resb 8                     ; to hold the value of the base addressm of IDT
    idtli resb 2                    ; to hold the value of the limit field of IDT
    ldt resb 2                      ; to hold ldtr value
    t_r resb 2                      ; to hold the tr value

; ----------- TEXT -----------

section .text
    global _start

_start:
    mov rsi,msw1
    smsw [rsi]
    mov ax,[rsi]
    bt ax,0                         ; If PE bit of MSW = 1 then it is protected mode
    jc next                         ; Print Protected Mode
    IO 1,1,Real,Reallen             ; Print Real Mode
    jmp z1

next: 
    IO 1,1,Prot,Protlen 

z1:
    IO 1,1,msw,mswlen               ; Display the contents of MSW (16 bit)
    mov ax,word[msw1]
    call display2 
    
    IO 1,1,gdtr,gdtrlen
    mov rsi,gdt
    sgdt [rsi]
    mov rax, qword[rsi]
    call display1                   ; Display the contents of GDTR (64 bit)
    
    mov rsi,gdtli
    mov ax,word[rsi]
    call display2                   ; Display the table limit of GDTR (16 bit)
    
    IO 1,1,ld,ldlen
    mov rsi,ldt
    sldt [rsi]
    mov rax, [ldt]
    call display2                   ; Display the contents of LDTR (16 bit)
    
    IO 1,1,idt,idtlen
    mov rsi,idt1
    sidt [rsi]
    mov rax, [idt1]
    call display1                   ; Display the contents of IDTR (64 bit)
    
    mov ax,[idtli]
    call display2                   ; Display the table limit of IDTR (16 bit)
    
    IO 1,1,tr,trlen
    mov rsi,t_r
    str [rsi]
    mov rax, [t_r]
    call display2                   ; Display the contents of TR (16 bit) 
    
    ; Exit System Call
    IO 60,0,0,0 

; ----------- PROCEDURES -----------
    
display1:

        mov bp,16                   ; To display 64 bit no
    up1:
        rol ax,4
        mov qword[result1],rax
        and al,0fh
        cmp al,09h
        jbe next1
        add al,07h
    next1:
        add al,30h
        mov byte[temp],al
        IO 1,1,temp,1
        mov rax,qword[result1]
        dec bp
        jnz up1
        ret

display2:  
                                    
        mov bp,4                    ; To display 16 bit no (same process as we have done earlier) 
    up2:
        rol ax,4
        mov word[result2],ax
        and al,0fh
        cmp al,09h
        jbe next2
        add al,07h
    next2:
        add al,30h
        mov byte[temp],al
        IO 1,1,temp,1
        mov ax,word[result2]
        dec bp
        jnz up2
        ret

; ----------- TO RUN -----------
    
; nasm -f elf64 <filename>.asm
; ld -o <filename> <filename>.o
; ./<filename>

; ----------- OUTPUT -----------

;Protected Mode : 
;MSW  : 0033
;GDTR : 007F007F007F007FFFFF
;LDTR : 0000
;IDTR : 0FFF0FFF0FFF0FFFFFFF
;TR : 0040
