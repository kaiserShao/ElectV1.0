/**************** (C) COPYRIGHT 2015 多功能电子琴 ****************
* 文 件 名: 板级驱动程序
* 创 建 者: Kaiser
* 描  述  :  electronic organ
* 最后修改:  2015年10月30日
*********************************** 修订记录 ********************/

//	0：(0000B)模拟输入模式
//	4：(0100B)浮空输入模式(复位后的状态)
//	8：(1000B)上拉/下拉输入模式
//	C：(1100B)保留
//	
//	1：(0001B)通用推挽输出模式10MHz
//	2：(0010B)通用推挽输出模式2MHz
//	3：(0011B)通用推挽输出模式50MHz
//	
//	5：(0101B)通用开漏输出模式10MHz
//	6：(0110B)通用开漏输出模式2MHz
//	7：(0111B)通用开漏输出模式50MHz
//	
//	9：(1001B)复用功能推挽输出模式10MHz
//	A：(1010B)复用功能推挽输出模式2MHz
//	B：(1011B)复用功能推挽输出模式50MHz
//	
//	D：(1101B)复用功能开漏输出模式10MHz
//	E：(1110B)复用功能开漏输出模式2MHz
//	F：(1111B)复用功能开漏输出模式50MHz

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
函数名称: N5110_PortInit
函数功能: N5110端口初始化
入口参数: 无
          无
出口参数: 无 
备 注： 
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
函数名称：N5110_Write_Byte
函数功能：模拟SPI接口时序写数据/命令N5110
入口参数：data    ：写入的数据；
          command ：写数据/命令选择；
出口参数：无 
备 注： 
***********************************************************/
void N5110_Write_Byte( uint8_t dat, bool command )
{
  uint8_t i;
  if ( command == TRUE )				 //写命令
    N5110_DC = 0;				  
  else  
    N5110_DC = 1;			  //写数据
  for( i = 0; i < 8; i ++ )				     //传送8bit数据
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
	GPIOD->CRH  = 0x44444444u;	//	浮空输入方式
}

void	P8P_ModeOutput( void )
{
	GPIOD->CRH  = 0x33333333u;	//	推挽输出方式
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

/********************************** 功能说明 ***********************************
*	按键端口扫描
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
	//	按键使用上拉输入模式
	GPIOA->BSRR = 0x00F8u;
	MODIFY_REG( GPIOA->CRL, 0xFFFFF000u, 0x88888000u );
}

/********************************** 功能说明 ***********************************
*	按键中断控制
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
	CLEAR_BIT( EXTI->IMR,  0x0307u );	// 禁止中断0# 1# 2# 8#,9#    因为NVIC_Init里面开了 0 1 2 3 4 9_5中断线
	SET_BIT(   EXTI->RTSR, 0x00FFu );	// rising edge trigger
	SET_BIT(   EXTI->FTSR, 0x00FFu );	// falling edge trigger
	WRITE_REG( EXTI->PR,   0x00FFu );	// 写1复位中断标志位
//	SET_BIT(   EXTI->IMR,  0x00FFu );	// 允许中断 0#~7#
	SET_BIT(   EXTI->IMR,  0x00F8u );	// 允许中断 3#~7# 
}

void	Keyboard_IRQ_Disable( void )
{
	WRITE_REG( EXTI->PR,   0x00FFu );	// 写1复位中断标志位
	CLEAR_BIT( EXTI->IMR,  0x03FFu );	// 禁止中断,包括 8#,9#
}


static	void	NVICInit( void )
{
	// 	表7.4 抢占优先级和子优先级的表达，位数与分组位置的关系
	// 	分组位置    表达抢占优先级的位段    表达子优先级的位段
	// 		0            [7:1]                 [0:0]
	// 		1            [7:2]                 [1:0]
	// 		2            [7:3]                 [2:0]
	// 		3            [7:4]                 [3:0]
	// 		4            [7:5]                 [4:0]
	// 		5            [7:6]                 [5:0]
	// 		6            [7:7]                 [6:0]
	// 		7            无                    [7:0]（所有位）
	NVIC_SetPriorityGrouping( 7 );	//	禁止中断抢占，即没有中断嵌套

	//	for Keyboard.
	NVIC_EnableIRQ( EXTI3_IRQn );
	NVIC_EnableIRQ( EXTI4_IRQn );
	NVIC_EnableIRQ( EXTI9_5_IRQn );

}







/********************************** 功能说明 ***********************************
*	访问I2C总线
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


