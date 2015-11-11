/**************** (C) COPYRIGHT 2015 多功能电子琴 ****************
* 文 件 名: Nokia5110液晶显示
* 创 建 者: Kaiser
* 描  述  :  
* 最后修改:  2015年10月30日
*********************************** 修订记录 ********************/
#include "stm32f10x.h"
#define max_txt_row		5u		// 行
#define max_txt_col		48u		// 列
#include "BIOS.H"
#include <string.h>

#define	code	const
#include "DOT_EN.TXT"
#include "DOT_CN.TXT"

typedef	uint8_t const * CGROM;
/*********************************************************** 
函数名称 ：N5110_set_XY
函数功能 ：设置N5110坐标函数
入口参数 ：X ：0－83
           Y ：0－5        
出口参数 ：无 
备 注： 
***********************************************************/
void N5110_set_XY( uint16_t yx )
{ 
  uint8_t row, col;
 
  row = ( yx ) / 256u;
	col = ( yx ) % 256u;
  
  N5110_Write_Byte( 0x40 | row, FALSE );		  // column
  N5110_Write_Byte( 0x80 | col, FALSE );        // row
}
// uint32_t hzNum;
// char hzIndex[1000]={0};char hzdot[1000] = {0};char  chardot[1000] = {0};
CGROM  DotSeekDBC ( int8_t sc )
{
    uint8_t uc = (uint8_t)sc;

	if ( uc < 0x20U ){	uc = 0x7FU;	}
	return	& chardot[( uc - 0x20U ) * 0x06U ];
}

CGROM  DotSeekSBC ( int8_t cc0, int8_t cc1 )
{
	uint16_t	cc16, cm16;
	uint16_t	mid, low, high;

	cc16 = ((uint8_t)cc0 * 0x100U ) + (uint8_t)cc1;

    low  = 1U;				/*	从[1]开始搜索	*/
	high = (uint16_t)hzNum - 1U;
	while ( low <= high ){

		mid = ( low + high ) / 2U;	/*	使用折半查找以加快检索速度	*/

		cm16 = ( hzIndex[ 2U * mid ] * 0x100U ) + hzIndex[( 2U * mid ) + 1U ];

		if ( cc16 == cm16 ){
			return	& hzdot[ mid * 0x20U ];
		}
		if ( cc16 > cm16 ){
			low  = mid + 1U;
		} else {
			high = mid - 1U;
		}
	}
	return	& hzdot[0];		/*	[0]存放空白字符	*/
}
/***********************************************************
函数名称：N5110_Puts
函数功能：显示英文字符
入口参数：c	:  显示的字符
出口参数：无 
备 注： 3310液晶显示屏汉字提取程序
***********************************************************/
void N5110_Puts( uint16_t yx, char * sz )
{
  uint8_t line, row, col, col_end, i;//typedef	uint8_t const * CGROM;
  char sDat;
  CGROM pDot;
  
  row = ( yx ) / 256u;
	col = ( yx ) % 256u;
  col_end = col + strlen( sz );
  
  do{
      sDat = *sz++;

      if (( sDat & 0x80u ) == 0u )
      { 	// DBC 半角英文
        N5110_set_XY( row * 256 + col++ );	//	设置地址
        pDot =  DotSeekDBC( sDat );
        for ( line=0; line<6; line++ )
          N5110_Write_Byte( *pDot++, TRUE );
      }
      else
      {	// SBC 全角汉字
        N5110_set_XY( row *256 + col++ );	//	设置地址
        pDot =  DotSeekSBC( sDat, * sz++ );
        for( i = 0u; i < 16u; ++i )
        {
          N5110_Write_Byte( *pDot++, TRUE );
        }
        N5110_set_XY( row * 256 + col++ );	//	设置地址
        for( i = 0u; i < 16u; ++i )
        {
          N5110_Write_Byte( *pDot++, TRUE );
        }
      }     
  }while( col < col_end  );
    			
}

/*********************************************************** 
函数名称：N5110_WriteBMP
函数功能：位图绘制函数
入口参数：YX  ：位图绘制的起始X、Y坐标；
*map    ：位图点阵数据；
Pix_x   ：位图像素（长）
Pix_y   ：位图像素（宽）
出口参数：无 
备 注： 
***********************************************************/
void N5110_WriteBMP( uint16_t yx, uint16_t bmpyx, uint8_t *map )
{
 	uint16_t i,n;
	uint8_t row, col;
	uint8_t brow, bcol;
	brow = bmpyx / 256;
	bcol = bmpyx % 256; 
	row = ( yx ) / 256u;
	col = ( yx ) % 256u;
  
  for ( n = 0; n < bcol; n ++ )		//换行
  {       
    N5110_set_XY( row * 256 + col++ );	
    for( i = 0; i < brow; i ++ )
    {	
      N5110_Write_Byte( *map++, TRUE );
    }                         
  }    
//   //计算位图所占行数
//   if(Pix_y%8==0) 		//如果为位图所占行数为整数
//     row=Pix_y/8;      
//   else
//     row=Pix_y/8+1;		//如果为位图所占行数不是整数

//   N5110_set_XY(X,Y);
//   for (n=0;n<row;n++)		//换行
//   {	
//     for(i=0;i<Pix_x;i++)
//     {	
//       N5110_set_XY(X+i,Y+n);
//       N5110_Write_Byte(map[i+n*Pix_x], 1);
//     }                         
//   }      
}
void N5110_clear( void )
{
  uint8_t n, i;
  for ( n = 0; n < max_txt_row; n ++ )		//换行
  {       
    N5110_set_XY( 0 * 256 + n );	
    for( i = 0; i < max_txt_col; i ++ )
    {	
      N5110_Write_Byte( 0xFF, TRUE );
    }                         
  }  
}
//管脚D/C(N5110_DC)用于选择写的是命令(D/C=0)还是数据(D/C=1)。
/*********************************************************** 
函数名称：N5110_init
函数功能：5110初始化
入口参数：无
出口参数：无 
备 注： 
***********************************************************/
void N5110_init( void )
{
//   N5110_RST = 0;     // 产生一个让N5110复位的低电平脉冲
//   delay_1us( );
//   N5110_RST = 1;

//   N5110_CE = 0;     // 关闭N5110
//   delay_1us( );
//   N5110_CE = 1;     // 使能N5110
//   delay_1us( );

  N5110_Write_Byte( 0x21, FALSE );	// 使用扩展命令设置N5110模式
  N5110_Write_Byte( 0xc8, FALSE );	// 设置液晶偏置电压
  N5110_Write_Byte( 0x06, FALSE );	// 温度校正
  N5110_Write_Byte( 0x13, FALSE );	// 1:48
  N5110_Write_Byte( 0x20, FALSE );	// 使用基本命令，V=0，水平寻址
  N5110_clear( );	           // 清屏
  N5110_Write_Byte( 0x0c, FALSE );	// 设定显示模式，正常显示

}
