/**************** (C) COPYRIGHT 2015 �๦�ܵ����� ****************
* �� �� ��: �弶��������
* �� �� ��: Kaiser
* ��  ��  :  electronic organ
* ����޸�:  2015��10��30��
*********************************** �޶���¼ ********************/

//	0��(0000B)ģ������ģʽ
//	4��(0100B)��������ģʽ(��λ���״̬)
//	8��(1000B)����/��������ģʽ
//	C��(1100B)����
//	
//	1��(0001B)ͨ���������ģʽ10MHz
//	2��(0010B)ͨ���������ģʽ2MHz
//	3��(0011B)ͨ���������ģʽ50MHz
//	
//	5��(0101B)ͨ�ÿ�©���ģʽ10MHz
//	6��(0110B)ͨ�ÿ�©���ģʽ2MHz
//	7��(0111B)ͨ�ÿ�©���ģʽ50MHz
//	
//	9��(1001B)���ù����������ģʽ10MHz
//	A��(1010B)���ù����������ģʽ2MHz
//	B��(1011B)���ù����������ģʽ50MHz
//	
//	D��(1101B)���ù��ܿ�©���ģʽ10MHz
//	E��(1110B)���ù��ܿ�©���ģʽ2MHz
//	F��(1111B)���ù��ܿ�©���ģʽ50MHz

#include "stm32f10x.h"
#ifndef	__bool_true_false_are_defined
	#include <stdbool.h>
	typedef	bool	BOOL;
	#define	TRUE	true
	#define	FALSE	false
#endif

#define	PinBB( _Port, _Num )	(*(__IO int32_t *)(PERIPH_BB_BASE + ((uint32_t)&(_Port) - PERIPH_BASE) * 32u + (_Num) * 4u ))

void	delay_us ( uint32_t us )
{
	while ( us-- )
	{
		__nop(); __nop(); __nop(); __nop(); __nop();
 		__nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop();
	}
}

void	delay_ms( uint16_t ms )
{
	while ( ms-- )
	{
		delay_us( 999u );
	}
}

/*********************************************************** 
��������: N5110_PortInit
��������: N5110�˿ڳ�ʼ��
��ڲ���: ��
          ��
���ڲ���: �� 
�� ע�� 
***********************************************************/
//  DC-PB12   CLK-PB13  BL-PB14  DIN-PB15
void	N5110_PortInit( void )
{
  MODIFY_REG( GPIOB->CRH, 0xFFFF0000u, 0x33330000u );	
}
#define	N5110_DC	PinBB( GPIOB->ODR, 12U )
#define	SCLK  		PinBB( GPIOB->ODR, 13U )
#define	SDIN		  PinBB( GPIOB->ODR, 15U )
/*********************************************************** 
�������ƣ�N5110_Write_Byte
�������ܣ�ģ��SPI�ӿ�ʱ��д����/����N5110
��ڲ�����data    ��д������ݣ�
          command ��д����/����ѡ��
���ڲ������� 
�� ע�� 
***********************************************************/
void N5110_Write_Byte( uint8_t dat, bool command )
{
  uint8_t i;
  if ( command == TRUE )				 //д����
    N5110_DC = 0;				  
  else  
    N5110_DC = 1;			  //д����
  for( i = 0; i < 8; i ++ )				     //����8bit����
  { 
    if( dat & 0x80 )
      SDIN = 1;
    else
      SDIN = 0;
    SCLK = 0;
    dat = dat << 1;
    SCLK = 1; 
  }
}
//  PD8--PD15
void	P8P_ModeInput( void )
{
	GPIOD->CRH  = 0x44444444u;	//	�������뷽ʽ
}

void	P8P_ModeOutput( void )
{
	GPIOD->CRH  = 0x33333333u;	//	���������ʽ
}

uint8_t	P8P_PortRead( void )
{
	return	(uint8_t)( GPIOD->IDR >> 8 );
}

void	P8P_PortWrite( uint8_t OutByte )
{
	GPIOD->BSRR = ( 0xFF00uL << 16 )
								| ( 0xFF00uL & ((uint32_t)OutByte << 8 ));
}
//  PA3--PA7

/********************************** ����˵�� ***********************************
*	�����˿�ɨ��
*******************************************************************************/
uint8_t	 ElecKey_PortRead( void )
{
	uint8_t	PortState = 0u;

	PortState = ( GPIOA->IDR & 0xF8u ) >> 3;
	return	(uint8_t)(~PortState) & 0x3F;
}

void	 ElecKey_PortInit( void )
{
	SET_BIT( RCC->APB2ENR, RCC_APB2ENR_IOPAEN );
	//	����ʹ����������ģʽ
	GPIOA->BSRR = 0x00F8u;
	MODIFY_REG( GPIOA->CRL, 0xFFFFF000u, 0x88888000u );
}

/********************************** ����˵�� ***********************************
*	�����жϿ���
*******************************************************************************/
void	 ElecKey_IRQ_Enable( void )
{
	SET_BIT( RCC->APB2ENR, RCC_APB2ENR_AFIOEN );

	AFIO->EXTICR[0] = 
            AFIO_EXTICR1_EXTI2_PA
					| AFIO_EXTICR1_EXTI3_PA
					;
	AFIO->EXTICR[1] = 
            AFIO_EXTICR2_EXTI4_PA
					| AFIO_EXTICR2_EXTI5_PA
					| AFIO_EXTICR2_EXTI6_PA
					| AFIO_EXTICR2_EXTI7_PA
					;
	CLEAR_BIT( EXTI->EMR,  0x03FFu );	// no event
	CLEAR_BIT( EXTI->IMR,  0x0307u );	// ��ֹ�ж�0# 1# 2# 8#,9#    ��ΪNVIC_Init���濪�� 0 1 2 3 4 9_5�ж���
	SET_BIT(   EXTI->RTSR, 0x00FFu );	// rising edge trigger
	SET_BIT(   EXTI->FTSR, 0x00FFu );	// falling edge trigger
	WRITE_REG( EXTI->PR,   0x00FFu );	// д1��λ�жϱ�־λ
//	SET_BIT(   EXTI->IMR,  0x00FFu );	// �����ж� 0#~7#
	SET_BIT(   EXTI->IMR,  0x00F8u );	// �����ж� 3#~7# 
}

void	Keyboard_IRQ_Disable( void )
{
	WRITE_REG( EXTI->PR,   0x00FFu );	// д1��λ�жϱ�־λ
	CLEAR_BIT( EXTI->IMR,  0x03FFu );	// ��ֹ�ж�,���� 8#,9#
}


static	void	NVICInit( void )
{
	// 	��7.4 ��ռ���ȼ��������ȼ��ı�λ�������λ�õĹ�ϵ
	// 	����λ��    �����ռ���ȼ���λ��    ��������ȼ���λ��
	// 		0            [7:1]                 [0:0]
	// 		1            [7:2]                 [1:0]
	// 		2            [7:3]                 [2:0]
	// 		3            [7:4]                 [3:0]
	// 		4            [7:5]                 [4:0]
	// 		5            [7:6]                 [5:0]
	// 		6            [7:7]                 [6:0]
	// 		7            ��                    [7:0]������λ��
	NVIC_SetPriorityGrouping( 7 );	//	��ֹ�ж���ռ����û���ж�Ƕ��

	//	for Keyboard.
	NVIC_EnableIRQ( EXTI3_IRQn );
	NVIC_EnableIRQ( EXTI4_IRQn );
	NVIC_EnableIRQ( EXTI9_5_IRQn );

}







/********************************** ����˵�� ***********************************
*	����I2C����
*******************************************************************************/
enum	I2C_DirectSet { I2C_Write, I2C_Read };
enum	I2C_AcknowlegeSet { I2C_ACK, I2C_NoACK };
#define	Pin_I2C_SCL_In		PinBB( GPIOB->IDR, 6U )
#define	Pin_I2C_SCL_Out		PinBB( GPIOB->ODR, 6U )
#define	Pin_I2C_SDA_In		PinBB( GPIOB->IDR, 7U )
#define	Pin_I2C_SDA_Out		PinBB( GPIOB->ODR, 7U )
BOOL	bus_i2c_shout ( uint8_t cOutByte )
{
	BOOL	AcknowlegeState;
	uint8_t	i;

	for( i = 8U; i != 0U; --i )
	{
		if ( cOutByte & 0x80u )
		{
			Pin_I2C_SDA_Out = 1;
		}
		else
		{
			Pin_I2C_SDA_Out = 0;
		}
		cOutByte <<= 1;

		delay_us( 1 );
		Pin_I2C_SCL_Out = 1;

		delay_us( 1 );
		Pin_I2C_SCL_Out = 0;
	}
	
	Pin_I2C_SDA_Out = 1;
	delay_us( 1 );
	Pin_I2C_SCL_Out = 1;
	delay_us( 1 );
 	AcknowlegeState	= Pin_I2C_SDA_In;
	Pin_I2C_SCL_Out = 0;

	if ( I2C_ACK != AcknowlegeState )
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

uint8_t	bus_i2c_shin( enum I2C_AcknowlegeSet AcknowlegeSet )
{
	uint8_t		cInByte = 0U;
	uint8_t		i;

	Pin_I2C_SDA_Out = 1;		// make SDA an input
	for( i = 8U; i != 0U; --i )
	{
		delay_us( 1 );
		Pin_I2C_SCL_Out = 1;

		delay_us( 1 );
		cInByte <<= 1;
		if ( Pin_I2C_SDA_In )
		{
			cInByte |= 0x01u;
		}
		else 
		{
			cInByte &= 0xFEu;
		}

		Pin_I2C_SCL_Out = 0;
	}

	if ( I2C_ACK == AcknowlegeSet )
	{
		Pin_I2C_SDA_Out = 0;
	}
	else
	{
		Pin_I2C_SDA_Out = 1;
	}
	delay_us( 1 );
	Pin_I2C_SCL_Out = 1;
	delay_us( 1 );
	Pin_I2C_SCL_Out = 0;

	return	cInByte;
}

BOOL	bus_i2c_start ( uint8_t Address8Bit, enum I2C_DirectSet DirectSet )
{
	SET_BIT( RCC->APB2ENR, RCC_APB2ENR_IOPBEN );
 	MODIFY_REG( GPIOB->CRL, 0xFF000000u, 0x77000000u );

	//	Verify bus available.
	Pin_I2C_SDA_Out = 1;
	Pin_I2C_SCL_Out = 1;
	delay_us( 10 );
	if( ! Pin_I2C_SDA_In ){	 return  FALSE; }
	if( ! Pin_I2C_SCL_In ){	 return  FALSE; }

	Pin_I2C_SDA_Out = 0;
	delay_us( 1 );
	Pin_I2C_SCL_Out = 0;

	if ( I2C_Write == DirectSet )
	{
		return	bus_i2c_shout( Address8Bit & 0xFEu );
	}
	else
	{
		return	bus_i2c_shout( Address8Bit | 0x01u );
	}
}

void	bus_i2c_stop ( void )
{
	Pin_I2C_SDA_Out = 0;
	delay_us( 1 );
	Pin_I2C_SCL_Out = 1;
	delay_us( 1 );
	Pin_I2C_SDA_Out = 1;
	delay_us( 1 );
}


void  BIOS_Init( void )
{
  NVICInit();
  ElecKey_PortInit();
  N5110_PortInit();
}


