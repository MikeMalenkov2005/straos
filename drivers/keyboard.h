#include "../utils/types.h"
#include "../utils/structs.h"
#include "./vga_text.h"
#include ".port_io.h"
#include "../cpu/irq.h"

//TODO Implement GetChar!
char GetChar(unsigned char scancode)
{
	return 0;
}

void InstallHandler(void (*handler)(unsigned char scancode))
{
	
}

void KeyboardScanner(struct regs *r)
{
	unsigned char scancode = inb(0x60);
	//TODO
}

void init()
{
	irq_install_handler(1, KeyboardScanner);
}
