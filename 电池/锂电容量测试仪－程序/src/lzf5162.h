#ifndef	__LZF5162_h__
#define	__LZF5162_h__
#include	"SLH89F5162.H"

#define uint8_t  unsigned char
#define uint16_t unsigned int



extern void pwm0(uint8_t pwmp,uint8_t pwmd);

extern void delay_1ms(uint16_t x);

extern void tm0_init(void);

extern void adcinit(void);

extern uint16_t adcz(uint8_t adn);
extern void delay(unsigned int x);

#endif
