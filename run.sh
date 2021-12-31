export PATH=$PATH:/usr/local/i386elfgcc/bin

DIR="./out/"
if [ ! -d "$DIR" ]; then
	mkdir out
	mkdir out/bin
fi

echo Boot:
nasm "boot/boot.asm" -f bin -o "out/bin/boot.bin" -i Bootloader
nasm "kernel/zeroes.asm" -f bin -o "out/bin/zeroes.bin"

echo Kernel:
nasm "kernel/kernel_entry.asm" -f elf -o "out/bin/kernel_entry.o" -i Kernel
i386-elf-gcc -ffreestanding -m32 -g -c "kernel/kernel.cpp" -o "out/bin/kernel.o" -I Kernel

echo Drivers:
i386-elf-gcc -ffreestanding -m32 -g -c "drivers/port_io.cpp" -o "out/bin/port_io.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "drivers/vga_text.cpp" -o "out/bin/vga_text.o" -I Drivers

echo CPU:
i386-elf-gcc -ffreestanding -m32 -g -c "cpu/idt.cpp" -o "out/bin/idt.o"
nasm "cpu/interrupt.asm" -f elf -o "out/bin/interrupt.o" -i CPU
i386-elf-gcc -ffreestanding -m32 -g -c "cpu/isr.cpp" -o "out/bin/isr.o" -I CPU
i386-elf-gcc -ffreestanding -m32 -g -c "cpu/irq.cpp" -o "out/bin/irq.o" -I CPU
i386-elf-gcc -ffreestanding -m32 -g -c "cpu/timer.cpp" -o "out/bin/timer.o" -I CPU

echo Linking:
i386-elf-ld -o "out/bin/full_kernel.bin" -Ttext 0x1000 "out/bin/kernel_entry.o" "out/bin/kernel.o" "out/bin/vga_text.o" "out/bin/port_io.o" "out/bin/idt.o" "out/bin/interrupt.o" "out/bin/isr.o" "out/bin/irq.o" "out/bin/timer.o" --oformat binary

cat "out/bin/boot.bin" "out/bin/full_kernel.bin" "out/bin/zeroes.bin"  > "out/OS.bin"

qemu-system-x86_64 -drive format=raw,file="out/OS.bin",index=0,if=floppy,  -m 128M
