org 0x7C00
section .text
global _start
_start:
mov ah , 0x0E
mov al , "O"
int 0x10
times 504 db 0
times 1 db 0x55
times 1 db 0xAA