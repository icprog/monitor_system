
#ifndef REGSLH89F5162_H
#define REGSLH89F5162_H
/* ------------------- BYTE Register-------------------- */
/* CPU */
sfr PSW = 0xD0;
sfr ACC = 0xE0;
sfr B = 0xF0;
sfr AUXC = 0xF1;
sfr SP = 0x81;
sfr DPL = 0x82;
sfr DPH = 0x83;
sfr DPL1 = 0x84;
sfr DPH1 = 0x85;
sfr INSCON   = 0x86;

/* Power  */
sfr PCON  = 0x87;
sfr SUSLO = 0x8E;

/* Clock */
sfr CLKCON = 0xB2;																											
        	                              																												
/* FLASH */
sfr XPAGE = 0xF7;
sfr IB_OFFSET = 0xFB;
sfr IB_DATA = 0xFC;	
sfr IB_CON1 = 0xF2;
sfr IB_CON2 = 0xF3;
sfr IB_CON3 = 0xF4;
sfr IB_CON4 = 0xF5;
sfr IB_CON5 = 0xF6;
sfr FLASHCON = 0xA7;

/* WDT */
sfr RSTSTAT = 0xB1;

/* INTERRUPT */
sfr IEN0= 0xA8;
sfr IEN1 = 0xA9;
sfr IENC = 0xBA;
sfr IPL0 = 0xB8;
sfr IPL1 = 0xB9;
sfr IPH0 = 0xB4;
sfr IPH1 = 0xB5;
sfr EXF0 = 0xAA;
sfr EXF1 = 0xD8;

/* TIMER 0/1 */
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr TCON1 = 0xCE;

/* TIMER2 */
sfr T2CON = 0xC8;
sfr T2MOD = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2 = 0xCC;
sfr TH2 = 0xCD;

/* LPD */
sfr LPDCON = 0xB3;
        	                              																												
/* Port */        	
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0xA0;
sfr P3 = 0xB0;
sfr P4 = 0xC0;

sfr P0M0 = 0xE9;
sfr P0M1 = 0xE1;
sfr P1M0 = 0xEA;
sfr P1M1 = 0xE2;
sfr P2M0 = 0xEB;
sfr P2M1 = 0xE3;
sfr P3M0 = 0xEC;
sfr P3M1 = 0xE4;
sfr P4M0 = 0xED;
sfr P4M1 = 0xE5;

/* EUART 0/1 */
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr SADDR = 0x9A;
sfr SADEN = 0x9B;	

sfr SCON1 = 0xE8;
sfr SBUF1 = 0x9D;
sfr SADDR1 = 0x9E;
sfr SADEN1 = 0x9F;	
sfr SBRT0 = 0x9C;
sfr SBRT1 = 0xA4;	

/* SPI */
sfr SPSTA = 0xF8;
sfr SPCON = 0xA2;
sfr SPDAT = 0xA3;
        	
/* ADC */
sfr ADCON = 0x93;
sfr ADT = 0x94;
sfr ADCH = 0x95;
sfr ADDL = 0x96;
sfr ADDH = 0x97;
        	
/* PWM */
sfr PWM0CON = 0xD9;
sfr PWM1CON = 0xDA;
sfr PWM2CON = 0xDB;
sfr PWM0P = 0xD1;
sfr PWM1P = 0xD2;
sfr PWM2P = 0xD3;
sfr PWM0D = 0xC1;
sfr PWM1D = 0xC2;
sfr PWM2D = 0xC3;
       	
/* CMP */
sfr CMPCON0 = 0x91;
sfr CMPCON1 = 0x92;

/* ISP */
sfr ISPLO = 0xA5;
sfr ISPCON = 0xA6;

/*--------------------------  BIT Register -------------------- */
/*  PSW   */
sbit CY = 0xD7;
sbit AC = 0xD6;
sbit F0 = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV = 0xD2;
sbit F1 = 0XD1;
sbit P = 0xD0;

/*  IPL0   */ 
sbit PADCL = 0xBE;
sbit PT2L = 0xBD;
sbit PS0L = 0xBC;
sbit PT1L = 0xBB;
sbit PX1L = 0xBA;
sbit PT0L = 0xB9;
sbit PX0L = 0xB8;

/*  SCON  */
sbit SM0_FE = 0x9F;
sbit SM1_RXOV = 0x9E;
sbit SM2_TXCOL = 0x9D;
sbit REN = 0x9C;
sbit TB8 = 0x9B;
sbit RB8 = 0x9A;
sbit TI = 0x99;
sbit RI = 0x98;

/*  TCON  */
sbit TF1 = 0x8F;
sbit TR1 = 0x8E;
sbit TF0 = 0x8D;
sbit TR0 = 0x8C;
sbit IE1 = 0x8B;
sbit IT1 = 0x8A;
sbit IE0 = 0x89;
sbit IT0 = 0x88;

/*  IEN0   */
sbit EA = 0xAF;
sbit EADC = 0xAE;
sbit ET2 = 0xAD;
sbit ES0 = 0xAC;
sbit ET1 = 0xAB;
sbit EX1 = 0xAA;
sbit ET0 = 0xA9;
sbit EX0 = 0xA8;

/*  EXF1  */
sbit IF40 = 0xD8;
sbit IF41 = 0xD9;
sbit IF42 = 0xDA;
sbit IF43 = 0xDB;
sbit IF44 = 0xDC;
sbit IF45 = 0xDD;
sbit IF46 = 0xDE;
sbit IF47 = 0xDF;

/*  T2CON  */
sbit TF2 = 0xCF;
sbit EXF2 = 0xCE;
sbit RCLK = 0xCD;
sbit TCLK = 0xCC;
sbit EXEN2 = 0xCB;
sbit TR2 = 0xCA;
sbit C_T2 = 0xC9;
sbit CP_RL2 = 0xC8;

/*  SCON1  */
sbit SM10_FE  = 0xEF;
sbit SM11_RXOV = 0xEE;
sbit SM12_TXCOL = 0xED;
sbit REN1 = 0xEC;
sbit TB18 = 0xEB;
sbit RB18 = 0xEA;
sbit TI1 = 0xE9;
sbit RI1 = 0xE8;

/* SPSTA */
sbit SPEN =  0xFF;
sbit SPIF =  0xFE;
sbit MODF =  0xFD;
sbit WCOL =  0xFC;
sbit RXOV =  0xFB;

/* P0 */
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;

/* P1 */
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

/* P2 */
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

/* P3 */
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

/* P4 */
sbit P4_0 = P4^0;
sbit P4_1 = P4^1;
sbit P4_2 = P4^2;
sbit P4_3 = P4^3;
sbit P4_4 = P4^4;
sbit P4_5 = P4^5;
sbit P4_6 = P4^6;
sbit P4_7 = P4^7;

#endif
