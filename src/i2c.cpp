#include "i2c.h"

void I2C_Buffer_t::fillBuf(uint8_t fdata){
    memset(Data, fdata, size-1);
}

void I2C_Buffer_t::reset(){
    ESP_LOGI("I2C_Buffer_t","Reset");
    fillBuf(0x00);
    Index = 0;
}

void I2C_Buffer_t::add(uint8_t data){
  Data[Index++] = data;
}

void I2C_Buffer_t::add(uint8_t data1, uint8_t data2){
  Data[Index++] = data1;
  Data[Index++] = data2;
}

void I2C_Buffer_t::add(uint8_t data1, uint8_t data2,  uint8_t data3){
  Data[Index++] = data1;
  Data[Index++] = data2;
  Data[Index++] = data3;
}

I2CMaster::I2CMaster(uint8_t i2cPort): _i2cPort(i2cPort){
  i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_PIN,
        .scl_io_num = I2C_MASTER_SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master={
            .clk_speed = I2C_MASTER_FREQ_HZ
            },
        .clk_flags=0
    };
    ESP_ERROR_CHECK(i2c_param_config(_i2cPort, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(_i2cPort, I2C_MODE, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0)); 
}

void I2CMaster::write( I2C_address_t slaveAddress, uint8_t cmd, bool ackCheckEnabled){
    i2c_cmd_handle_t cmdlink = i2c_cmd_link_create();
    ack_t ackCheck = ackCheckEnabled ? ACK_CHECK_ENABLE : ACK_CHECK_DISABLE;
    ESP_ERROR_CHECK(i2c_master_start(cmdlink));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmdlink, slaveAddress << 1 | WRITE_BIT, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmdlink, cmd, ackCheck));
    ESP_ERROR_CHECK(i2c_master_stop(cmdlink));
    ESP_ERROR_CHECK(i2c_master_cmd_begin(_i2cPort, cmdlink, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS));
    i2c_cmd_link_delete(cmdlink);
}

void I2CMaster::write( I2C_address_t slaveAddress, uint8_t cmd, I2C_Buffer_t *data, bool ackCheckEnabled){
    i2c_cmd_handle_t cmdlink = i2c_cmd_link_create();
    ack_t ackCheck = ackCheckEnabled ? ACK_CHECK_ENABLE : ACK_CHECK_DISABLE;
    ESP_ERROR_CHECK(i2c_master_start(cmdlink));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmdlink, slaveAddress << 1 | WRITE_BIT, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write_byte(cmdlink, cmd, ackCheck));
    ESP_ERROR_CHECK(i2c_master_write(cmdlink, data->Data, data->Index-1, ackCheck));
    ESP_ERROR_CHECK(i2c_master_stop(cmdlink));
    ESP_ERROR_CHECK(i2c_master_cmd_begin(_i2cPort, cmdlink, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS));
    data->reset();
    i2c_cmd_link_delete(cmdlink);
}

I2CMaster::~I2CMaster(){
    i2c_driver_delete(_i2cPort);
}