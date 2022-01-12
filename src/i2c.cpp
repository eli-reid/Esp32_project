#include "i2c.h"
I2CMaster::I2CMaster(uint8_t i2cPort): _i2cPort(i2cPort){
  i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_PIN,
        .scl_io_num = I2C_MASTER_SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master={
            .clk_speed = I2C_MASTER_FREQ_HZ
            }
    };
    ESP_ERROR_CHECK(i2c_param_config(_i2cPort, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(_i2cPort, I2C_MODE, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0)); 
}

void I2CMaster::write(I2C_address_t slaveAddress, bool ackCheckEnabled){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ack_t ackCheck = ackCheckEnabled ? ACK_CHECK_ENABLE : ACK_CHECK_DISABLE;
    ESP_ERROR_CHECK(i2c_master_start(cmd));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmd, slaveAddress << 1 | WRITE_BIT, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write(cmd, _writeBuffer.Data, _writeBuffer.Index, ackCheck));
    ESP_ERROR_CHECK(i2c_master_stop(cmd));
    ESP_ERROR_CHECK(i2c_master_cmd_begin(_i2cPort, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS));
    _clearWriteBuffer();
    i2c_cmd_link_delete(cmd);
}

void I2CMaster::write(uint8_t command, I2C_address_t slaveAddress, bool ackCheckEnabled){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ack_t ackCheck = ackCheckEnabled ? ACK_CHECK_ENABLE : ACK_CHECK_DISABLE;
    ESP_ERROR_CHECK(i2c_master_start(cmd));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmd, slaveAddress << 1 | WRITE_BIT, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmd, command, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write(cmd, _writeBuffer.Data, _writeBuffer.Index, ackCheck));
    ESP_ERROR_CHECK(i2c_master_stop(cmd));
    ESP_ERROR_CHECK(i2c_master_cmd_begin(_i2cPort, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS));
    _clearWriteBuffer();
    i2c_cmd_link_delete(cmd);
}

void I2CMaster::_clearWriteBuffer(){
    fillWriteBuffer(0x00);
    _writeBuffer.Index = 0;
}

void I2CMaster::writeBufferAdd(uint8_t data1) {
  _writeBuffer.Data[_writeBuffer.Index++] = data1;
}

void I2CMaster::writeBufferAdd(uint8_t data1, uint8_t data2) {
  _writeBuffer.Data[_writeBuffer.Index++] = data1;
  _writeBuffer.Data[_writeBuffer.Index++] = data2;
}

void I2CMaster::writeBufferAdd(uint8_t data1, uint8_t data2, uint8_t data3) {
  _writeBuffer.Data[_writeBuffer.Index++] = data1;
  _writeBuffer.Data[_writeBuffer.Index++] = data2;
  _writeBuffer.Data[_writeBuffer.Index++] = data3;
}

void I2CMaster::fillWriteBuffer(uint8_t fill){
  memset(_writeBuffer.Data, fill, _writeBuffer.size-1);
  _writeBuffer.Index = _writeBuffer.size - 1;
}


I2CMaster::~I2CMaster(){
    i2c_driver_delete(_i2cPort);
    
}