#ifndef I2C_H
#define	I2C_H

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "i2c_dfs.h"
#ifdef	__cplusplus
extern "C" {
#endif

class I2CMaster
{
private:
    uint8_t _i2cPort;
    I2C_Buffer_t _writeBuffer{
        .Index=0,
        .Data={0x00},
        .size = I2C_BUFFER_SIZE
    };
    bool _bufLck = false;
    void _clearWriteBuffer();
public:
    I2CMaster(uint8_t i2c_port);
    ~I2CMaster();
    void write(I2C_address_t slaveAddress, bool ackCheckEnabled);
    void write(uint8_t command, I2C_address_t slaveAddress, bool ackCheckEnabled);
    void writeBufferAdd(uint8_t data1);
    void writeBufferAdd(uint8_t data1, uint8_t data2);
    void writeBufferAdd(uint8_t data1, uint8_t data2,  uint8_t data3);
    void fillWriteBuffer(u_int8_t fill);
    uint8_t getWriteBufferSize(){ return _writeBuffer.size; }
};

#ifdef	__cplusplus
}
#endif

#endif
