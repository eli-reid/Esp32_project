#ifndef I2C_DFS_H
#define	I2C_DFS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#ifndef I2C_BUFFER_SIZE
  #define I2C_BUFFER_SIZE           64
#endif

#define I2C_MASTER_SCL_PIN          22    
#define I2C_MASTER_SDA_PIN          21 
#define I2C_MASTER_PORT_NUM         0                       
#define I2C_MASTER_FREQ_HZ          400000                     
#define I2C_MASTER_TX_BUF_DISABLE   0                          
#define I2C_MASTER_RX_BUF_DISABLE   0                          
#define I2C_MASTER_TIMEOUT_MS       1000
#define I2C_MODE                    I2C_MODE_MASTER
#define ACK_CHECK_ENABLE            0x1                        
#define ACK_CHECK_DISABLE           0x0                
#define ACK_VAL                     0x0             
#define NACK_VAL                    0x1    
#define WRITE_BIT                   I2C_MASTER_WRITE     
#define READ_BIT                    I2C_MASTER_READ 

typedef uint8_t I2C_address_t;

typedef struct {
  uint8_t Index;
  uint8_t Data[I2C_BUFFER_SIZE];
  const uint8_t size;
} I2C_Buffer_t;  

typedef unsigned int ack_t;
#ifdef	__cplusplus
}
#endif
#endif