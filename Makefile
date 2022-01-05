all:
	mkdir bin
	nasm boot/boot.asm -f bin -o bin/boot.bin
	nasm kernel/kernel_entry.asm -f elf -o bin/kernel_entry.o
	gcc -m32 -fno-PIC -ffreestanding -c kernel/kernel.c -o bin/kernel.o
	gcc -m32 -fno-PIC -ffreestanding -c kernel/memory.c -o bin/memory.o
	gcc -m32 -fno-PIC -ffreestanding -c drivers/port_io.c -o bin/port_io.o
	gcc -m32 -fno-PIC -ffreestanding -c drivers/vga_text.c -o bin/vga_text.o
	ld -m elf_i386 -no-PIE -o bin/kernel.bin -Ttext 0x1000 bin/kernel_entry.o bin/kernel.o bin/memory.o bin/port_io.o bin/vga_text.o --oformat binary
	cat bin/boot.bin bin/kernel.bin > OS.bin
clean: all
	rm -r bin
