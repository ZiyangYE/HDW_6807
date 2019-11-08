#include "lcd12864.h"

void lcdDelay(void){
	//__NOP;
	for(volatile uint16_t i=0;i<16;i++);
	//HAL_Delay(1);
}

void lcdSetCS(uint8_t CS){
	if(CS>3)return;
	if(CS==0)return;
	HAL_GPIO_WritePin(LCD_CS1G,LCD_CS1P,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS2G,LCD_CS2P,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS==1?LCD_CS1G:LCD_CS2G,CS==1?LCD_CS1P:LCD_CS2P,GPIO_PIN_SET);
}

void lcdEnable(void){
	HAL_GPIO_WritePin(LCD_RSTG,LCD_RSTP,GPIO_PIN_SET);
}

void lcdDisable(void){
	HAL_GPIO_WritePin(LCD_RSTG,LCD_RSTP,GPIO_PIN_RESET);
}

void lcdSetDataRead(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

	GPIO_InitStruct.Pin = LCD_D0_P;
  HAL_GPIO_Init(LCD_D0_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D1_P;
  HAL_GPIO_Init(LCD_D1_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D2_P;
  HAL_GPIO_Init(LCD_D2_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D3_P;
  HAL_GPIO_Init(LCD_D3_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D4_P;
  HAL_GPIO_Init(LCD_D4_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D5_P;
  HAL_GPIO_Init(LCD_D5_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D6_P;
  HAL_GPIO_Init(LCD_D6_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D7_P;
  HAL_GPIO_Init(LCD_D7_G, &GPIO_InitStruct);
}

void lcdSetDataWrite(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	GPIO_InitStruct.Pin = LCD_D0_P;
  HAL_GPIO_Init(LCD_D0_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D1_P;
  HAL_GPIO_Init(LCD_D1_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D2_P;
  HAL_GPIO_Init(LCD_D2_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D3_P;
  HAL_GPIO_Init(LCD_D3_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D4_P;
  HAL_GPIO_Init(LCD_D4_G, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D5_P;
  HAL_GPIO_Init(LCD_D5_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D6_P;
  HAL_GPIO_Init(LCD_D6_G, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_D7_P;
  HAL_GPIO_Init(LCD_D7_G, &GPIO_InitStruct);
}

uint8_t lcdRead(void){
	uint8_t read=0;

	read|=(HAL_GPIO_ReadPin(LCD_D0_G,LCD_D0_P)<<0);
	read|=(HAL_GPIO_ReadPin(LCD_D1_G,LCD_D1_P)<<1);
	read|=(HAL_GPIO_ReadPin(LCD_D2_G,LCD_D2_P)<<2);
	read|=(HAL_GPIO_ReadPin(LCD_D3_G,LCD_D3_P)<<3);
	read|=(HAL_GPIO_ReadPin(LCD_D4_G,LCD_D4_P)<<4);
	read|=(HAL_GPIO_ReadPin(LCD_D5_G,LCD_D5_P)<<5);
	read|=(HAL_GPIO_ReadPin(LCD_D6_G,LCD_D6_P)<<6);
	read|=(HAL_GPIO_ReadPin(LCD_D7_G,LCD_D7_P)<<7);
	
	return read;
}

uint8_t lcdReadSta(void){
	uint8_t read=0;
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RS_G,LCD_RS_P,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdDelay();
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_SET);
	lcdDelay();
	
	read=lcdRead();
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
	
	return read;
}


void lcdWrite(uint8_t raw){
	HAL_GPIO_WritePin(LCD_D0_G,LCD_D0_P,raw&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D1_G,LCD_D1_P,raw&0x02?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D2_G,LCD_D2_P,raw&0x04?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D3_G,LCD_D3_P,raw&0x08?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D4_G,LCD_D4_P,raw&0x10?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_G,LCD_D5_P,raw&0x20?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_G,LCD_D6_P,raw&0x40?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_G,LCD_D7_P,raw&0x80?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void lcdSendCMD(uint8_t cmd){
	HAL_GPIO_WritePin(LCD_RS_G,LCD_RS_P,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
	
	lcdSetDataWrite();
	lcdDelay();
	lcdWrite(cmd);
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdDelay();
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_SET);
	lcdDelay();
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
}

void lcdSendDAT(uint8_t dat){
	HAL_GPIO_WritePin(LCD_RS_G,LCD_RS_P,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
	
	lcdSetDataWrite();
	lcdDelay();
	lcdWrite(dat);
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdDelay();
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_SET);
	lcdDelay();
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
}

uint8_t lcdReadDAT(void){
	uint8_t read=0;
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RS_G,LCD_RS_P,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdDelay();
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_SET);
	lcdDelay();
	
	read=lcdRead();
	
	HAL_GPIO_WritePin(LCD_E__G,LCD_E__P,GPIO_PIN_RESET);
	lcdSetDataRead();
	HAL_GPIO_WritePin(LCD_RW_G,LCD_RW_P,GPIO_PIN_RESET);
	
	return read;
}
