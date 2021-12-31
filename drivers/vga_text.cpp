#include "../utils/types.h"
#include "./port_io.h"

#define	VIDEO_MEMORY	(char*)0xB8000
#define	VGA_WIDTH	80

uint16_t cursor = 0;

uint16_t GetCursor()
{
	return cursor;
}

void SetCursorRaw(uint16_t pos)
{
	if(pos >= 0 && pos < 2000)
	{
		outb(0x3d4, 0x0f);
		outb(0x3d5, (uint8_t)(pos & 0xff));
		outb(0x3d4, 0x0e);
		outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
		cursor = pos;
	}
	return;
}

void SetCursor(int x, int y)
{
	uint16_t pos;
	pos = y * VGA_WIDTH + x;
	SetCursorRaw(pos);
	return;
}

void SetCharRaw(uint16_t pos, char chr)
{
	*(VIDEO_MEMORY + pos * 2) = chr;
	return;
}

void SetChar(int x, int y, char chr)
{
	uint16_t pos;
	pos = y * VGA_WIDTH + x;
	SetCharRaw(pos, chr);
	return;
}

void SetColorRaw(uint16_t pos, uint8_t col)
{
	*(VIDEO_MEMORY + pos * 2 + 1) = (char)col;
	return;
}

void SetColor(int x, int y, uint8_t col)
{
	uint16_t pos;
	pos = y * VGA_WIDTH + x;
	SetColorRaw(pos, col);
	return;
}

void InvertColorRaw(uint16_t pos)
{

	char* addr = VIDEO_MEMORY + pos * 2 + 1;
	char col = *addr;
	*addr = (char) ((col << 4) | (col >> 4));
	return;
}

void InvertColor(int x, int y)
{
	uint16_t pos;
	pos = y * VGA_WIDTH + x;
	InvertColorRaw(pos);
	return;
}
