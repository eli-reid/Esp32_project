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
typedef struct{

    const uint8_t size = I2C_BUFFER_SIZE;
    uint8_t Index = 0;
    uint8_t Data[I2C_BUFFER_SIZE];
    void fillBuf(uint8_t fdata);
    void reset();
    void add(uint8_t data);
    void add(uint8_t data1, uint8_t data2);
    void add(uint8_t data1, uint8_t data2,  uint8_t data3);

} I2C_Buffer_t;  

typedef unsigned int ack_t;
class I2CMaster
{
private:
    uint8_t _i2cPort;
    bool _bufLck = false;
 
public:
    I2CMaster(uint8_t i2c_port);
    ~I2CMaster();
    void write(I2C_address_t slaveAddress, uint8_t command, bool ackCheckEnabled);
    void write(I2C_address_t slaveAddress, uint8_t command, I2C_Buffer_t *buffer, bool ackCheckEnabled);
};

#ifdef	__cplusplus
}
#endif

#endif
