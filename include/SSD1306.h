
#ifndef SSD1306_H
#define	SSD1306_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "i2c.h"
#include "SSD1306_dfs.h"
#include "fonts.h"
class ssdLCD{
private:
    I2CMaster *_i2cPtr;
    I2C_address_t _address;
    void _send();
public:
    ssdLCD(I2CMaster *i2cPtr, I2C_address_t address);
    ssdLCD();
    void init();
    void clrScreen(uint8_t color);
    void printChar(char chr, uint8_t row,uint8_t col);
    void printStr(char* str, uint8_t row,uint8_t col, bool bold);
    void screenTest();
 };

#ifdef	__cplusplus
}
#endif

#endif