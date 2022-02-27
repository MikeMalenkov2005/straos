bin:
	if test ! -e bin; then mkdir bin; fi
all: bin
	nasm boot/boot.asm -f bin -o bin/boot.bin
	nasm kernel/kernel_entry.asm -f elf -o bin/kernel_entry.o
	gcc -m32 -fno-PIC -ffreestanding -c kernel/kernel.c -o bin/kernel.o
	gcc -m32 -fno-PIC -ffreestanding -c kernel/memory.c -o bin/memory.o
	gcc -m32 -fno-PIC -ffreestanding -c drivers/port_io.c -o bin/port_io.o
	gcc -m32 -fno-PIC -ffreestanding -c drivers/vga_text.c -o bin/vga_text.o
	gcc -m32 -fno-PIC -ffreestanding -c drivers/keyboard.c -o bin/keyboard.o
	gcc -m32 -fno-PIC -ffreestanding -c cpu/idt.c -o bin/idt.o
	gcc -m32 -fno-PIC -ffreestanding -c cpu/irq.c -o bin/irq.o
	gcc -m32 -fno-PIC -ffreestanding -c cpu/isr.c -o bin/isr.o
	gcc -m32 -fno-PIC -ffreestanding -c cpu/timer.c -o bin/timer.o
	ld -m elf_i386 -no-PIE -o bin/kernel.bin -Ttext 0x1000 bin/kernel_entry.o bin/kernel.o bin/memory.o bin/idt.o bin/irq.o bin/isr.o bin/port_io.o bin/vga_text.o bin/keyboard.o bin/timer.o --oformat binary
	cat bin/boot.bin bin/kernel.bin > OS.bin
clean: all
	rm -r bin
clear:
	if test -e bin; then rm -r bin; fi
	if test -e OS.bin; then rm OS.bin; fi
