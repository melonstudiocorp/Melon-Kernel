; DO NOT TOUCH THIS FILE, IF YOU TOUCH THIS YOUR "OS" DONT STARTED!!!

BITS 32
ALIGN 4

section .multiboot
global multiboot_header
multiboot_header:
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)