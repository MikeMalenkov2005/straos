#ifndef KEYBOARD_H
#define KEYBOARD_H

char GetChar(uint8_t scancode);
void InstallKeyboardHandler(void (*handler)(uint8_t scancode));

#endif
