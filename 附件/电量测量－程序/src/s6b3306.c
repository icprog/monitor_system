#include "s6b3306.h"
#include "LZF5162.h"

#include "zi16.h"


//---------------------------------------------------------3线SPI接口 驱动
//&&&&&&&&&&&&&&&&&&&&&&&&&&&         PS=0;MPU=0   &&&&&&&&&&&&&&&&&&
                   
sbit    RSTB = P1^5;
sbit    SCL  = P1^4;
sbit    SDI  = P1^2;
sbit    CS1  = P1^0;



 



//--------------------------------------------------------------------------
// 初始化S6B3306 2013-12-21 LIZHF
// 开机-复位-关闭待机-200mS-设置寄存器-100mS-开始显示
//
//--------------------------------------------------------------------------
void Init_S6B33B()
{
       HDReset();
       delay_1ms(50);
       Write_S6B33B_COM(0x2c);  //关闭待机模式
       delay_1ms(240);                  
      // Write_S6B33B_COM(0x02);	//设置振荡模式
      // Write_S6B33B_COM(0x00);  //设置00:内部振荡  默认也是内部振荡

       Write_S6B33B_COM(0x28);  //设置温度斜率补偿   
       Write_S6B33B_COM(0x01);  //01：-0.05%/°C 

      // Write_S6B33B_COM(0x45);    //RAM Skip AREA set设置显示RAM数据的X地址区域
      // Write_S6B33B_COM(0x00);	  //不跳动	默认00
      // Write_S6B33B_COM(0x53);    //指定显示模式  
      // Write_S6B33B_COM(0x00);	  //00：一般模式 默认00
       Write_S6B33B_COM(0x10);    //Drive output mode set
       Write_S6B33B_COM(0x03+0X8);    //22    0,0,DLN,MY,MX,SWP,CDIR 行列增量正负(MY MX)=0
	                              //修改为默认00 给的03

       Write_S6B33B_COM(0x30);  //4k he 65k 
       Write_S6B33B_COM(0x1d);  //1d  //修改为默认00
       Write_S6B33B_COM(0x32);  //设置行功能 Row vector mode set
       Write_S6B33B_COM(0x0e);	//	行增量于每周期 默认00每组0E每帧
       Write_S6B33B_COM(0x40);  //输入模式
       Write_S6B33B_COM(0x80+0X02);  //00  Y/X=0
       Write_S6B33B_COM(0x42);  // Y ADDRESS 
       Write_S6B33B_COM(2);
       Write_S6B33B_COM(129);
       Write_S6B33B_COM(0x43); // X ADDRESS
       Write_S6B33B_COM(4);
       Write_S6B33B_COM(131);
       Write_S6B33B_COM(0x34);  //反转设置 
       Write_S6B33B_COM(0x8d);	 //修改为默认00不反转，原8D
       Write_S6B33B_COM(0x2a);  // 调节对比度值 
       Write_S6B33B_COM(0x32);   //V1 3.339V  默认00 2.8V最大7F 4V
       Write_S6B33B_COM(0x55);   //局部显示模式设置   
       Write_S6B33B_COM(0x00);	 //局部显示开关。00关 01开
       Write_S6B33B_COM(0x56);   //局部显示开始的LINE地址（Y地址？）
       Write_S6B33B_COM(0x00);
       Write_S6B33B_COM(0x57);   //局部显示结束的LINE地址（Y地址？）  
       Write_S6B33B_COM(0x9f);
	   delay_1ms(120);;
       Write_S6B33B_COM(0x51);  //Display ON
}

//***************************************************************************SPI3
void Write_S6B33B_COM(uint8_t COMDADA_3SPI)
{
 uint8_t bit8;
 CS1=0;
 SCL=0;
 SDI=0;
 SCL=1; 
 for(bit8=0;bit8<8;bit8++)
 {
  SCL=0;
  SDI=COMDADA_3SPI&0x80;
  SCL=1;
  COMDADA_3SPI=(COMDADA_3SPI<<1);
 }
    CS1=1;
   
}
void Write_S6B33B_DISPLAY_DATA_serial_3SPI(uint8_t DADA_3SPI)
{   
 uint8_t bit8;
 CS1=0;
 SCL=0;
 SDI=1;
 SCL=1;
 for(bit8=0;bit8<8;bit8++)
 {
  SCL=0;
  SDI=DADA_3SPI&0x80;
  SCL=1;
  DADA_3SPI=(DADA_3SPI<<1);
 }
  CS1=1;
}
void Write_S6B33B_DISPLAY_DATA(uint8_t hibyte,uint8_t lowbyte)
{
 Write_S6B33B_DISPLAY_DATA_serial_3SPI(hibyte);
 Write_S6B33B_DISPLAY_DATA_serial_3SPI(lowbyte);
}
  


/*************************************************************
// S6B3306复位 2013-12-21 LIZHF
// 上电-2mS-复位-等待释放复位.
//
*************************************************************/
void HDReset()
{
 delay_1ms(5);
 RSTB=0;
 delay_1ms(20);
 RSTB=1;
 delay_1ms(20);

}

//--------------------------------------------------------
// 设置要显示区域的地址:X,Y为起始地址 ix,iy为增量地址
//
//
//--------------------------------------------------------
void setad(uint8_t x,uint8_t ix,uint8_t y,uint8_t iy)
{
     Write_S6B33B_COM(0x42);  // Y ADDRESS 
     Write_S6B33B_COM(2+x);
     Write_S6B33B_COM(2+x+ix);
     Write_S6B33B_COM(0x43); // X ADDRESS
     Write_S6B33B_COM(4+y);
     Write_S6B33B_COM(4+y+iy);
	 delay_1ms(1);
} 

  
/*************************************************************
// S6B3306测试 2013-12-21 LIZHF
//  
//
*************************************************************/ 
/*
void test_s6b3306()
{ 
 uint8_t p,q;
 delay_1ms(100); 
 Init_S6B33B();
 //0xf8,0x00单色
 setad(0,127,0,127);
 for(p=0;p<128;p++)
 {
  for(q=0;q<128;q++)
    Write_S6B33B_DISPLAY_DATA(0xf8,0x00);
 }
delay_1ms(1000); 

//0x07,0xe0单色
setad(0,127,0,127);
for(p=0;p<128;p++)
 {
  for(q=0;q<128;q++)
   Write_S6B33B_DISPLAY_DATA(0x07,0xe0);
 }
delay_1ms(1000); 
 
//0x00,0x1f单色
setad(0,127,0,127);
 for(p=0;p<128;p++)
 {
  for(q=0;q<128;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x00,0x1f);
  }
 }
delay_1ms(1000); 


// 七色条码
setad(0,127,0,127);
 for(p=0;p<128;p++)
 {
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0xf8,0x00);
  }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x07,0xe0);
  }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x00,0x1f);
  }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0xff,0xff);
   }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x00,0x00);
  }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x00,0x1f);
  }  
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0x07,0xe0);
  }
  for(q=0;q<16;q++)
  {
   Write_S6B33B_DISPLAY_DATA(0xf8,0x00);
  }
 }

} */
	
/***************************************************************************************
 描述: 在以X Y 起始的位置输入一个16X16大小的字
	   蓝底白字

****************************************************************************************/
void zi16(uint8_t x,uint8_t y,const unsigned char *p)
{   uint8_t QQ,px,ax;
    setad(x,15,y,15);
	   QQ=0;
       for(px=0;px<32;px++)	//一个字72个字节 每个字节8个位
	    { ax = p[px];
          for(QQ=0;QQ<8;QQ++)  //处理8个位，是1就出颜色 否则出0XFF 0XFF（黑色）
		  {	
		  	 if(ax&0x80)
             Write_S6B33B_DISPLAY_DATA(0Xff,0X0ff);	      //高位是1写入红色
	         else   Write_S6B33B_DISPLAY_DATA(0X0,0X1f);	      //高位是1写入颜色             
             ax=(ax<<1);	 //左移	 
			
		  }
        }
}

/***************************************************************************************
 描述: 在以X Y 起始的位置输入一个16X16大小的字
	   白底蓝字

****************************************************************************************/
void fzi16(uint8_t x,uint8_t y,const unsigned char *p)
{   uint8_t QQ,px,ax;
    setad(x,15,y,15);
	   QQ=0;
       for(px=0;px<32;px++)	//一个字72个字节 每个字节8个位
	    { ax = p[px];
          for(QQ=0;QQ<8;QQ++)  //处理8个位，是1就出颜色 否则出0XFF 0XFF（黑色）
		  {	
		  	 if(ax&0x80)
             Write_S6B33B_DISPLAY_DATA(0X00,0X1f);	      //高位是1写入红色
	         else   Write_S6B33B_DISPLAY_DATA(0Xff,0Xff);	      //高位是1写入白色             
             ax=(ax<<1);	 //左移	 
			
		  }
        }
}

/***************************************************************************************
 描述: 在以X Y 起始的位置输入一个8X16大小的字
       蓝底白字

****************************************************************************************/
void zi8(uint8_t x,uint8_t y,const unsigned char *p)
{   uint8_t QQ,px,ax;
    setad(x,7,y,15);
	   QQ=0;
       for(px=0;px<16;px++)	//一个字72个字节 每个字节8个位
	    { ax = p[px];
          for(QQ=0;QQ<8;QQ++)  //处理8个位，是1就出颜色  
		  {	
		  	 if(ax&0x80)
             Write_S6B33B_DISPLAY_DATA(0Xff,0X0ff);	      //高位是1写入红色
	         else   Write_S6B33B_DISPLAY_DATA(0X0,0X1f);	      //高位是1写入颜色             
             ax=(ax<<1);	 //左移	 
			
		  }
        }
}

/***************************************************************************************
 描述: 在以X Y 起始的位置输入一个8X16大小的字
	   白底蓝字


void fzi8(uint8_t x,uint8_t y,const unsigned char *p)
{   uint8_t QQ,px,ax;
    setad(x,7,y,15);
	   QQ=0;
       for(px=0;px<16;px++)	//一个字72个字节 每个字节8个位
	    { ax = p[px];
          for(QQ=0;QQ<8;QQ++)  //处理8个位，是1就出颜色  
		  {	
		  	 if(ax&0x80)
             Write_S6B33B_DISPLAY_DATA(0X00,0X01f);	      //高位是1写入蓝色
	         else   Write_S6B33B_DISPLAY_DATA(0X0ff,0Xff);	      //高位是1写入白色             
             ax=(ax<<1);	 //左移	 
			
		  }
        }
}
****************************************************************************************/

         
/***************************************************************************************
 描述:  将背景改成纯蓝色 

****************************************************************************************/
void BIUE(void)
{
    uint8_t p,q;

    setad(0,127,0,127);
   
    for(p=0;p<128;p++)
    {
      for(q=0;q<128;q++)     
         Write_S6B33B_DISPLAY_DATA(0x00,0x1f);   
    }

}


 /*
void logo(void)
{
 	uint8_t p,q,QQ;
    setad(0,127,0,127);
	   QQ=0;
	for(p=0;p<128;p++)
	{
		for(q=0;q<128;q++)
		{
			Write_S6B33B_DISPLAY_DATA(QQ,QQ+1);
			QQ++;
			QQ++;
		}
	}


}	 */
/***************************************************************************************
 描述: 预显示的菜单


****************************************************************************************/
void yu()
{

  zi16(16,0,hzli);
  zi16(32,0,hzdian);
  zi16(48,0,hzrong);
  zi16(64,0,hzliang);
  zi16(80,0,hzce);
  zi16(96,0,hzshi);
  //设置:
  zi16(0,16,hzshe);
  zi16(16,16,hzzhi);
  zi8(32,16,fhmh);
  //放电电流:
     //放电电流:
   zi16(0,32,hzfang);
   zi16(16,32,hzdian);
   zi16(32,32,hzdian);
   zi16(48,32,hzliu);

   zi8(64,32,fhmh);  
   zi8(88,32,fhd);
   zi8(104,32,zmA);
   //结束电压:
   	  //结束电压:
   zi16(0,48,hzjie);
   zi16(16,48,hzshu);
   zi16(32,48,hzdian);
   zi16(48,48,hzya); 
   zi8(64,48,fhmh);
   zi8(88,48,fhd);
   zi8(104,48,zmV);

  //状态:
  zi16(0,64,hzzhun);
  zi16(16,64,hztai);
  zi8(32,64,fhmh);
  //放电电流:
  zi16(0,80,hzfang);
  zi16(16,80,hzdian);
  zi16(32,80,hzdian);
  zi16(48,80,hzliu);
  zi8(64,80,fhmh);
  zi8(80,80,fhd);
  zi8(104,80,zmA);
  //电池电压:
  zi16(0,96,hzdian);
  zi16(16,96,hzchi);
  zi16(32,96,hzdian);
  zi16(48,96,hzya);
  zi8(64,96,fhmh);
  zi8(80,96,fhd);
  zi8(104,96,zmV);
  //已放容量:
  zi16(0,112,hzyi);
  zi16(16,112,hzfang);
  zi16(32,112,hzrong);
  zi16(48,112,hzliang);
  zi8(64,112,fhmh);
  zi8(104,112,zmm);
  zi8(112,112,zmA);
  zi8(120,112,zmH);

}


/***************************************************************************************
 描述:状态
 输入:xa,ADC的50次平均值.xv,ADC50次的平均值 mah电池容量的结果

****************************************************************************************/

void xs_zt(uint16_t xa,uint16_t xv,uint16_t mah)
{
  uint8_t a13,a12,a10,v13,v12,v10;
  uint8_t  m14,m13,m12,m11,m1;
   
  //电流
  xa = xa*2.32;
  if(xa%10>7)
   xa= xa+10;

  a13 = xa/1000;
  a12 = (xa%1000)/100;
  a10 = (xa%100)/10;
 // a1 = xa%10;
 
  zi8(72,80,sn[a13]);
  //zi8(80,80,sn[a100]);
  zi8(88,80,sn[a12]);
  zi8(96,80,sn[a10]);
  //电压
  xv = xv*4.87;
  if(xa%10>7)
  xv = xv+10;

  v13 = xv/1000;
  v12 = (xv%1000)/100;
  v10 = (xv%100)/10;
  //v1 = xv%10;
 
  zi8(72,96,sn[v13]);
 // zi8(80,96,sn[v100]);
  zi8(88,96,sn[v12]);
  zi8(96,96,sn[v10]); 
  //容量
  m14 = mah/10000;
  m13 = (mah%10000)/1000;
  m12 = (mah%1000)/100;
  m11 = (mah%100)/10;
  m1 = mah%10;
  if(m14>0)
  { 
    zi8(72,112,sn[m14]);
	zi8(80,112,sn[m13]);
	zi8(88,112,fhd);
	zi8(96,112,sn[m12]);
	zi8(104,112,sn[m11]);
	}
	else
	{
	zi8(72,112,sn[m13]);
	zi8(80,112,sn[m12]);
	zi8(88,112,sn[m11]);
	zi8(96,112,sn[m1]);
	zi8(104,112,zmm); 	
	}


}
/***************************************************************************************
 描述: 预设的值显示, seta,setv
       引入变量setn,0 
	                1:"设置电流" 
				    2:"结束电压"
	  	fdzt:0显示停止中
		     1显示放电中
****************************************************************************************/
void xs_sz(uint8_t seta,uint8_t setv,uint8_t setn)
{
  uint8_t a10,a1,v10,v1; 
  a10 = (seta%100)/10;
  a1 = seta%10;
  v10 = (setv%100)/10;
  v1 = setv%10;	 

  //: 2.0A  
  zi8(80,32,sn[a10]);  
  zi8(96,32,sn[a1]);
  
   //: 3.2V	  
  zi8(80,48,sn[v10]);  
  zi8(96,48,sn[v1]);
  
    if(setn == 0)
  {  
       //放电电流:
   zi16(0,32,hzfang);
   zi16(16,32,hzdian);
   zi16(32,32,hzdian);
   zi16(48,32,hzliu);
      	  //结束电压:
   zi16(0,48,hzjie);
   zi16(16,48,hzshu);
   zi16(32,48,hzdian);
   zi16(48,48,hzya);

  }
    if(setn == 1)
  {   
       //放电电流:
   fzi16(0,32,hzfang);
   fzi16(16,32,hzdian);
   fzi16(32,32,hzdian);
   fzi16(48,32,hzliu);
      	  //结束电压:
   zi16(0,48,hzjie);
   zi16(16,48,hzshu);
   zi16(32,48,hzdian);
   zi16(48,48,hzya);
   // zi8(112,32,fhjt);
 
 
  }
   if(setn == 2)
  {    //放电电流:
   zi16(0,32,hzfang);
   zi16(16,32,hzdian);
   zi16(32,32,hzdian);
   zi16(48,32,hzliu);
      	  //结束电压:
   fzi16(0,48,hzjie);
   fzi16(16,48,hzshu);
   fzi16(32,48,hzdian);
   fzi16(48,48,hzya);
  // zi8(112,48,fhjt);  
  }


}
void xsfdzt(bit fdzt)
{
  if(fdzt)
   {
    zi16(40,64,hzfang); 
    zi16(56,64,hzdian);
    zi16(72,64,hzzhong);  
   }
  else
   {
   	zi16(40,64,hzting); 
    zi16(56,64,hzzi);
   }
}