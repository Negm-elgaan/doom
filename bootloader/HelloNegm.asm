
org 0x7C00
section .data
section .text
global _start
_start:
mov ah , 0x0E
mov ax , 0
mov ds , ax
mov si , msg
nn:
Lodsb
int 0x10
cmp al , 0
jne nn
jmp $
msg db "Hello , Negm" , 0
times 510 - ($ - $$) db 0 
times 1 db 0x55
times 1 db 0xAA