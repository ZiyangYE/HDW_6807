#include "lcd_user.h"
#include "f7_11.h"
#include "f7_10.h"

uint8_t fulldata[14];
uint8_t zerodata[14];

void WriteBlock(uint8_t block,uint8_t* data){
	uint8_t index = 0;
	if(block==9){
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+0);
		lcdSendCMD(LCD_CMD_YA+63);
		lcdSendDAT(data[index++]);
		
		lcdSetCS(2);
		lcdSendCMD(LCD_CMD_XA+0);
		lcdSendCMD(LCD_CMD_YA+0);
		for(uint8_t u=0;u<6;u++)
			lcdSendDAT(data[index++]);
		
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+1);
		lcdSendCMD(LCD_CMD_YA+63);
		lcdSendDAT(data[index++]);
		
		lcdSetCS(2);
		lcdSendCMD(LCD_CMD_XA+1);
		lcdSendCMD(LCD_CMD_YA+0);
		for(uint8_t u=0;u<6;u++)
			lcdSendDAT(data[index++]);
			
	}else
	if(block==25){
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+4);
		lcdSendCMD(LCD_CMD_YA+63);
		lcdSendDAT(data[index++]);
		
		lcdSetCS(2);
		lcdSendCMD(LCD_CMD_XA+4);
		lcdSendCMD(LCD_CMD_YA+0);
		for(uint8_t u=0;u<6;u++)
			lcdSendDAT(data[index++]);
		
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+5);
		lcdSendCMD(LCD_CMD_YA+63);
		lcdSendDAT(data[index++]);
		
		lcdSetCS(2);
		lcdSendCMD(LCD_CMD_XA+5);
		lcdSendCMD(LCD_CMD_YA+0);
		for(uint8_t u=0;u<6;u++)
			lcdSendDAT(data[index++]);
			
	}else
	if(block<9){                             
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+0);
		lcdSendCMD(LCD_CMD_YA+block*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);

		lcdSendCMD(LCD_CMD_XA+1);
		lcdSendCMD(LCD_CMD_YA+block*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);
		
	}else
	if(block<16){
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+2);
		lcdSendCMD(LCD_CMD_YA+(block-10)*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);

		lcdSendCMD(LCD_CMD_XA+3);
		lcdSendCMD(LCD_CMD_YA+(block-10)*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);
		
	}else{
		lcdSetCS(1);
		lcdSendCMD(LCD_CMD_XA+4);
		lcdSendCMD(LCD_CMD_YA+(block-16)*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);

		lcdSendCMD(LCD_CMD_XA+5);
		lcdSendCMD(LCD_CMD_YA+(block-16)*7);
		for(uint8_t u=0;u<7;u++)
			lcdSendDAT(data[index++]);
		
	}
}

void LCDInit(void){
	for(int i=0;i<14;i++){
		fulldata[i]=0xFF;
		zerodata[i]=0x00;
	}
	lcdDisable();
	lcdEnable();
	for(int i=0;i<26;i++)LCDFlush(i);
	lcdSetCS(1);
	lcdSendCMD(LCD_CMD_DSP+1);
	lcdSetCS(2);
	lcdSendCMD(LCD_CMD_DSP+1);
}

void LCDFlush(uint8_t block){
	WriteBlock(block,zerodata);
	return;
}

void LCDFull(uint8_t block){
	WriteBlock(block,fulldata);
	return;
}

uint8_t* LCDGenData(char c,uint8_t size){
	if(size==10){
		return &F7_10[c*14];
	}else
	if(size==11)
		return &F7_11[c*14];
	else
		return zerodata;
}

void LCDWrite(uint8_t block,char c){
	if(block>9&&block<16){
		WriteBlock(block,LCDGenData(c,10));
	}else{
		WriteBlock(block,LCDGenData(c,11));
	}
}
void LCDPrint(uint8_t line,char* str,uint8_t len){
	if(line == 0){
		if(len>10)len=10;
		for(uint8_t i=0;i<len;i++)
			LCDWrite(0+i,str[i]);
	}
	if(line == 1){
		if(len>6)len=6;
		for(uint8_t i=0;i<len;i++)
			LCDWrite(10+i,str[i]);
	}
	if(line == 2){
		if(len>10)len=10;
		for(uint8_t i=0;i<len;i++)
			LCDWrite(16+i,str[i]);
	}
}
