#include <stdint.h>
#include <stddef.h>
#include "./port_io.h"
#include "../cpu/irq.h"

//TODO Implement GetChar!
char GetChar(uint8_t scancode)
{
	return 0;
}

void (*KEYBOARD_HANDLER)(uint8_t scancode) = NULL;

void KeyboardScanner(struct regs *r)
{
	uint8_t scancode = inb(0x60);
	KEYBOARD_HANDLER(scancode);
}

void InstallKeyboardHandler(void (*handler)(uint8_t scancode))
{
	irq_install_handler(1, KeyboardScanner);
	KEYBOARD_HANDLER = handler;
}
