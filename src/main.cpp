#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "i2c.h"
#include "SSD1306.h"
extern "C" {
    void app_main(void);
}

void app_main() {
    I2CMaster i =I2CMaster(0);
    ssdLCD l = ssdLCD(&i, SSD1306_ADDR);
    l.init();
    l.printStr((char*)"hello World!", 0,0,1);
    
}