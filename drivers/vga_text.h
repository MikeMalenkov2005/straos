#ifndef VGA_TEXT_H
#define VGA_TEXT_H

uint16_t GetCursor();
void SetCursorRaw(uint16_t pos);
void SetCursor(int x, int y);
void SetCharRaw(uint16_t pos, char chr);
void SetChar(int x, int y, char chr);
void SetColorRaw(uint16_t pos, uint8_t col);
void SetColor(int x, int y, uint8_t col);
void InverColorRaw(uint16_t pos);
void InvertColor(int x, int y);

#endif
