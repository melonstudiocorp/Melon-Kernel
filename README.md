# 🍈 Melon-OS Kernel

Minimalist educational kernel/operating system written in **C** (with a bit of ASM(multiboot for grub)).  
Created for fun, learning low-level programming and writing a small kernel.

---

## ✨ Features
- ⌨️ Simple **Rain-Shell** with basic commands
- 🔄 `reboot` — restart the system
- 🧹 `clear` — clear the terminal
- ⭐ `stars` — secret (Starfall ASCII animation)
- 🌀 `spin` — another secret (spinner(somehow dont working correctly))
- ❓ `help` — list available commands
- 🔡 Custom `strcmp`, `strlen`, `strcpy` (no `string.h`, freestanding mode)

---

## 🛠️ Build
You will need:
- `i686-elf-gcc` (cross-compiler)
- `nasm`
- `qemu-system-i386` (or VirtualBox)

📂 Project structure(ITS OLD STRUCTURE!!)
MelonOS/
│── boot/         # Bootloader(just grub.cfg)
│── kernel/       # Kernel (C/ASM code)
│── fun/          # ASCII games (Starfall, Spinner)
│── shell/        # Rain-Shell(just initializing krnl.c)
│── README.md     # This file :)

Good Luck to Develop and playing with Kernel 🤗