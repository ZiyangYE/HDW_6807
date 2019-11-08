#ifndef LCD_USER_H_
#define LCD_USER_H_
#include "lcd12864.h"

void LCDInit(void);

void LCDFlush(uint8_t block);

void LCDFull(uint8_t block);

void LCDWrite(uint8_t block,char c);

void LCDPrint(uint8_t line,char* str,uint8_t len);

#endif
