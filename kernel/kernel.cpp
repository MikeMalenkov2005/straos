#include "../utils/types.h"
#include "../drivers/vga_text.h"

extern "C" void main()
{
	uint16_t pos = 0;
	SetCharRaw(pos++, 'S');
	SetCharRaw(pos++, 't');
	SetCharRaw(pos++, 'r');
	SetCharRaw(pos++, 'a');
	SetCharRaw(pos++, 'O');
	SetCharRaw(pos++, 'S');
	SetCursorRaw(pos);
	return;
}
