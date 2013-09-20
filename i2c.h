#ifndef I2C_H_
#define I2C_H_

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u16;
typedef signed int s16;

typedef struct {
    u8 count;
    u8 state;
    u16 address;
    u8 *buffer;
} i2c_data_t;


#define size_tr(size, addr16) ((size-1)<<1)|(addr16 & 0x01)

// number of bytes to transfer(1 to 128, 2+ for RX), device ID, buffer pointer, is 16bit addressing, memory address
#define i2c_tx(size, id, buffer, addr16, address) i2c_trans(size_tr(size,addr16), id, buffer, address)
#define i2c_rx(size, id, buffer, addr16, address) i2c_trans(size_tr(size,addr16), id|0x01, buffer, address)

// number of bytes to transfer|16 bit addressing, device ID|dirrection, buffer pointer, memory address  
void i2c_trans(u8 size, u8 id, u8 buffer[], u16 address);

void i2c_init(void); // setup
u8 i2c_int(void); // data transfer interrupt
u8 i2c_eint(void); // NACK interrupt

#endif /*I2C_H_*/
