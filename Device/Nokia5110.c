/**************** (C) COPYRIGHT 2015 �๦�ܵ����� ****************
* �� �� ��: Nokia5110Һ����ʾ
* �� �� ��: Kaiser
* ��  ��  :  
* ����޸�:  2015��10��30��
*********************************** �޶���¼ ********************/
#include "stm32f10x.h"
#define max_txt_row		5u		// ��
#define max_txt_col		48u		// ��
#include "BIOS.H"
#include <string.h>

#define	code	const
#include "DOT_EN.TXT"
#include "DOT_CN.TXT"

typedef	uint8_t const * CGROM;
/*********************************************************** 
�������� ��N5110_set_XY
�������� ������N5110���꺯��
��ڲ��� ��X ��0��83
           Y ��0��5        
���ڲ��� ���� 
�� ע�� 
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

    low  = 1U;				/*	��[1]��ʼ����	*/
	high = (uint16_t)hzNum - 1U;
	while ( low <= high ){

		mid = ( low + high ) / 2U;	/*	ʹ���۰�����Լӿ�����ٶ�	*/

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
	return	& hzdot[0];		/*	[0]��ſհ��ַ�	*/
}
/***********************************************************
�������ƣ�N5110_Puts
�������ܣ���ʾӢ���ַ�
��ڲ�����c	:  ��ʾ���ַ�
���ڲ������� 
�� ע�� 3310Һ����ʾ��������ȡ����
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
      { 	// DBC ���Ӣ��
        N5110_set_XY( row * 256 + col++ );	//	���õ�ַ
        pDot =  DotSeekDBC( sDat );
        for ( line=0; line<6; line++ )
          N5110_Write_Byte( *pDot++, TRUE );
      }
      else
      {	// SBC ȫ�Ǻ���
        N5110_set_XY( row *256 + col++ );	//	���õ�ַ
        pDot =  DotSeekSBC( sDat, * sz++ );
        for( i = 0u; i < 16u; ++i )
        {
          N5110_Write_Byte( *pDot++, TRUE );
        }
        N5110_set_XY( row * 256 + col++ );	//	���õ�ַ
        for( i = 0u; i < 16u; ++i )
        {
          N5110_Write_Byte( *pDot++, TRUE );
        }
      }     
  }while( col < col_end  );
    			
}

/*********************************************************** 
�������ƣ�N5110_WriteBMP
�������ܣ�λͼ���ƺ���
��ڲ�����YX  ��λͼ���Ƶ���ʼX��Y���ꣻ
*map    ��λͼ�������ݣ�
Pix_x   ��λͼ���أ�����
Pix_y   ��λͼ���أ���
���ڲ������� 
�� ע�� 
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
  
  for ( n = 0; n < bcol; n ++ )		//����
  {       
    N5110_set_XY( row * 256 + col++ );	
    for( i = 0; i < brow; i ++ )
    {	
      N5110_Write_Byte( *map++, TRUE );
    }                         
  }    
//   //����λͼ��ռ����
//   if(Pix_y%8==0) 		//���Ϊλͼ��ռ����Ϊ����
//     row=Pix_y/8;      
//   else
//     row=Pix_y/8+1;		//���Ϊλͼ��ռ������������

//   N5110_set_XY(X,Y);
//   for (n=0;n<row;n++)		//����
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
  for ( n = 0; n < max_txt_row; n ++ )		//����
  {       
    N5110_set_XY( 0 * 256 + n );	
    for( i = 0; i < max_txt_col; i ++ )
    {	
      N5110_Write_Byte( 0xFF, TRUE );
    }                         
  }  
}
//�ܽ�D/C(N5110_DC)����ѡ��д��������(D/C=0)��������(D/C=1)��
/*********************************************************** 
�������ƣ�N5110_init
�������ܣ�5110��ʼ��
��ڲ�������
���ڲ������� 
�� ע�� 
***********************************************************/
void N5110_init( void )
{
//   N5110_RST = 0;     // ����һ����N5110��λ�ĵ͵�ƽ����
//   delay_1us( );
//   N5110_RST = 1;

//   N5110_CE = 0;     // �ر�N5110
//   delay_1us( );
//   N5110_CE = 1;     // ʹ��N5110
//   delay_1us( );

  N5110_Write_Byte( 0x21, FALSE );	// ʹ����չ��������N5110ģʽ
  N5110_Write_Byte( 0xc8, FALSE );	// ����Һ��ƫ�õ�ѹ
  N5110_Write_Byte( 0x06, FALSE );	// �¶�У��
  N5110_Write_Byte( 0x13, FALSE );	// 1:48
  N5110_Write_Byte( 0x20, FALSE );	// ʹ�û������V=0��ˮƽѰַ
  N5110_clear( );	           // ����
  N5110_Write_Byte( 0x0c, FALSE );	// �趨��ʾģʽ��������ʾ

}
