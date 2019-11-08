//VEE 3.9K V0 2.7K GND
#ifndef LCD12864_H_
#define LCD12864_H_
#include "main.h"

#define LCD_RSTG	GPIOB
#define LCD_CS2G	GPIOB
#define LCD_CS1G	GPIOB
#define LCD_D7_G	GPIOB
#define LCD_D6_G	GPIOB
#define LCD_D5_G	GPIOB
#define LCD_D4_G	GPIOB
#define LCD_D3_G	GPIOA
#define LCD_D2_G	GPIOA
#define LCD_D1_G	GPIOA
#define LCD_D0_G	GPIOA
#define LCD_E__G	GPIOA
#define LCD_RW_G	GPIOA
#define LCD_RS_G	GPIOB

#define LCD_RSTP	GPIO_PIN_9
#define LCD_CS2P	GPIO_PIN_8
#define LCD_CS1P	GPIO_PIN_7
#define LCD_D7_P	GPIO_PIN_6
#define LCD_D6_P	GPIO_PIN_5
#define LCD_D5_P	GPIO_PIN_4
#define LCD_D4_P	GPIO_PIN_3
#define LCD_D3_P	GPIO_PIN_15
#define LCD_D2_P	GPIO_PIN_12
#define LCD_D1_P	GPIO_PIN_11
#define LCD_D0_P	GPIO_PIN_10
#define LCD_E__P	GPIO_PIN_9
#define LCD_RW_P	GPIO_PIN_8
#define LCD_RS_P	GPIO_PIN_15

#define LCD_CMD_DSP 0x3E
#define LCD_CMD_SL	0xC0
#define LCD_CMD_XA	0xB8
#define LCD_CMD_YA	0x40

void lcdSetCS(uint8_t CS);

void lcdEnable(void);

void lcdDisable(void);

void lcdSetDataRead(void);

void lcdSetDataWrite(void);

uint8_t lcdRead(void);

uint8_t lcdReadSta(void);

void lcdWrite(uint8_t raw);

void lcdSendCMD(uint8_t cmd);

void lcdSendDAT(uint8_t dat);

uint8_t lcdReadDAT(void);

#endif
