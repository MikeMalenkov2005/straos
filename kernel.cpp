//80×30
void pstr(int col, const char *str)
{
    volatile char *video = (volatile char*)0xB8000;
    while( *str != 0 )
    {
        *video++ = *str++;
        *video++ = col;
    }
}

extern "C" void main()
{
	pstr(0x07, "ABOBA");
	return;
}
