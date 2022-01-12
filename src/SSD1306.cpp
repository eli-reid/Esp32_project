#include "SSD1306.h"
#include "freertos/task.h"
ssdLCD::ssdLCD(I2CMaster *i2cPtr, I2C_address_t address):
_i2cPtr(i2cPtr), _address(address){
}

void ssdLCD::clrScreen(uint8_t color){
    const TickType_t Dly = 100/ portTICK_PERIOD_MS;
    // send buffer 4 times to = 128 width

    for(int i=0;i<8;i++){ 
        _i2cPtr->writeBufferAdd(SSD1306_PAGE_0 + i);//row
        _i2cPtr->writeBufferAdd(0x00); //col high byte
        _i2cPtr->writeBufferAdd(0x10); // col low byte
        _i2cPtr->write(SSD1306_CONTROL_CMD_STREAM, _address, true);
        for (int j=0;j<4;j++){
            _i2cPtr->fillWriteBuffer(color);
            _i2cPtr->write(SSD1306_CONTROL_DATA_STREAM,  _address, false);
             vTaskDelay(Dly);
        }

        vTaskDelay(Dly);
    }
}

void ssdLCD::printChar(char chr, uint8_t row, uint8_t col) {
    _i2cPtr->writeBufferAdd(SSD1306_PAGE_0 + row);
    _i2cPtr->writeBufferAdd((0x00) | (col & 0x0F));
    _i2cPtr->writeBufferAdd((0x10) | (col>>4));
    _i2cPtr->write(SSD1306_CONTROL_CMD_STREAM, _address, true);
    for(int i=0; i < 5; i++){
        _i2cPtr->writeBufferAdd(Font7x10[(chr - 32)][i]); 
    }
    _i2cPtr->writeBufferAdd(0x00,0x00,0x00);
    _i2cPtr->write(SSD1306_CONTROL_DATA_STREAM,_address, true);
  return;
}

void ssdLCD::printStr(char* str, uint8_t row, uint8_t col, bool bold){
    if(bold)
        printStr(str,(row + 4),col,false);
    
    for(int i=0; i < strlen(str);i++){
        printChar(str[i],row,col);
        col+=8;
        if(i==15){
            col=0;
            row++;
        }
    }
    return;
}

void ssdLCD::init(){
    _i2cPtr->writeBufferAdd(SSD1306_SET_MPLX,  SSD1306_HEIGHT - 1);
    _i2cPtr->writeBufferAdd(SSD1306_SET_OFFSET,0);
    _i2cPtr->writeBufferAdd(SSD1306_MEM_ADDR_MODE,0);
    _i2cPtr->writeBufferAdd(SSD1306_SET_START);
    _i2cPtr->writeBufferAdd(SSD1306_COL_NORM); 
    _i2cPtr->writeBufferAdd(SSD1306_ROW_NORM); 
    _i2cPtr->writeBufferAdd(0x20,0x02);//set page address mode
    _i2cPtr->writeBufferAdd(0x22,0,7); //set page range
    _i2cPtr->writeBufferAdd(0x21,0,127);//set col range
    _i2cPtr->writeBufferAdd(0xDA,0x00);
    _i2cPtr->writeBufferAdd(SSD1306_SET_CONTRAST,200);
    _i2cPtr->writeBufferAdd(SSD1306_DISPLAY_NORMAL );
    _i2cPtr->writeBufferAdd(SSD1306_OSC, 0x81 );
    _i2cPtr->writeBufferAdd(SSD1306_CHARGE_PUMP ,SSD1306_CHARGE_PUMP_ON);
    _i2cPtr->writeBufferAdd(SSD1306_CHARGE_PERIOD , 2);
    _i2cPtr->writeBufferAdd(SSD1306_DISPLAY_ON);  
    _i2cPtr->write(SSD1306_CONTROL_CMD_STREAM,_address, true);
    screenTest();
}
void ssdLCD::screenTest(){
        clrScreen(0xff);
        clrScreen(0x00);
}