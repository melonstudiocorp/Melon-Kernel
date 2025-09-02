#!/bin/bash
set -e

# Пути
KERNEL_DIR="kernel/core/krnl"
SHELL_DIR="kernel/core/shell"
BOOT_DIR="boot"
BIN_DIR="bin"
ISO_DIR="iso"
GAME_DIR="kernel/fun"

mkdir -p "$BIN_DIR"
mkdir -p "$ISO_DIR/boot/grub"

# compiling multiboot.asm for GRUB
nasm -f elf "$SHELL_DIR/multiboot/multiboot.asm" -o "$BIN_DIR/multiboot.o"

# Compiling krnl.c
i686-elf-gcc -ffreestanding -m32 -c "$KERNEL_DIR/krnl.c" -o "$BIN_DIR/krnl.o"

# Compiling shell.c
i686-elf-gcc -ffreestanding -m32 -c "$SHELL_DIR/shell.c" -o "$BIN_DIR/shell.o"

i686-elf-gcc -ffreestanding -m32 -c "$GAME_DIR/games.c" -o "$BIN_DIR/games.o"

# Link into shell.elf
i686-elf-ld -m elf_i386 -T "$SHELL_DIR/shelllink.ld" \
    -o "$BOOT_DIR/shell.elf" \
    "$BIN_DIR/multiboot.o" \
    "$BIN_DIR/krnl.o" \
    "$BIN_DIR/shell.o" \
    "$BIN_DIR/games.o"

echo "Build complete: $BOOT_DIR/shell.elf"

# --- Prepairing ISO via grub-mkrescue ---
# copy shell.elf and grub.cfg into ISO structure
mkdir -p "$ISO_DIR/boot/grub"
cp "$BOOT_DIR/shell.elf" "$ISO_DIR/boot/"
cp "$BOOT_DIR/grub/grub.cfg" "$ISO_DIR/boot/grub/"

# creating ISO with GRUB
grub-mkrescue -o MelonOS.iso "$ISO_DIR"

echo "ISO build complete: MelonOS.iso"