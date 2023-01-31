#ifndef _i2c_H_
#define _i2c_H_

#define ICLK   PORTCbits.RC3
#define IDAT   PORTCbits.RC4
#define TIDAT  TRISCbits.TRISC4

extern void Ndelay(void);
extern void i2c_init(void);
extern void i2c_start(void);
extern void i2c_stop(void);
extern void i2c_wb(unsigned char );
extern unsigned char i2c_rb(unsigned char );


#endif

