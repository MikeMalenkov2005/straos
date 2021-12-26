export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "boot.asm" -f bin -o "out/boot.bin"
nasm "kernel_entry.asm" -f elf -o "out/kernel_entry.o"
i386-elf-gcc -ffreestanding -m32 -g -c "kernel.cpp" -o "out/kernel.o"
nasm "zeroes.asm" -f bin -o "out/zeroes.bin"

i386-elf-ld -o "out/full_kernel.bin" -Ttext 0x1000 "out/kernel_entry.o" "out/kernel.o" --oformat binary

cat "out/boot.bin" "out/full_kernel.bin" "out/zeroes.bin"  > "out/OS.bin"

qemu-system-x86_64 -drive format=raw,file="out/OS.bin",index=0,if=floppy,  -m 128M
