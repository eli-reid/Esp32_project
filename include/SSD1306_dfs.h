#ifndef _SSD1306_DFS_H_
#define _SSD1306_DFS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SSD1306_ADDR                    0x3C
#define SSD1306_WIDTH                   128
#define SSD1306_HEIGHT                  64
#define SSD1306_BOLD                    1   
// Display Commands
#define SSD1306_CONTROL_CMD_SINGLE      0x80
#define SSD1306_CONTROL_CMD_STREAM      0x00
#define SSD1306_CONTROL_DATA_SINGLE     0xC0
#define SSD1306_CONTROL_DATA_STREAM     0x40
#define SSD1306_ALL_ON_RAM              0xA4 
#define SSD1306_ALL_ON                  0xA5
#define SSD1306_DISPLAY_NORMAL          0xA6
#define SSD1306_DISPLAY_INVERSE         0xA7
#define SSD1306_SET_MPLX                0xA8
#define SSD1306_DISPLAY_OFF             0xAE
#define SSD1306_DISPLAY_ON              0xAF 
#define SSD1306_SET_CONTRAST            0x81 // 0 - 255
#define SSD1306_OSC                     0xD5 
#define SSD1306_SET_OFFSET              0xD3
#define SSD1306_SET_START               0x40 // range 0x40~0x7F
#define SSD1306_CHARGE_PUMP             0x8D
#define SSD1306_CHARGE_PUMP_ON          0x14
#define SSD1306_CHARGE_PUMP_OFF         0x10
#define SSD1306_CHARGE_PERIOD           0xD9
#define SSD1306_MEM_ADDR_MODE           0x20
#define SSD1306_COL_NORM                0xA0
#define SSD1306_COL_INVERSE             0xA1
#define SSD1306_ROW_NORM                0xC0
#define SSD1306_ROW_INVERSE             0xC8
#define SSD1306_SET_VERT_SCROLL_AREA    0xA3
#define SSD1306_ACTIVE_SCROLL           0x2F
#define SSD1306_DEACTIVE_SCROLL         0x2E
#define SSD1306_SET_PAGE_ADDR_MODE      0x20
#define SSD1306_NOP                     0xE3
#define SSD1306_PAGE_0                  0xB0
#define SSD1306_PAGE_1                  0xB1
#define SSD1306_PAGE_2                  0xB2
#define SSD1306_PAGE_3                  0xB3
#define SSD1306_PAGE_4                  0xB4
#define SSD1306_PAGE_5                  0xB5
#define SSD1306_PAGE_6                  0xB6
#define SSD1306_PAGE_7                  0xB7

#define SSD1306_
#ifdef	__cplusplus
}
#endif
#endif