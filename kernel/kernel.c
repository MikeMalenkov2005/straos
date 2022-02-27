#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "./memory.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga_text.h"

void test_handler(uint8_t scancode)
{
	if (scancode == 'K') SetCursorRaw(GetCursor() - 1);
	if (scancode == 'M') SetCursorRaw(GetCursor() + 1);
	if (scancode == 'H') SetCursorRaw(GetCursor() - 80);
	if (scancode == 'P') SetCursorRaw(GetCursor() + 80);
	SetCharRaw(159, scancode & 0x7F);
}

void main()
{
	SetCursorRaw(159);
	ClearScreen(0, 0x0F);
	PrintStringPaw(0, " _____  _              _____  _____ ", 0x0F);
	PrintStringPaw(80, "|   __|| |_  ___  ___ |     ||   __|", 0x0F);
	PrintStringPaw(160, "|__   ||  _||  _|| .'||  |  ||__   |", 0x0F);
	PrintStringPaw(240, "|_____||_|  |_|  |__,||_____||_____|", 0x0F);
	InitHeap(0x50000, 0x20000);
	void* test = Allocate(200);
	if(test != NULL)
	{
		SetCharRaw(79, 'V');
		SetColorRaw(79, 0x02);
		Free(test);
	}
	else
	{
		SetCharRaw(79, 'X');
		SetColorRaw(79, 0x04);
	}
	idt_install();
	isrs_install();
	irq_install();
	asm volatile ("sti");
	timer_install();
	InstallKeyboardHandler(test_handler);
	return;
}
