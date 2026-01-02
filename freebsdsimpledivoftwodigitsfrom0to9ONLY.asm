section .data
msg db "demonitor is zero"
section .bss
NegmInt resb 1
OmarInt resb 1
Newline resb 1
section .text
global _start
_start:
mov rax , 3
mov rdi , 0
mov rsi , NegmInt
mov rdx , 1
syscall

mov rax , 3
mov rdi , 0
mov rsi , Newline
mov rdx , 1
syscall

mov rax , 3
mov rdi , 0
mov rsi , OmarInt
mov rdx , 1
syscall

movzx rax , byte [NegmInt]
movzx rbx , byte [OmarInt]
sub rax , '0'
sub rbx , '0'
cmp rbx , 0
je zero_label
jne not_zero_label
zero_label:
mov rax , 4
mov rdi  , 1
mov rsi , msg
mov rdx , 17
syscall

mov rax , 1
mov rdi , 0
syscall

not_zero_label:
xor rdx , rdx
idiv rbx
mov rdi , rax
mov rax , 1
syscall
