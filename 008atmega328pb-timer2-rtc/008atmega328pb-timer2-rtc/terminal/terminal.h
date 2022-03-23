#ifndef TERMINAL_H_
#define TERMINAL_H_


void terminal_init();
void terminal_printChar(char c);
void terminal_printString(char* string);
void terminal_printFmt(const char* fmt, ...);

#endif /* TERMINAL_H_ */