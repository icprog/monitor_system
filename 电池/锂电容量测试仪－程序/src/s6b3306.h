#ifndef	__s6b3306_h__
#define	__s6b3306_h__
#include	"SLH89F5162.H"
#include	"LZF5162.h"

//#define unchar  unsigned char
//#define unint   unsigned int
       

extern void Init_S6B33B();
extern void Write_S6B33B_COM(uint8_t COMDADA_3SPI);
extern void Write_S6B33B_DISPLAY_DATA_serial_3SPI(uint8_t DADA_3SPI);
extern void Write_S6B33B_DISPLAY_DATA(uint8_t hibyte,uint8_t lowbyte);

extern void HDReset();
//extern void setad(uint8_t x,uint8_t ix,uint8_t y,uint8_t iy);
extern void BIUE(void);
extern void test_s6b3306();
extern void yu();
extern void xs_zt(uint16_t xa,uint16_t xv,uint16_t mah);

extern void logo(void);
extern void xs_sz(uint8_t seta,uint8_t setv,uint8_t setn);
extern void xsfdzt(bit fdzt);
#endif
