#include "lzf5162.h"
#include "s6b3306.h"
#include "zi16.h"

sbit    ax  = P2^5;
sbit    bx  = P2^4;
sbit    zj  = P2^2;
sbit    kt  = P2^7;
sbit    mosoff  = P3^5;
sbit    led0  = P1^7;

static bit aold,bold;//编码器旧状态

uint8_t tmrn;
uint16_t adc4;// 电流值
uint16_t adc3;//电池电压
uint16_t adc4a;//  电流值
uint16_t adc3v;//电池电压
uint16_t mah;
uint16_t mas;	//1mA*1S  1mah = 3600maS
uint8_t tmrnx;
uint8_t seta=10;
uint8_t setv=30;
uint8_t setn=0;	//菜单状态

bit fdzt=0;    //放电状态


uint16_t adcz(uint8_t adn);
void tm0_init(void);
void bmkg(void);
void jia1(void);
void jian1(void);
//void yu();
void main()
{
  uint16_t adc3old,adc4old,mahold;
  bit xsx,fdztold;
 
  P2M0 = 0X0;
  P2M1 = 0X0;  //8051标准模式
  P1M0 = 0X0;
  P1M1 = 0X0ff;  //改成全推挽输出
  P4M0 = 0X0;
  P4M1 = 0X0ff;  //改成全推挽输出 

  P3M0 &= ~(1<<5);
  P3M1 |= (1<<5);
  led0 = 0;	  mosoff  = 1;
  P2 = 0X0FF;

  TMOD = 0X0|(1<<4);//定时器1以16位定时方式工作
   
  Init_S6B33B(); //初始化屏幕
  BIUE(); //屏幕蓝色背景
 
  yu();	//预先固定显示的内容
 
  delay_1ms(10);
  adcinit();
  tm0_init();
   xs_sz(seta, setv, setn);
   xs_zt(0,0,0);
   xsfdzt(fdzt);
  EA=1;
 

  while(1)
  {
  	if(adc3old != adc3)
	 xsx = 1; 
	if(adc4old != adc4)
	 xsx = 1; 
	if(mahold != mah)
	 xsx = 1; 
    if(xsx)
	{
	 xs_zt(adc4,adc3,mah);
	 xsx = 0;
	 mahold = mah;	adc4old = adc4;	 adc3old = adc3;

	}
    else
	 delay_1ms(2);
	if(fdztold != fdzt)
	{
	 xsfdzt(fdzt);
	 fdztold = fdzt;
	}

	   	 //显示时关掉中断.
	//编码开关中键,按下改设置 

	 //编码开关
	 if(seta == 0)
	  seta = 20;
     if(seta >= 21)
	  seta = 1;				     
	 if(setv == 0)
	  setv = 50;
     if(setv >= 51)
	  setv = 1;
	 
	 bmkg();
 
	//开始暂停按键
	  delay_1ms(1);
	if(kt == 0)
	{ 
	 delay_1ms(10);
	  if(kt == 0)
	  {
	   if(fdzt==1)
	    {fdzt = 0; mosoff = 1;led0=1; pwm0(190,0);	}
		else 
		 {fdzt = 1;pwm0(240,seta*6);
		  mosoff=0;}
	   	  
	  while(!kt);
	  delay(3);
	  xsfdzt(fdzt);
	  
	  
	  }
	  
	}
  	

    if(zj==0)
	 { 
	  delay_1ms(10);
	   if(zj==0)
	   {
	     setn++;
		 if(setn >= 3)
		   setn = 0;	  
		 while(!zj);
    	 xs_sz(seta, setv, setn);
    	 
		 		 
	   }
	 }




  }//


}



/**********************************************************
 定时器1中断服务程序 LIZHF 2013-12-25
 条件: 11..0592M晶振 CPU 1T
 占用资源: 
**********************************************************/

void tm0_int(void) interrupt 1 
{
  uint16_t tmp1,tmp2;
  TH0=(65535-55296)/256;
  TL0=(65535-55296)%256; 
  
  tmrn++;
  tmp1 = adcz(4);
  adc4a = adc4a + tmp1;
  tmp2 = adcz(3);
  adc3v = adc3v + tmp2;
   
  if(tmrn==50)
  {
      tmrnx++;

	if(adc4a%50>35)
    	adc4a = adc4a/50+1;
		else adc4a = adc4a/50;
	if(adc3v%50>35)
    	adc3v = adc3v/50+1;
		else adc3v = adc3v/50;
   
 
   //放电时计数
   if(fdzt)
   {     led0=!led0;
     mas = mas + 0.58*adc4a;
	 if(mas>3600)
	  {
	   mah++;
	   mas = mas-3600;
	  }   
   }
   
   tmp1 = setv*20.53;
   if(adc3v<tmp1)
   {
   	fdzt=0;
	mosoff=1;
	led0=1;
	pwm0(190,0);//默认1A
	
   } 
   adc4 = adc4a;
   adc3 = adc3v;
   adc4a = 0;
   adc3v = 0; 
   tmrn=0; 

  }//50次


}


/***************************************************************************************
 描述 : 检测编码开关子程序	 程序占用全局变量: aold bold
 时间 : 2013-11-14	for lizhifang 
****************************************************************************************/

void bmkg(void)
{   
  
   if(aold^bold)    //异或有转动
  {
   if(ax&&bx)	   //转到A,B同为1
   {
     if(bold)
	  jia1();  	//处理子程序
	 if(aold)
	 jian1();
   }
   if((!ax)&&(!bx)) //转到A,B同为0
   {        
     if(aold)
	  jia1();
	 if(bold)
	  jian1();    
   } 
  } 
  aold = ax;
  bold = bx;
  //return bmn;
}

void jia1(void)
{
 if(setn==1)
  seta++;
   pwm0(240,seta*6);
 if(setn==2)
 setv++;
   xs_sz(seta, setv, setn);

}

void jian1(void)
{
 if(setn==1)
  seta=seta-1;
   pwm0(190,seta*5);
 if(setn==2)
 setv=setv-1;
   xs_sz(seta, setv, setn);

}
