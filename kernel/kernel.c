#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "./memory.h"
#include "../drivers/vga_text.h"

void main()
{
	SetCursorRaw(79);
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
	return;
}
