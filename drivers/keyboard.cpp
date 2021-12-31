#ifndef KEYBOARD_H
#define KEYBOARD_H

char GetChar(unsigned char scancode);
void InstallHandler(void (*handler)(unsigned char scancode));
void init();

#endif
