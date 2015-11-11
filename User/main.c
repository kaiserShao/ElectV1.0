#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <cmsis_os.h>
// #define __task          // __declspec(noreturn)
// #define __used          // __attribute__((used))os_tsk_pass()osThreadTerminate os_clock_demon osDelay osThreadYield
// /********************************** 功能说明 ***********************************
// *	I2C 总线的互斥访问控制
// *******************************************************************************/
// // static	osMutexId	mutexBus_I2C = NULL;

// // void	bus_i2c_mutex_apply( void )
// // {
// // 	osMutexWait( mutexBus_I2C, osWaitForever );
// // }

// // void	bus_i2c_mutex_release( void )
// // {
// // 	osMutexRelease( mutexBus_I2C );
// // }

// // static	void	bus_i2c_mutex_init( void )
// // {
// // 	static	osMutexDef ( mutex_i2cbus );

// // 	mutexBus_I2C = osMutexCreate( osMutex( mutex_i2cbus ));
// // }
// // static	osMutexId	mutexBus_SPI = NULL;

// // void	bus_SPI_mutex_apply( void )
// // {
// // 	osMutexWait( mutexBus_SPI, osWaitForever );
// // }

// // void	bus_SPI_mutex_release( void )
// // {
// // 	osMutexRelease( mutexBus_SPI );
// // }

// // static	void	bus_SPI_mutex_init( void )
// // {
// // 	static	osMutexDef ( mutex_SPIbus );

// // 	mutexBus_SPI = osMutexCreate( osMutex( mutex_SPIbus ));
// // }


// // uint32_t ID1,ID2;

// // void  _task_Keyboard( void const * p_arg ) __task ;	
// // void task1(  void const * p_arg  )__task ;
// // void task2( void const * p_arg ) __task ;
// // //	osThreadDef(name, priority, instances, stacksz)
// // static	osThreadDef( _task_Keyboard, osPriorityNormal, 1u, 100u );
// // static	osThreadDef( task1, osPriorityNormal, 1, 200 );
// // static	osThreadDef( task2, osPriorityNormal, 1, 200 );
// // osSemaphoreId	semiKeyHited;	
// // osSemaphoreId	semiKeyChanged;	//

// // // osSemaphoreWait( semiKeyHited, iRetry * 10u );
// // // osSemaphoreRelease( semiKeyChanged );

// // osSemaphoreDef( KeyChanged );
// // osSemaphoreDef( KeyHited );
// // void task2( void const * p_arg ) __task 
// // {
// // 	for(;;)
// // 	{
// // 		bus_SPI_mutex_apply();
// // 		__nop();
// // 		osDelay(500);
// // 		bus_SPI_mutex_release();
// // 	}
// // }
// // void task1(  void const * p_arg  )__task 
// // {
// //  for(;;)
// // 	{
// // 		bus_i2c_mutex_apply();
// // // 		osSemaphoreWait( semiKeyHited,osWaitForever );
// // // 		osThreadCreate( osThread( task2 ), NULL );
// // 		osDelay(300);
// // // 		osSemaphoreRelease( semiKeyHited );
// // 		
// // 		bus_i2c_mutex_release();
// // 	}
// // }
// // void  _task_Keyboard( void const * p_arg ) __task 
// // {
// // 	for(;;)
// // 	{
// // // 		bus_SPI_mutex_apply();
// // 		osSemaphoreWait( semiKeyHited,osWaitForever );	
// // // 		osThreadCreate( osThread( task1 ), NULL );
// // 		osDelay(200);
// // 		osSemaphoreRelease( semiKeyHited );

// // // 		bus_SPI_mutex_release();
// // 	}
// // }

// // void	RTOS_Init( void )
// // {
// // // 	static osStatus s;
// // // 	static int8_t x;
// // // 	s = osKernelInitialize();
// // // 	s = osKernelStart();
// // // 	x = osKernelRunning();	
// // // 	osThreadCreate( osThread( task1 ), NULL);
// // 	bus_i2c_mutex_init();
// // 	bus_SPI_mutex_init();
// // 	semiKeyChanged = osSemaphoreCreate(osSemaphore( KeyChanged ), 0 );
// // 	semiKeyHited = osSemaphoreCreate(osSemaphore( KeyHited ), 0 );
// // 	osThreadCreate( osThread( _task_Keyboard ), 0 );osThreadCreate( osThread( task1 ), NULL );osThreadCreate( osThread( task2 ), NULL );
// // 	osSemaphoreRelease( semiKeyHited );
// // // 	if( x == 1 && s == osOK )
// // // 		return;
// // // 	else
// // // 		for(;;)
// // // 		{
// // // 			;
// // // 		}
// // }
typedef char CHAR;
struct	uMenu
{
	uint16_t yx;
	CHAR * sz;
};
/*********************************menu_Main***********************************
*主菜单*
******************************************************************************/
// void menu_Main( void )
// {
// 	static	struct uMenu  const  menu[] =
// 	{
// 		{ 0x0202u, "主菜单"	},
// 		{ 0x0203u,  "弹奏" 	},	 
// 		{ 0x020Au,  "点播" 	}, 
// 		{ 0x0403u,  "闹钟" 	}, 
// 		{ 0x040Au,  "设置" 	},
// 	};

// 	uint8_t	item = 1u;

// 	for(;;)
// 	{
// 		cls();
// 		Menu_Redraw( menu );
// 		item = Menu_Select_Ex( menu, item, show_std_clock );
// 		
// 		switch( item )
// 		{
// 			case 1: Play_Piano();	break;
// 			case 2: Recording();	break;
// 			case 3: Play_Music();	break;
// 			case 4: Set_alarm();	break;
// 		}
// 	}
// }
/************************Play_Piano********************************************
*弹奏*
******************************************************************************/
// void Play_Piano( void )
// {
// 	static	struct uMenu  const  menu[] =
// 	{
// 		{ 0x0202u, "弹奏"	},
// 		{ 0x0203u,  "乐谱模式" 	},	 
// 		{ 0x0403u,  "开始演奏" 	}, 
// 	};

// 	uint8_t	item = 1u;

// 	for(;;)
// 	{
// 		cls();
// 		Menu_Redraw( menu );
// 		item = Menu_Select_Ex( menu, item, show_std_clock );
// 		
// 		switch( item )
// 		{
// 			case 1: Music_Score();	break;
// 			case 2: Play_Star();	break;
// 		}
// 	}
// }
/********************************Music_Score***********************************
*乐谱类型*
******************************************************************************/
// void Music_Score( void )
// {
// 	static	struct uMenu  const  menu[] =
// 	{
// 		{ 0x0202u, "乐谱显示类型"	},
// 		{ 0x0203u,  "五线谱" 	},	 
// 		{ 0x0403u,  "数  字" 	}, 
// 		{ 0x0403u,  "简谱" 	}, 
// 	};

// 	uint8_t	item = 1u;

// do
// 	{
// 		cls();
// 		Menu_Redraw( menu );
// 		item = Menu_Select_Ex( menu, item, show_std_clock );
// 		
// 		switch( item )
// 		{
// 			case 1: Music_Stave();	break;
// 			case 2: Music_Num();	break;
// 			case 3: Music_Notation();	break;
// 		}
// 	}while( enumSelectESC != item )
// }
/***************************Recording******************************************
*播放*
******************************************************************************/
void Recording( void )
 {
	
// 	static	struct uMenu * menu;
//	{ { 0x00, TableSZ[0] }, }
// 	CHAR  * TableSZ;
// 	u8 i;
// 	struct uMusic	Music;
	

// 	do
// 	{
// 		menu [0].yx = 0x0106;
// 		menu [0].sz = "乐曲选择";	
// 		for( i = 1; i < 7; i ++ )
// 		{
// 			File_Load( i - 1, &Music,sizeof( struct uMusic ) );
// 			sprintf( TableSZ,"%d.%s",i, Music.Save_Time );
// 			menu [i].yx = 0x00;
// 			menu [i].sz = TableSZ;
// 			memset( TableSZ, 0x00, 20 );//	xxxx-xx-xx xx:xx  16字节 24c08	1024 * 8 --- 8192字节
// 		}
// 		cls();
// 		Menu_Redraw( menu );

// 		item = Menu_Select_Ex( menu, item, show_std_clock );
// 		File_Load( i, &Music,sizeof( struct uMusic ) );

// 		switch( item )
// 		{
// 			case 1: Music_Stave();	break;
// 			case 2: Music_Num();	break;
// 			case 3: Music_Notation();	break;
// 		}
// 	}while( enumSelectESC != item )
 }
/*****************************************************************************
*闹钟设置
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

/*****************************************************************************
*
******************************************************************************/

int  main(void)
{
// 	RTOS_Init();
	for(;;)
	{
// 		menu_Main();
	}
}


// /*systick*/


// static	uint32_t m_tick;

// void	MonitorTickReset( void )
// {
//     m_tick = 0u;
// }


// bool	MonitorTickTimeout( void )
// {
// 	const	uint32_t	Interval_set = 50;	//	5 sec.

// 	return	( m_tick >= Interval_set );	//	超时返回TRUE.
// }


// void	MonitorTickInit( void )
// {
//     m_tick = 0u;
// 	SysTick_Config( SystemCoreClock / 10 );	//	中断频率10Hz  //100ms
// }


// uint8_t HCBoxFlag = FALSE;
// __irq
// void	SysTick_Handler( void )
// {	
// 	static  uint32_t    HCBoxtick;
// 	uint32_t    tmp = m_tick + 1;
// 	
// 	if ( ( tmp != 0u ) )	//	未溢出
// 	{
// 		m_tick = tmp;
// 	}
// 	if( ( HCBoxtick ++ ) % 10 == 0 )
// 	{
// 		HCBoxFlag = TRUE;
// 	}
// }


// /*i2c*/


// BOOL	EE24C512_Save( uint16_t address, uint8_t const * buffer, uint8_t count )
// {
// 	// send sub address
// 	if ( ! bus_i2c_start( _SLAVE_24C512, I2C_Write ))   { bus_i2c_stop(); return FALSE; }
//     if ( ! bus_i2c_shout((uint8_t)( address / 0x100U ))){ bus_i2c_stop(); return FALSE; }
//     if ( ! bus_i2c_shout((uint8_t)( address % 0x100U ))){ bus_i2c_stop(); return FALSE; }

// 	// continue send write data.
//     do
// 	{
// 		if ( ! bus_i2c_shout((uint8_t)~(*buffer++))){	bus_i2c_stop(); return FALSE; 	}
// 	}
// 	while ( --count );

//     bus_i2c_stop();

//     // acknowledge polling.
// 	return	polling( _SLAVE_24C512 );	//	使用铁电存储器时，可以不用轮询, 但加上也无所谓。
// }

// BOOL	EE24C512_Load( uint16_t address, uint8_t * buffer, uint8_t count )
// {
// 	// send sub address
// 	if ( ! bus_i2c_start( _SLAVE_24C512, I2C_Write ))   { bus_i2c_stop(); return FALSE; }
// 	if ( ! bus_i2c_shout((uint8_t)( address / 0x100U ))){ bus_i2c_stop(); return FALSE; }
// 	if ( ! bus_i2c_shout((uint8_t)( address % 0x100U ))){ bus_i2c_stop(); return FALSE; }

// 	// Send read command and receive data.
// 	if ( ! bus_i2c_start( _SLAVE_24C512, I2C_Read ))	{ bus_i2c_stop(); return FALSE; }
// 	while ( --count )
// 	{
// 		*buffer++ =  (uint8_t)~bus_i2c_shin( I2C_ACK );	// Receive and send ACK
// 	}
// 	*buffer =  (uint8_t)~bus_i2c_shin( I2C_NoACK );		// Receive and send NoACK
// 	bus_i2c_stop();

// 	return TRUE;
// }


// /*pwm*/


// /********************************** 功能说明 ***********************************
// *	使用 TIM3 实现 PWM功能，输出范围固定：0 ~ PWM_Output_Max(通常是27648u)
// *******************************************************************************/
// #define	_TIM3_PWM_Period	2400u

// static	uint16_t	_TIM3_PWM_Regular( uint16_t OutValue )
// {
// 	return	(uint32_t)OutValue * _TIM3_PWM_Period / PWM_Output_Max;
// }

// static	void	TIM3_Init( void )
// {
// 	TIM_TypeDef	* TIMx = TIM3;

// 	SET_BIT( RCC->APB1ENR, RCC_APB1ENR_TIM3EN );
// 	//	TIMx 时基初始化: 输入时钟频率24MHz，PWM分辨率2400, PWM频率10KHz
// 	TIMx->CR1  = 0u;
// 	TIMx->PSC  = 0u;
// 	TIMx->ARR  = ( _TIM3_PWM_Period - 1u );
// 	TIMx->EGR  = TIM_EGR_UG;

// 	//	配置过程中暂时全部关闭输出
// 	TIMx->CCER = 0u;
// 	TIMx->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
// 				| TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
// 	TIMx->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1
// 				| TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
// 	TIMx->CCR1 = 0u;
// 	TIMx->CCR2 = 0u;
// 	TIMx->CCR3 = 0u;
// 	TIMx->CCR4 = 0u;

// //	SET_BIT( TIMx->CCER, TIM_CCER_CC3E );	//	T3CH3 接大气采样泵
// //	SET_BIT( TIMx->CCER, TIM_CCER_CC4E );	//	T3CH4 接制冷箱风扇
// 	//	TIMx 使能
// 	SET_BIT( TIMx->CR1, TIM_CR1_CEN );

// 	//	配置输出管脚
// 	SET_BIT( RCC->APB2ENR, RCC_APB2ENR_AFIOEN );
//  	MODIFY_REG( AFIO->MAPR, AFIO_MAPR_TIM3_REMAP, AFIO_MAPR_TIM3_REMAP_FULLREMAP );
// //	SET_BIT( RCC->APB2ENR, RCC_APB2ENR_IOPCEN );
// //	MODIFY_REG( GPIOC->CRL, 0x0F000000u, 0x0B000000u );		//	PC.6, T3CH1
// //	MODIFY_REG( GPIOC->CRL, 0xF0000000u, 0xB0000000u );		//	PC.7, T3CH2
// // 	MODIFY_REG( GPIOC->CRH, 0x0000000Fu, 0x0000000Bu );		//	PC.8, T3CH3
// // 	MODIFY_REG( GPIOC->CRH, 0x000000F0u, 0x000000B0u );		//	PC.9, T3CH4
// }


// /******************Edit**********************/

// /**************** (C) COPYRIGHT 2014 青岛金仕达电子科技有限公司 ****************
// * 文 件 名: Edit.C
// * 创 建 者: 董峰
// * 描  述  : 数字显示/编辑
// * 最后修改: 2014年8月25日
// *********************************** 修订记录 ***********************************
// * 版  本:
// * 修订人:
// *******************************************************************************/
// #include "BSP.H"
// #include "Edit.H"
// #include <time.h>
// #include <stdio.h>

// #define	K_INC	K_UP
// #define	K_DEC	K_DOWN

// /********************************** 功能说明 ***********************************
// *  显示时间
// *******************************************************************************/
// void	ShowClock( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;

//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, " %02u-%02u %02u:%02u:%02u ",
//              t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
//     Lputs( yx, sbuffer );
// }


// void	ShowClockDate( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;

//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, "%04u-%02u-%02u",  t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday );
//     Lputs( yx, sbuffer );

// }

// void	ShowClockTime( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;

//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, "%02u:%02u:%02u", t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
//     Lputs( yx, sbuffer );
// }

// static	uint8_t	dayOfmonth( uint16_t year, uint8_t month )
// {
//     switch( month )
//     {
//     default:
//     case  1:
//         return 31;
//     case  2:
//         return (((year%4)==0) ? 29 : 28 );
//     case  3:
//         return 31;
//     case  4:
//         return 30;
//     case  5:
//         return 31;
//     case  6:
//         return 30;
//     case  7:
//         return 31;
//     case  8:
//         return 31;
//     case  9:
//         return 30;
//     case 10:
//         return 31;
//     case 11:
//         return 30;
//     case 12:
//         return 31;
//     }
// }

// BOOL	EditClockDate( uint16_t yx, uClock * pClock )
// {
//     CHAR  	sbuffer[20];
//     struct tm t_tm;
//     uint16_t	year;
//     uint8_t 	month;
//     uint8_t 	day_m;
//     uint8_t 	option = 1u;

//     _localtime_r( pClock, &t_tm );
//     year  = t_tm.tm_year + 1900;
//     month = t_tm.tm_mon  + 1;
//     day_m = t_tm.tm_mday;

//     for(;;)
//     {
//         sprintf( sbuffer, "%04u-%02u-%02u", year, month, day_m );
//         Lputs( yx, sbuffer );

//         switch( option )
//         {
//         case 1:
//             LcmMask( yx  , 4 );
//             break;	// year
//         case 2:
//             LcmMask( yx+5, 2 );
//             break;	// month
//         case 3:
//             LcmMask( yx+8, 2 );
//             break;	// day_m
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 if ( ++year > 2099u )
//                 {
//                     year = 2000u;
//                 }
//                 break;
//             case 2:
//                 if ( ++month > 12u )
//                 {
//                     month = 1u;
//                 }
//                 break;
//             case 3:
//                 if ( ++day_m > dayOfmonth( year, month ))
//                 {
//                     day_m = 1u;
//                 }
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_DEC:
//             switch(  option )
//             {
//             case 1:
//                 if ( --year < 2000u )
//                 {
//                     year = 2099u;
//                 }
//                 break;
//             case 2:
//                 if ( --month < 1u )
//                 {
//                     month = 12u;
//                 }
//                 break;
//             case 3:
//                 if ( --day_m < 1u )
//                 {
//                     day_m = dayOfmonth( year, month );
//                 }
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++option > 3u )
//             {
//                 option = 1u;
//             }
//             break;

//         case K_LEFT:
//             if ( --option < 1u )
//             {
//                 option = 3u;
//             }
//             break;

//         case K_OK:
//             t_tm.tm_year = year  - 1900;
//             t_tm.tm_mon  = month - 1;
//             t_tm.tm_mday = day_m;
//             * pClock = mktime( &t_tm );
//             return	TRUE;

//         case K_ESC:
//             return	FALSE;

//         default:
//             break;
//         }
//     }
// }


// BOOL	EditClockTime( uint16_t yx, uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t;
//     uint8_t 	option = 1u;

//     _localtime_r( pClock, &t );

//     for(;;)
//     {
//         sprintf( sbuffer, "%02u:%02u:%02u", t.tm_hour, t.tm_min, t.tm_sec );
//         Lputs( yx, sbuffer );

//         switch( option )
//         {
//         case 1:
//             LcmMask( yx  , 2 );
//             break;  // hour
//         case 2:
//             LcmMask( yx+3, 2 );
//             break;  // minute
//         case 3:
//             LcmMask( yx+6, 2 );
//             break;  // second
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 t.tm_hour = ( t.tm_hour +  1u ) % 24u;
//                 break;
//             case 2:
//                 t.tm_min  = ( t.tm_min  +  1u ) % 60u;
//                 break;
//             case 3:
//                 t.tm_sec  = ( t.tm_sec  +  1u ) % 60u;
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_DEC:
//             switch( option )
//             {
//             case 1:
//                 t.tm_hour = ( t.tm_hour + 23u ) % 24u;
//                 break;
//             case 2:
//                 t.tm_min  = ( t.tm_min  + 59u ) % 60u;
//                 break;
//             case 3:
//                 t.tm_sec  = ( t.tm_sec  + 59u ) % 60u;
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++option > 3u )
//             {
//                 option = 1;
//             }
//             break;

//         case K_LEFT:
//             if ( --option < 1u )
//             {
//                 option = 3u;
//             }
//             break;

//         case K_OK:
//             * pClock = mktime( &t );
//             return	TRUE;

//         case K_ESC:
//             return	FALSE;

//         default:
//             break;
//         }
//     }
// }

// ///////////////////////////////////////////////////////////////////
// // 设置采样时间参数
// ///////////////////////////////////////////////////////////////////
// void	ShowDATE( uint16_t yx, uint32_t timer )
// {
//     CHAR	sbuffer[20];
//     struct tm t;

//     _localtime_r( &timer, &t );
//     sprintf( sbuffer, "%2d-%2d %02d:%02d", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min );
//     Lputs( yx, sbuffer );
// }

// void	ShowTIME( uint16_t yx, uint16_t Time )
// {
//     CHAR	sbuffer[20];
//     uint8_t	hour   = ( Time / 60u );
//     uint8_t	minute = ( Time % 60u );

//     sprintf( sbuffer, "%02u:%02u", hour, minute );
//     Lputs( yx, sbuffer );
// }

// BOOL	EditTIME( uint16_t yx, uint16_t * pTime )
// {
//     uint8_t hour   = (( *pTime / 60u ) % 100u );
//     uint8_t minute = (  *pTime % 60u );
//     BOOL	changed = FALSE;
//     uint8_t option = 1u;

//     do
//     {
//         ShowTIME( yx, (( hour * 60u ) + minute ));
//         switch( option )
//         {
//         case 1:
//             LcmMask( yx + 0u, 1u );
//             break;  // 10 hour
//         case 2:
//             LcmMask( yx + 1u, 1u );
//             break;  //  1 hour
//         case 3:
//             LcmMask( yx + 3u, 1u );
//             break;  // 10 minute
//         case 4:
//             LcmMask( yx + 4u, 1u );
//             break;  //  1 minute
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 hour   = (  hour  + 10u ) % 100;
//                 break;
//             case 2:
//                 hour   = (( hour  / 10u ) * 10u ) + (( hour   + 1u ) % 10u );
//                 break;
//             case 3:
//                 minute = ( minute + 10u ) % 60u;
//                 break;
//             case 4:
//                 minute = ((minute / 10u ) * 10u ) + (( minute + 1u ) % 10u );
//                 break;
//             default:
//                 break;
//             }
//             break;
//         case K_DEC:
//             switch( option )
//             {
//             case 1:
//                 hour   = (  hour   + 90u ) % 100u;
//                 break;
//             case 2:
//                 hour   = (( hour   / 10u ) * 10u ) + (( hour   + 9u ) % 10u );
//                 break;
//             case 3:
//                 minute = (  minute + 50u ) % 60u;
//                 break;
//             case 4:
//                 minute = (( minute / 10u ) * 10u ) + (( minute + 9u ) % 10u );
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++ option > 4u )
//             {
//                 option = 1u;
//             }
//             break;

//         case K_LEFT:
//             if ( -- option < 1u )
//             {
//                 option = 4u;
//             }
//             break;

//         case K_OK:
//             *pTime = ( hour * 60u ) + minute;
//             changed = TRUE;
//             option = 0u;
//             break;

//         case K_ESC:
//             changed = FALSE;
//             option = 0u;
//             break;

//         default:
//             break;
//         }
//     }
//     while ( 0u != option );

//     return	changed;
// }

// ///////////////////////////////////////////////////////////////////
// static	uint32_t const	tbl_pow10_I32U[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
// static	FP32	const	tbl_pow10_FP32[] = { 1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8, 1E9 };

// void	ShowFP32( uint16_t yx, FP32   NumFP32, uint16_t fmt, const CHAR * Unit )
// {
//     CHAR	sbuffer[20];

//     sprintf( sbuffer, "%*.*f", fmt / 0x100, fmt % 0x100, NumFP32 );
//     Lputs( yx, sbuffer );
//     if( Unit )
//     {
//         Lputs( yx + strlen( sbuffer ), Unit );
//     }
// }

// void	ShowI16U( uint16_t yx, uint16_t NumI16U, uint16_t fmt, const CHAR * Unit )
// {
//     FP32	NumFP32 = NumI16U / tbl_pow10_FP32[ fmt % 0x100 ];
//     CHAR	sbuffer[20];

//     sprintf( sbuffer, "%*.*f", fmt / 0x100, fmt % 0x100, NumFP32 );
//     Lputs( yx, sbuffer );
//     if( Unit )
//     {
//         Lputs( yx + strlen( sbuffer ), Unit );
//     }
// }

// void	ShowPercent( uint16_t yx, FP32 percent )
// {
//     ShowFP32( yx, percent * 100.0f, 0x0501u, "%" );
// }

// void	ShowHEX16( uint16_t yx, uint16_t hex16 )
// {
//     CHAR	sbuffer[10];

//     sprintf( sbuffer, "%04X", hex16 );

//     Lputs( yx, sbuffer );
// }
// //	#if 0
// //		uint32_t  PowN = 0;
// //		uint32_t  password = 0UL;
// //		uint8_t  choice = 0U;						//	用户输入位置从0开始
// //		uKey  keyin;
// //		uint16_t  yx = 0x0305u;
// //		CHAR	sbuffer[20];

// //		cls();
// //		Lputs( 0x0000U, "输入密码: " );

// //		for (;;)
// //		{
// //			sprintf( sbuffer, "%06u", password );
// //			Lputs( yx, sbuffer );

// //			LcmMask( yx + choice, 1 );				//	移到光标到输入位置

// //			keyin = getKey();

// //			PowN = tbl_pow10_I32U[5-choice];

// //			switch( keyin )
// //			{
// //	//			case K_RIGHT:
// //	//				choice = ( choice + 1U ) % 6U;
// //	//				break;
// //	//			case K_LEFT:
// //	//				choice = (( choice - 1U ) + 6U ) % 6U;
// //	//				break;

// //	//			case K_XCH:	 choice = (choice + 1) % 6;	break;

// //			case K_INC:
// //				if ( password / PowN % 10 == 9 )
// //				{
// //					password -= PowN * 9;
// //				}
// //				else
// //				{
// //					password += PowN;
// //				}
// //				break;

// //			case K_DEC:
// //				if ( password / PowN % 10 == 0 )
// //				{
// //					password += PowN * 9;
// //				}
// //				else
// //				{
// //					password -= PowN;
// //				}
// //				break;

// //			case K_RIGHT:
// //				choice = ( choice + 1 ) % 6;
// //				break;

// //			case K_LEFT:
// //				choice = ( choice + 6 - 1 ) % 6;
// //				break;

// //			case K_OK:
// //				return  password;

// //			case K_ESC:
// //				return  0;

// //			default:
// //				break;
// //			}
// //		}
// //	#endif

// 	
// ///////////////////////////////////////////////////////////////////
// BOOL	EditI32U( uint16_t yx, uint32_t * pNUM, uint16_t fmt )
// {
//     uint32_t	PowN;
//     uint32_t	Num = *pNUM;
//     uint8_t 	M, N, choice = 0u;
//     CHAR		sbuffer[20];

//     N = fmt % 0x100u;										//	小数点后的有效位数
//     M = ( N == 0 ) ? ( fmt / 0x100 ) : ( fmt / 0x100 - 1 );	//	有效位数, 即choice 变化范围
//     Num = Num % tbl_pow10_I32U[M];							//	保留低位, 清零高位

//     for (;;)
//     {
//         sprintf( sbuffer, "%0*.*f", ( fmt / 0x100 ), ( fmt % 0x100 ), Num / tbl_pow10_FP32[N] );
//         Lputs( yx, sbuffer );

// 			if ( choice < ( M - N ))
// 			{
// 						LcmMask( yx + choice, 1 );		//	输入位置在小数点之前
// 			}
// 			else
// 			{
//             LcmMask( yx + choice + 1, 1 );	//	输入位置在小数点之后
// 			}

//         if (  M >= ( choice + 1u ))
//         {
//             PowN = tbl_pow10_I32U[ M - ( choice + 1u )];
//         }
//         else
//         {
//             PowN = 1u;
//         }

//         switch ( getKey() )
//         {
//         case K_INC:
//             if( Num / PowN % 10 == 9 )
//             {
//                 Num -= PowN * 9;
//             }
//             else
//             {
//                 Num += PowN;
//             }
//             break;
//         case K_DEC:
//             if( Num / PowN % 10 == 0 )
//             {
//                 Num += PowN * 9;
//             }
//             else
//             {
//                 Num -= PowN;
//             }
//             break;
//         case K_RIGHT:
//         //case K_XCH:
//             choice = ( choice + 1 ) % M;
//             break;

//         case K_LEFT:
//             choice = ( choice + M - 1 ) % M;
//             break;

//         case K_OK:
//             *pNUM = Num;
//             return TRUE;
//         case K_ESC:
//             return FALSE;
//         default:
//             break;
//         }
//     }
// }

// BOOL	EditI16U( uint16_t yx, uint16_t * pNUM, uint16_t fmt )
// {
// 	uint32_t	Num = *pNUM;
// 	
// 	if ( ! EditI32U( yx, &Num, fmt ))
// 	{
// 		return  false;
// 	}
// 	
// 	*pNUM = (uint16_t)Num;
// 	return  true;	
// }

// ///////////////////////////////////////////////////////////////////
// // 输入密码
// ///////////////////////////////////////////////////////////////////

// uint32_t	InputPassword( void )
// {
// 	uint32_t	password = 0u;
// 	
// 	cls();
// 	Lputs( 0x0000u, "输入密码:" );
// 	
// 	if ( ! EditI32U( 0x0305u, &password, 0x0600u ))
// 	{
// 		return  0u;
// 	}
// 	return  password;
// }

// /********  (C) COPYRIGHT 2014 青岛金仕达电子科技有限公司  **** End Of File ****/
// /**********************Menu******************************/

// /**************** (C) COPYRIGHT 2013 青岛金仕达电子科技有限公司 ****************
// * 文 件 名: Menu.C
// * 创 建 者: 董峰
// * 描  述  : 菜单显示/选择
// * 最后修改: 2013年8月17日
// *********************************** 修订记录 ***********************************
// * 版  本: 
// * 修订人: 
// *******************************************************************************/
// #include "BSP.H"
// #include <stm32f10x.h>
// #include "Edit.H"
// #include <stdio.h>
// #define	LOBYTE(__w)		((uint8_t)((__w)&0x0FF))
// #define	HIBYTE(__w)		((uint8_t)(((__w)>>8)&0x0FF))

// ///////////////////////////////////////////////////////////////////
// //	菜单绘制/选择
// ///////////////////////////////////////////////////////////////////
// void	Menu_Item_Mask ( const struct uMenu * menu, uint8_t item )
// {
// 	LcmMask ( menu[item].yx, strlen ( menu[item].sz ) );
// }

// void	Menu_Redraw ( const struct uMenu * menu )
// {
//     uint8_t	mlen, mlen_row, mlen_col;
//     uint8_t	i;

//     mlen_row = HIBYTE ( menu[0].yx );
//     mlen_col = LOBYTE ( menu[0].yx );

//     if ( 0u == mlen_row )
//     {
//         mlen = mlen_col;
//     }
//     else
//     {
//         mlen = mlen_row * mlen_col;
//     }

//     if ( menu[0].sz != NULL )
//     {
//         Lputs ( 0x0000u, menu[0].sz );	// 显示菜单标题
//     }

//     for ( i = 1u; i <= mlen; ++i )
//     {
//         Lputs ( menu[i].yx, menu[i].sz );
//     }
// }

// uint8_t	Menu_Select ( const struct uMenu * menu, uint8_t item )
// {
// 	return	Menu_Select_Ex( menu, item, NULL );
// }
// uint8_t	Menu_Select2 ( const struct uMenu * menu, uint8_t item, BOOL Direction )  //可换向
// {
// 	return	Menu_Select_Ex2( menu, item, NULL, Direction );
// }
// uint8_t	Menu_Select3 ( const struct uMenu * menu, uint8_t item, uint8_t timeout )         //可超时关闭
// {
// 	return	Menu_Select_Ex3( menu, item, NULL, timeout);
// }
// uint8_t	Menu_Select_Ex ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ) )
// {
// 	uint8_t	mlen, mlen_row, mlen_col;

// 	mlen_row = HIBYTE ( menu[0].yx );
// 	mlen_col = LOBYTE ( menu[0].yx );

// 	if ( 0u == mlen_row )
// 	{
// 		mlen = mlen_col;
// 	}
// 	else
// 	{
// 		mlen = mlen_row * mlen_col;
// 	}

// 	if ( ( item < 1u ) || ( item > mlen ) )
// 	{
// 		item = 1u;
// 	}

// 	for ( ; ; )
// 	{
// 		LcmMask ( menu[item].yx, strlen ( menu[item].sz ) );
// 		do
// 		{
// 			if ( NULL != pHook )
// 			{
// 				pHook();
// 			}
// 		}
// 		while ( ! hitKey ( 50u ) );

// 		Lputs ( menu[item].yx, menu[item].sz );

// 		switch ( getKey() )
// 		{
// 		case K_RIGHT:
// 			if ( 0 == ( item % mlen_col ) )
// 			{
// 				item -= mlen_col;
// 			}
// 			++item;
// 			break;

// 		case K_LEFT:
// 			--item;
// 			if ( 0 == ( item % mlen_col ) )
// 			{
// 				item += mlen_col;
// 			}
// 			break;

// 		case K_DOWN:
// 			item += mlen_col;
// 			if ( item > mlen )
// 			{
// 				item -= mlen;
// 			}
// 			break;

// 		case K_UP:
// 			if ( item <= mlen_col )
// 			{
// 				item += mlen;
// 			}
// 			item -= mlen_col;
// 			break;

// 		case K_OK:
// 			return	item;

// 		case K_ESC:
// 			return	enumSelectESC;

// 		case K_SHIFT:		
// 			return	enumSelectXCH;
// 		
// 		default:
// 			break;
// 		}
// 	}
// }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// uint8_t	Menu_Select_Ex2 ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ),BOOL Direction ) 
// {                                                                                           //TRUE 改纵向  FALSE 改横向 
// 	uint8_t	mlen, mlen_row, mlen_col;
// 	BOOL Flag = FALSE;
// 	mlen_row = HIBYTE ( menu[0].yx );
// 	mlen_col = LOBYTE ( menu[0].yx );

// 	if ( 0u == mlen_row )
// 	{
// 		mlen = mlen_col;
// 	}
// 	else
// 	{
// 		mlen = mlen_row * mlen_col;
// 	}

// 	if ( ( item < 1u ) || ( item > mlen ) )
// 	{
// 		item = 1u;
// 	}

// 	for ( ; ; )
// 	{
// 		LcmMask ( menu[item].yx, strlen ( menu[item].sz ) );
// 		do
// 		{
// 			if ( NULL != pHook )
// 			{
// 				pHook();
// 			}
// 		}
// 		while ( ! hitKey ( 50u ) );

// 		Lputs ( menu[item].yx, menu[item].sz );

// 		switch ( getKey() )
// 		{
// 				
// 		case K_RIGHT:
// 		  if((!Direction) && (!Flag))	
// 			{
// 				item += mlen_col;
// 				if ( item > mlen )
// 				{
// 					item -= mlen;
// 				}
// 			}
// 			else
// 			{
// 				if ( 0 == ( item % mlen_col ) )
// 				{
// 					item -= mlen_col;
// 				}
// 				++item;
// 			}
// 			
// 			break;

// 		case K_LEFT:
// 			if((!Direction) && (!Flag))
// 			{
// 				if ( item <= mlen_col )
// 				{
// 					item += mlen;
// 				}
// 				item -= mlen_col;
// 			}
// 			else
// 			{
// 				--item;
// 				if ( 0 == ( item % mlen_col ) )
// 				{
// 					item += mlen_col;
// 				}
// 			}		
// 			break;
// 			
// 		case K_DOWN:
// 			if( Direction && (!Flag) )
// 			{
// 				 if ( 0 == ( item % mlen_col ) )
// 				{
// 					item -= mlen_col;
// 				}
// 				++item;
// 			}		
// 			else
// 			{
// 				item += mlen_col;
// 				if ( item > mlen )
// 				{
// 					item -= mlen;
// 				}
// 			}
// 			break;
// 		case K_UP:
// 			if( Direction && (!Flag) )
// 			{
// 				--item;
// 				if ( 0 == ( item % mlen_col ) )
// 				{
// 					item += mlen_col;
// 				}
// 			}		
// 			else
// 			{
// 				if ( item <= mlen_col )
// 				{
// 					item += mlen;
// 				}
// 				item -= mlen_col;
// 			}
// 			break;

// 		case K_OK:
// 			Flag = TRUE;
// 			return	item;

// 		case K_ESC:
// 			Flag = FALSE;
// 			return	enumSelectESC;

// 		case K_SHIFT:		
// 			return	enumSelectXCH;
// 		
// 		default:
// 			break;
// 		}
// 	}
// }
// uint8_t	Menu_Select_Ex3 ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ),uint8_t timeout )
// {  
// 	uint8_t	mlen, mlen_row, mlen_col;
// 	uint8_t secnow;
// 	uint32_t starsec; 
// 	mlen_row = HIBYTE ( menu[0].yx );
// 	mlen_col = LOBYTE ( menu[0].yx );
// 	if ( 0u == mlen_row )
// 	{
// 		mlen = mlen_col;
// 	}
// 	else
// 	{
// 		mlen = mlen_row * mlen_col;
// 	} 

// 	if ( ( item < 1u ) || ( item > mlen ) )
// 	{
// 		item = 1u;
// 	} 
// 	starsec = get_Now();
// 	for ( ; ; )
// 	{ 
// 		LcmMask ( menu[item].yx, strlen ( menu[item].sz ) );   
// 		do
// 		{
// 			if ( NULL != pHook )
// 			{
// 				pHook();
// 			}    
// 			secnow = get_Now() - starsec;
// 			if( secnow >= timeout ) 
// 				return 1;				
// 				
// 		}
// 		while ( ! hitKey ( 50u ) );
// 		Lputs ( menu[item].yx, menu[item].sz );
//   
// 		switch ( getKey() )
// 		{
// 		case K_RIGHT:
// 			if ( 0 == ( item % mlen_col ) )
// 			{
// 				item -= mlen_col;
// 			}
// 			++item;
// 			break;

// 		case K_LEFT:
// 			--item;
// 			if ( 0 == ( item % mlen_col ) )
// 			{
// 				item += mlen_col;
// 			}
// 			break;

// 		case K_DOWN:
// 			item += mlen_col;
// 			if ( item > mlen )
// 			{
// 				item -= mlen;
// 			}
// 			break;

// 		case K_UP:
// 			if ( item <= mlen_col )
// 			{
// 				item += mlen;
// 			}
// 			item -= mlen_col;
// 			break;

// 		case K_OK:
// 			return	item;

// 		case K_ESC:
// 			return	enumSelectESC;

// 		case K_SHIFT:		
// 			return	enumSelectXCH;
// 		
// 		default:
// 			break;
// 		}
// 	}
// }
// //		///////////////////////////////////////////////////////////////////
// //		//	模拟VB的MsgBox函数
// //		///////////////////////////////////////////////////////////////////
// //		//	buttons 参数有下列设置值：
// //		//	vbOKOnly			0 只显示 OK 按钮。
// //		//	vbOKCancel			1 显示 OK 及 Cancel 按钮。
// //		//	vbAbortRetryIgnore	2 显示 Abort、Retry 及 Ignore 按钮。
// //		//	vbYesNoCancel		3 显示 Yes、No 及 Cancel 按钮。
// //		//	vbYesNo				4 显示 Yes 及 No 按钮。
// //		//	vbRetryCancel		5 显示 Retry 及 Cancel 按钮。
// //		//
// //		//	vbDefaultButton1	0x00 第一个按钮是缺省值。
// //		//	vbDefaultButton2	0x10 第二个按钮是缺省值。
// //		//	vbDefaultButton3	0x20 第三个按钮是缺省值。
// //		//	vbDefaultButton4	0x30 第四个按钮是缺省值。

// //		//	返回值
// //		//	0x00	K_ESC press
// //		//	vbOK		1 OK
// //		//	vbCancel	2 Cancel
// //		//	vbAbort		3 Abort
// //		//	vbRetry		4 Retry
// //		//	vbIgnore	5 Ignore
// //		//	vbYes		6 Yes
// //		//	vbNo 		7 No

// //		//	enum {
// //		//		vbOKOnly,
// //		//		vbOKCancel,
// //		//		vbAbortRetryIgnore,
// //		//		vbYesNoCancel,
// //		//		vbYesNo,
// //		//		vbRetryCancel,
// //		//	};
// //		//	enum {
// //		//		vbDefaultButton1 = 0x00,	//	 第一个按钮是缺省值。
// //		//		vbDefaultButton2 = 0x10,	//	 第二个按钮是缺省值。
// //		//		vbDefaultButton3 = 0x20,	//	 第三个按钮是缺省值。
// //		//		vbDefaultButton4 = 0x30,	//	 第四个按钮是缺省值。
// //		//	};

// //		//	MsgBox的返回值
// //		//	enum {	vbOK, vbCancel, vbAbort, vbRetry, vbIgnore, vbYes, vbNo }
// //		uint8_t	MsgBox ( const char * szPrompt, uint16_t buttons )
// //		{
// //			static	const struct uMenu  menu_OKOnly[]			= { 0x0101u, NULL, 0x050B, "确定" };
// //			static	const struct uMenu  menu_OKCancel[]			= { 0x0102u, NULL, 0x0503, "确定", 0x0509, "取消" };
// //			static	const struct uMenu  menu_YesNo[]			= { 0x0102u, NULL, 0x0503, " 是 ", 0x0509, " 否 " };
// //			static	const struct uMenu  menu_RetryCancel[]		= { 0x0102u, NULL, 0x0503, "重试", 0x0509, "取消" };
// //			static	const struct uMenu  menu_YesNoCancel[]		= { 0x0103u, NULL, 0x0501, " 是 ", 0x0506, " 否 ", 0x050B, "取消" };
// //			static	const struct uMenu  menu_AbortRetryIgnore[]	= { 0x0103u, NULL, 0x0501, "终止", 0x0506, "重试", 0x050B, "忽略" };

// //			static	const struct uMenu * const menu_lst[] =
// //			{
// //				menu_OKOnly,
// //				menu_OKCancel,
// //				menu_AbortRetryIgnore,
// //				menu_YesNoCancel,
// //				menu_YesNo,
// //				menu_RetryCancel
// //			};
// //			const struct uMenu * menu;
// //			uint8_t	Response;

// //			cls();
// //			//	if( szTitle  != NULL )	Lputs( 0x0000u, szTitle );
// //			if ( szPrompt != NULL )
// //			{
// //				Lputs ( 0x0000u, szPrompt );
// //			}

// //			menu = menu_lst[buttons & 0x0F];
// //			Menu_Redraw ( menu );
// //			Response = Menu_Select ( menu, buttons / 0x10 % 0x10 + 1 );	//	Menu_Select程序会自动调整不合理的默认选项
// //			switch ( buttons & 0x0F )
// //			{
// //			default:
// //			case vbOKOnly:				switch ( Response )
// //				{
// //				default:	return	vbCancel;
// //				case 1:		return	vbOK;
// //				}
// //				//	break;
// //			case vbOKCancel:			switch ( Response )
// //				{
// //				default:	return	vbCancel;
// //				case 1:		return	vbOK;
// //					//	case 2:		return	vbCancel;
// //				}
// //				//	break;
// //			case vbAbortRetryIgnore:	switch ( Response )
// //				{
// //				default:	return	vbRetry;
// //				case 1:		return	vbAbort;
// //					//	case 2:		return	vbRetry;
// //				case 3:		return	vbIgnore;
// //				}
// //				//	break;
// //			case vbYesNoCancel:			switch ( Response )
// //				{
// //				default:	return	vbCancel;
// //				case 1:		return	vbYes;
// //				case 2:		return	vbNo;
// //					//	case 3:		return	vbCancel;
// //				}
// //				//	break;
// //			case vbYesNo:				switch ( Response )
// //				{
// //				default:	return	vbCancel;
// //				case 1:		return	vbYes;
// //				case 2:		return	vbNo;
// //				}
// //				//	break;
// //			case vbRetryCancel:			switch ( Response )
// //				{
// //				default:	return	vbCancel;
// //				case 1:		return	vbRetry;
// //					//	case 2:		return	vbCancel;
// //				}
// //				//	break;
// //			}
// //		}

// //		///////////////////////////////////////////////////////////////////
// //		//	uint8_t	Confirm( const char const * prompt ){
// //		//	//	struct	uMenu const menu[] = {
// //		//	//		0x03, NULL, 0x0501, "是", 0x0505, "否", 0x050A, "取消",
// //		//	//	};
// //		//	//	cls();	Lputs( 0x0000, prompt );
// //		//	//	Menu_Redraw( menu );
// //		//	//	return	Menu_Select( menu, 3 );
// //		//
// //		//		return	MsgBox( prompt, vbYesNoCancel + vbDefaultButton3 );
// //		//	}
// //		///////////////////////////////////////////////// End of File /////




// ///////////////////////////////////////////////////////////////////
// //	模拟VB的MsgBox函数
// ///////////////////////////////////////////////////////////////////
// uint8_t	MsgBox( const CHAR  * sPrompt, uint16_t buttons )
// {
// 	static	const struct uMenu  menu_OKOnly[]			= { 0x0101u, NULL, 0x050B, "确定" };
// 	static	const struct uMenu  menu_OKCancel[]			= { 0x0102u, NULL, 0x0503, "确定", 0x0509, "取消" };
// 	static	const struct uMenu  menu_YesNo[]			= { 0x0102u, NULL, 0x0503, " 是 ", 0x0509, " 否 " };
// 	static	const struct uMenu  menu_RetryCancel[]		= { 0x0102u, NULL, 0x0503, "重试", 0x0509, "取消" };
// 	static	const struct uMenu  menu_YesNoCancel[]		= { 0x0103u, NULL, 0x0501, " 是 ", 0x0506, " 否 ", 0x050B, "取消" };
// 	static	const struct uMenu  menu_AbortRetryIgnore[]	= { 0x0103u, NULL, 0x0501, "终止", 0x0506, "重试", 0x050B, "忽略" };

// 	static	const struct uMenu * const menu_list[] = 
// 	{
// 		menu_OKOnly,
// 		menu_OKCancel,
// 		menu_AbortRetryIgnore,
// 		menu_YesNoCancel,
// 		menu_YesNo,
// 		menu_RetryCancel
// 	};
// 	const struct uMenu * menu;
// 	uint8_t	Response;

// 	if( sPrompt != NULL )
// 	{
// 		cls();
// 		Lputs( 0x0000, sPrompt );
// 	}

// 	menu = menu_list[buttons & 0x0Fu];
// 	Menu_Redraw( menu );
// 	Response = Menu_Select( menu, buttons / 0x10 % 0x10 + 1 );	//	Menu_Select程序会自动调整不合理的默认选项

// 	switch( buttons & 0x0Fu )
// 	{
// 	default:
// 	case vbOKOnly:
// 		switch( Response )
// 		{
// 			default:	return	vbCancel;
// 			case 1:		return	vbOK;
// 		}
// 		//	break;
// 	case vbOKCancel:
// 		switch( Response )
// 		{
// 			default:	return	vbCancel;
// 			case 1:		return	vbOK;
// 		//	case 2:		return	vbCancel;
// 		}
// 		//	break;
// 	case vbAbortRetryIgnore:
// 		switch( Response )
// 		{
// 			default:	return	vbRetry;
// 			case 1:		return	vbAbort;
// 		//	case 2:		return	vbRetry;
// 			case 3:		return	vbIgnore; 
// 		}
// 		//	break;
// 	case vbYesNoCancel:
// 		switch( Response )
// 		{
// 			default:	return	vbCancel;
// 			case 1:		return	vbYes;
// 			case 2:		return	vbNo;
// 		//	case 3:		return	vbCancel;
// 		}
// 		//	break;
// 	case vbYesNo:
// 		switch( Response )
// 		{
// 			default:	return	vbCancel;
// 			case 1:		return	vbYes;
// 			case 2:		return	vbNo;
// 		}
// 		//	break;
// 	case vbRetryCancel:
// 		switch( Response )
// 		{
// 			default:	return	vbCancel;
// 			case 1:		return	vbRetry;
// 		//	case 2:		return	vbCancel;
// 		}
// 		//	break;
// 	}
// }
// /***************************************/
// //菜单模板
// // static	struct uMenu  const  menu[] =
// // 	{
// // 		{ 0x0201u, "" },
// // 		{ 0x0300u, "" },
// // 		{ 0x0500u, "" },
// // 	};
// // 	uint8_t item = 1u;	
// // 	cls();
// // 	Menu_Redraw( menu );
// // 	do {
// // 		item = Menu_Select( menu, item ,FALSE);

// // 		switch ( item )
// // 		{
// // 		case 1:
// // 			break;
// // 		case 2:
// // 			break;
// // 		}
// // 	} while ( enumSelectESC != item );
// // 	
// // 	}
// /********  (C) COPYRIGHT 2013 青岛金仕达电子科技有限公司  **** End Of File ****/

// /****************************按键***********************/
// #include "BSP.H"
// #include "BIOS.H"
// #include <cmsis_os.h>

// static	BOOL		KeyHited;
// static	uKey		KeyDirect;
// static	uKey		KeyBuffer;
// /********************************** 功能说明 ***********************************
// *	按键访问接口
// *******************************************************************************/
// osSemaphoreId semiKeyHited;		//	有新按键按下（按键处理程序发送，使用者接收）

// uKey	getKey( void )
// {
// 	uKey  KeyRead;

// 	if ( ! KeyHited )
// 	{	//	等待按键信号
// 		osSemaphoreWait( semiKeyHited, osWaitForever );
// 	}
// 	
// 	KeyRead = KeyBuffer;
// 	KeyHited = FALSE;
// 	tick();
// 	return	KeyRead;
// }

// BOOL	hitKey( uint16_t iRetry )
// {
// 	if ( ! KeyHited )
// 	{	//	等待按键信号
// 		osSemaphoreWait( semiKeyHited, iRetry * 10u );
// 	}
// 	
// 	return	KeyHited;
// }

// BOOL	releaseKey( uKey lastKey, uint16_t iRetry )
// {
// 	while( iRetry-- )
// 	{
// 		if ( lastKey != KeyDirect )
// 		{
// 			break;
// 		}
// 		delay( 10u );
// 	}
// 	return	( lastKey != KeyDirect ) ? TRUE : FALSE;
// }

// /********************************** 功能说明 ***********************************
// *	按键扫描事件
// *******************************************************************************/
// osSemaphoreId	semiKeyChanged;	//	按键状态变化（由管脚变化中断发送，按键处理程序接收）

// static	void	KeyboardStateChanged_Post( void )
// {
// 	osSemaphoreRelease( semiKeyChanged );
// }

// /********************************** 功能说明 ***********************************
// *	按键中断处理	使用中断检测按键的变化，可以节省大量的查询时间
// *******************************************************************************/
// void	Keyboard_IRQ_Server( void )
// {
// 	Keyboard_IRQ_Disable();				//	禁止按键变化中断
// 	KeyboardStateChanged_Post();		//  发信号给按键扫描任务
// }









// volatile	uint32_t	TimeoutLight = 0u;

// void		DisplaySetTimeout( uint8_t setTimeout )
// {
// 	switch ( setTimeout )
// 	{
// 	case 0:	TimeoutLight = 0u;			break;
// 	case 1:	TimeoutLight = 15 * 1000u;	break;
// 	case 2:	TimeoutLight = 30 * 1000u;	break;
// 	case 3:	TimeoutLight = 60 * 1000u;	break;
// 	default:
// 	case 4:	TimeoutLight = osWaitForever;	break;
// 	}
// }

// static	void	KeyboardStateChanged_Poll( void )
// {
// 	int32_t	result;
// 	
// 	switch ( TimeoutLight )
// 	{
// 	case 0u:
// 		Backlight_OFF();
// 		osSemaphoreWait( semiKeyChanged, osWaitForever );
// 		break;
// 	case osWaitForever:
// 		Backlight_ON();
// 		osSemaphoreWait( semiKeyChanged, osWaitForever );
// 		break;
// 	default:
// 		Backlight_ON();
// 		result = osSemaphoreWait( semiKeyChanged, TimeoutLight );

// 		if (  result <= 0 )
// 		{	//	没有等到信号量，那么应该是超时时间到了，关闭背光。
// 			Backlight_OFF();
// 			osSemaphoreWait( semiKeyChanged, osWaitForever );
// 		}
// 		break;
// 	}
// }


// /********************************** 功能说明 ***********************************
// *	按键扫描接口
// *******************************************************************************/
// __task	void	_task_Keyboard( void const * p_arg )
// {
// 	uKey	keyPortState, keyDebounce;

// 	( void )p_arg;
// 	delay( 100u );

// 	Keyboard_PortInit();
// 	for (;;)
// 	{
// 		Keyboard_IRQ_Enable();			//	允许按键变化触发中断
// 		

// 		delay( 20u );					//	等待按键状态稳定后再读
// 		keyPortState = Keyboard_PortRead();
// 		KeyboardStateChanged_Poll();	//	等待按键变化事件信号
// 		do 
//     {
// 			keyDebounce = keyPortState;
// 			delay( 20u );
// 			keyPortState = Keyboard_PortRead();
// 		} while ( keyDebounce != keyPortState );

// 		KeyDirect = keyDebounce;		//	保存扫描结果
// 		
// 		//	新的按键入队并告知主程序有新的按键按下。
// 		if ( ! KeyHited )
// 		{
// 			if ( KeyBuffer < KeyDirect )
// 			{
// 				KeyHited = TRUE;
// 			}
// 			KeyBuffer = KeyDirect;

// 			if ( KeyHited )
// 			{	//	向等待按键的任务发信号
// 				osSemaphoreRelease( semiKeyHited );
// 			}
// 		}
// 	}
// }

// /********************************** 功能说明 ***********************************
// *	按键扫描系列初始化
// *******************************************************************************/
// osThreadDef( _task_Keyboard, osPriorityAboveNormal, 1u, 100u );
// osSemaphoreDef( KeyChanged );
// osSemaphoreDef( KeyHited );

// void	Keyboard_Init( void )
// {
// 	semiKeyChanged = osSemaphoreCreate(osSemaphore( KeyChanged ), 0 );
// 	semiKeyHited = osSemaphoreCreate(osSemaphore( KeyHited ), 0 );
// 	osThreadCreate( osThread( _task_Keyboard ), NULL );
// }

// __irq	void	EXTI0_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// __irq	void	EXTI1_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// __irq	void	EXTI2_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// __irq	void	EXTI3_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// __irq	void	EXTI4_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// __irq	void	EXTI9_5_IRQHandler( void )
// {
// 	Keyboard_IRQ_Server();
// }

// /**************** (C) COPYRIGHT 2014 青岛金仕达电子科技有限公司 ****************
// * 文 件 名: 
// * 创 建 者:  
// * 描  述  :  
// * 最后修改:  
// *********************************** 修订记录 ***********************************/
// #include "stm32f10x.h"
// #include "bkpdata.h"
// #include "BIOS.H"

// void BKP_Write (uint16_t BKP_DR, uint16_t Data)
// {
//   __IO uint32_t tmp = 0;
//   tmp = (uint32_t)BKP_BASE; 
//   tmp += BKP_DR;
//   *(__IO uint32_t *) tmp = Data;
// }

// uint16_t BKP_Read (uint16_t BKP_DR)
// {
//   __IO uint32_t tmp = 0;
//   tmp = (uint32_t)BKP_BASE; 
//   tmp += BKP_DR;
//   return (*(__IO uint16_t *) tmp);
// }

// void BKPConfig(void)
// { 	
// 	RCC->APB1ENR|=1<<27; //bkp时钟
// 	RCC->APB1ENR|=1<<28; //后备电源时钟
// 	PWR->CR|=1<<8;//	
// }

// void Powertime_Write( uint32_t Data,uint8_t state)
// {
// 	uint16_t DataH,DataL;
// 	DataH = Data>>16;
// 	DataL = Data;
//   BKP_Write( BKP_DR3 , DataH );
//   BKP_Write( BKP_DR4 , DataL );

// }

// uint32_t Powertime_Read( uint8_t state )
// {
// 	uint32_t Dataout=0;
//   Dataout  = BKP_Read(BKP_DR3);
//   Dataout <<= 16;
//   Dataout |= BKP_Read(BKP_DR4); 
// 	return Dataout; 
// }
// #define	K_INC	K_UP
// #define	K_DEC	K_DOWN
// struct RTCtm {
//     int		sec;   /* seconds after the minute, 0 to 60
//                      (0 - 60 allows for the occasional leap second) */
//     int		min;   /* minutes after the hour, 0 to 59 */
//     int		hour;  /* hours since midnight, 0 to 23 */
//     int		mday;  /* day of the month, 1 to 31 */
//     int		mon;   /* months since January, 0 to 11 */
//     int		year;  /* years since 1900 */
//     int		wday;  /* days since Sunday, 0 to 6 */
//     int		yday;  /* days since January 1, 0 to 365 */
// };

// static struct RTCtm Tm;

// const	char	*	WEEK_STR[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
//  /*计算公历*/
// void	GregorianDay(struct RTCtm * tim,const uClock * standard)
// {
// 	int leapsToDate;
// 	int lastYear;
// 	int day;
// 	int MonthOffset[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
// 	static struct tm t_tm;

// 	_localtime_r( standard, &t_tm );
// 	if( Tm.mday != t_tm.tm_mday )
// 	{
// 		
// 		Tm.year = (t_tm.tm_year + 1900);
// 		Tm.mon = t_tm.tm_mon +1;
// 		Tm.mday = t_tm.tm_mday;
// 	
// 	
// 		lastYear=tim->year - 1;

// 		/*计算从公元元年到计数的前一年之中一共经历了多少个闰年*/
// 		leapsToDate = lastYear / 4 - lastYear / 100 + lastYear / 400;      

// 			 /*如若计数的这一年为闰年，且计数的月份在2月之后，则日数加1，否则不加1*/
// 		if( (tim->year % 4 == 0 ) &&
// 			 ( (tim->year % 100 != 0 ) || ( tim->year % 400 == 0 ) ) &&
// 			 ( tim->mon > 2 )) 
// 		{/* We are past Feb. 29 in a leap year*/	 	
// 			day=1;
// 		} else 
// 		{
// 			day=0;
// 		}

// 		day += lastYear * 365 + leapsToDate + MonthOffset[ tim->mon - 1 ] + tim->mday; /*计算从公元元年元旦到计数日期一共有多少天*/

// 		tim->wday = day % 7;
// 	}
// }

// void	ShowWDay( uint16_t yx, const uClock * Now )
// { 
// 	GregorianDay( &Tm, Now );
// 	SEDLputs( yx, WEEK_STR[ Tm.wday ] );
// }
// /********************************** 功能说明 ***********************************
// *  显示时间
// *******************************************************************************/
// void	ShowClock( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;

//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, "%02u-%02u %02u:%02u:%02u",
//              t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
// 		SEDLputs( yx, sbuffer);

// }

// void	ShowClockDate( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;

//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, "%04u-%02u-%02u",  t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday );
//     Lputs( yx, sbuffer );

// }

// void	ShowClockTime( uint16_t yx, const uClock * pClock )
// {
//     CHAR	sbuffer[20];
//     struct tm t_tm;
//     _localtime_r( pClock, &t_tm );
//     sprintf( sbuffer, "%02u:%02u:%02u", t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
//     Lputs( yx, sbuffer );
// }


// static	uint8_t	dayOfmonth( uint16_t year, uint8_t month )
// {
//     switch( month )
//     {
//     default:
//     case  1:
//         return 31;
//     case  2:
//         return ( (( year % 4 == 0 ) &&
// 										( ( year % 100 != 0 ) || ( year % 400 == 0 ) ))
// 								? 29 : 28 );	 
//     case  3:
//         return 31;
//     case  4:
//         return 30;
//     case  5:
//         return 31;
//     case  6:
//         return 30;
//     case  7:
//         return 31;
//     case  8:
//         return 31;
//     case  9:
//         return 30;
//     case 10:
//         return 31;
//     case 11:
//         return 30;
//     case 12:
//         return 31;
//     }
// }

// BOOL	EditClockDate( uint16_t yx, uClock * pClock )
// {
//     CHAR  	sbuffer[20];
//     struct tm t_tm;
//     uint16_t	year;
//     uint8_t 	month;
//     uint8_t 	day_m;
//     uint8_t 	option = 1u;
// 		uint16_t gray  = Configure.DisplayGray;
// 		BOOL	graychanged = FALSE;

//     _localtime_r( pClock, &t_tm );
//     year  = t_tm.tm_year + 1900;
//     month = t_tm.tm_mon  + 1;
//     day_m = t_tm.tm_mday;

//     for(;;)
//     {
//         sprintf( sbuffer, "%04u-%02u-%02u", year, month, day_m );
//         Lputs( yx, sbuffer );

//         switch( option )
//         {
//         case 1:
//             LcmMask( yx  , 4,NULL );
//             break;	// year
//         case 2:
//             LcmMask( yx+10, 2,NULL );
//             break;	// month
//         case 3:
//             LcmMask( yx+16, 2,NULL );
//             break;	// day_m
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 if ( ++year > 2099u )
//                 {
//                     year = 2000u;
//                 }
//                 break;
//             case 2:
//                 if ( ++month > 12u )
//                 {
//                     month = 1u;
//                 }
//                 break;
//             case 3:
//                 if ( ++day_m > dayOfmonth( year, month ))
//                 {
//                     day_m = 1u;
//                 }
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_DEC:
//             switch( option )
//             {
//             case 1:
//                 if ( --year < 2000u )
//                 {
//                     year = 2099u;
//                 }
//                 break;
//             case 2:
//                 if ( --month < 1u )
//                 {
//                     month = 12u;
//                 }
//                 break;
//             case 3:
//                 if ( --day_m < 1u )
//                 {
//                     day_m = dayOfmonth( year, month );
//                 }
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++option > 3u )
//             {
//                 option = 1u;
//             }
//             break;

//         case K_LEFT:
//             if ( --option < 1u )
//             {
//                 option = 3u;
//             }
//             break;

//         case K_OK:
//             t_tm.tm_year = year  - 1900;
//             t_tm.tm_mon  = month - 1;
//             t_tm.tm_mday = day_m;
//             * pClock = mktime( &t_tm );
//             return	TRUE;

//         case K_ESC:
//             return	FALSE;

// 				case K_OK_UP:	
// 					if ( gray < 2200u )
// 					{
// 						++gray;
// 					}
// 					if( ! releaseKey( K_OK_UP,100 ))
// 					{
// 						while( ! releaseKey( K_OK_UP, 1 ))
// 						{
// 							++gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}
// 					}
// 					graychanged = true;		
// 					break;
// 				case K_OK_DOWN:
// 					if ( gray >  200u )
// 					{
// 						--gray;
// 					}
// 					if( ! releaseKey( K_OK_DOWN, 100 ))
// 					{
// 						while( ! releaseKey( K_OK_DOWN, 1 ))
// 						{
// 							--gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}			
// 					}
// 					graychanged = true;
// 					break;

// 				case K_OK_RIGHT:
// 					if ( gray < ( 2000u - 50u ))
// 					{ 
// 						gray += 100u;
// 					}
// 					graychanged = true;
// 					break;
// 				case K_OK_LEFT:	
// 					if ( gray > ( 200 + 20u ))
// 					{
// 						gray -= 20u;
// 					}
// 					graychanged = true;
// 					break;
// 				default:
// 					break;
// 				}
// 				if( graychanged == true )
// 				{
// 					DisplaySetGrayVolt( gray * 0.01f );
// 					Configure.DisplayGray = gray;
// 					ConfigureSave();
// 					graychanged = FALSE;;
// 				}		

//     }
// }


// BOOL	EditClockTime( uint16_t yx, uClock * pClock )
// {
//     CHAR	sbuffer[20];
// 		uint16_t gray  = Configure.DisplayGray;
// 		BOOL	graychanged = FALSE;
//     struct tm t;
//     uint8_t 	option = 1u;

//     _localtime_r( pClock, &t );

//     for(;;)
//     {
//         sprintf( sbuffer, "%02u:%02u:%02u", t.tm_hour, t.tm_min, t.tm_sec );
//         Lputs( yx, sbuffer );

//         switch( option )
//         {
//         case 1:
//             LcmMask( yx  , 2,NULL );
//             break;  // hour
//         case 2:
//             LcmMask( yx+6, 2,NULL );
//             break;  // minute
//         case 3:
//             LcmMask( yx+12, 2,NULL );
//             break;  // second
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 t.tm_hour = ( t.tm_hour +  1u ) % 24u;
//                 break;
//             case 2:
//                 t.tm_min  = ( t.tm_min  +  1u ) % 60u;
//                 break;
//             case 3:
//                 t.tm_sec  = ( t.tm_sec  +  1u ) % 60u;
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_DEC:
//             switch( option )
//             {
//             case 1:
//                 t.tm_hour = ( t.tm_hour + 23u ) % 24u;
//                 break;
//             case 2:
//                 t.tm_min  = ( t.tm_min  + 59u ) % 60u;
//                 break;
//             case 3:
//                 t.tm_sec  = ( t.tm_sec  + 59u ) % 60u;
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++option > 3u )
//             {
//                 option = 1;
//             }
//             break;

//         case K_LEFT:
//             if ( --option < 1u )
//             {
//                 option = 3u;
//             }
//             break;

//         case K_OK:
//             * pClock = mktime( &t );
//             return	TRUE;

//         case K_ESC:
//             return	FALSE;

// 				case K_OK_UP:	
// 					if ( gray < 2200u )
// 					{
// 						++gray;
// 					}
// 					if( ! releaseKey( K_OK_UP,100 ))
// 					{
// 						while( ! releaseKey( K_OK_UP, 1 ))
// 						{
// 							++gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}
// 					}
// 					graychanged = true;		
// 					break;
// 				case K_OK_DOWN:
// 					if ( gray >  200u )
// 					{
// 						--gray;
// 					}
// 					if( ! releaseKey( K_OK_DOWN, 100 ))
// 					{
// 						while( ! releaseKey( K_OK_DOWN, 1 ))
// 						{
// 							--gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}			
// 					}
// 					graychanged = true;
// 					break;


// 				case K_OK_RIGHT:
// 					if ( gray < ( 2000u - 50u ))
// 					{ 
// 						gray += 100u;
// 					}
// 					graychanged = true;
// 					break;
// 				case K_OK_LEFT:	
// 					if ( gray > ( 200 + 20u ))
// 					{
// 						gray -= 20u;
// 					}
// 					graychanged = true;
// 					break;
// 				default:
// 					break;
// 				}
// 				if( graychanged == true )
// 				{
// 					DisplaySetGrayVolt( gray * 0.01f );
// 					Configure.DisplayGray = gray;
// 					ConfigureSave();
// 					graychanged = FALSE;;
// 				}		

//     }
// }

// ///////////////////////////////////////////////////////////////////
// // 设置采样时间参数
// ///////////////////////////////////////////////////////////////////
// void	ShowDATE( uint16_t yx, uint32_t timer )
// {
// 	CHAR	sbuffer[20];
// 	struct tm t;

// 	_localtime_r( &timer, &t );
// 	sprintf( sbuffer, "%2d-%2d %02d:%02d", t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min );
// 	Lputs( yx, sbuffer );
// }

// void	ShowTIME( uint16_t yx, uint16_t Time )
// {
// 	CHAR	sbuffer[20];
// 	uint8_t	hour   = ( Time / 60u );
// 	uint8_t	minute = ( Time % 60u );

// 	sprintf( sbuffer, "%02u:%02u", hour, minute );
// 	Lputs( yx, sbuffer );
// }

// BOOL	EditTIME( uint16_t yx, uint16_t * pTime )
// {
//     uint8_t hour   = (( *pTime / 60u ) % 100u );
//     uint8_t minute = (  *pTime % 60u );
// 		uint16_t gray  = Configure.DisplayGray;
// 		BOOL	graychanged = FALSE;
//     BOOL	changed = FALSE;
//     uint8_t option = 1u;

//     do
//     {
//         ShowTIME( yx, (( hour * 60u ) + minute ));
//         switch( option )
//         {
//         case 1:
//             LcmMask( yx + 0u, 1u,NULL );
//             break;  // 10 hour
//         case 2:
//             LcmMask( yx + 2u, 1u,NULL );
//             break;  //  1 hour
//         case 3:
//             LcmMask( yx + 6u, 1u,NULL );
//             break;  // 10 minute
//         case 4:
//             LcmMask( yx + 8u, 1u,NULL );
//             break;  //  1 minute
//         default:
//             break;
//         }
//         switch( getKey() )
//         {
//         case K_INC:
//             switch( option )
//             {
//             case 1:
//                 hour   = (  hour  + 10u ) % 100;
//                 break;
//             case 2:
//                 hour   = (( hour  / 10u ) * 10u ) + (( hour   + 1u ) % 10u );
//                 break;
//             case 3:
//                 minute = ( minute + 10u ) % 60u;
//                 break;
//             case 4:
//                 minute = ((minute / 10u ) * 10u ) + (( minute + 1u ) % 10u );
//                 break;
//             default:
//                 break;
//             }
//             break;
//         case K_DEC:
//             switch( option )
//             {
//             case 1:
//                 hour   = (  hour   + 90u ) % 100u;
//                 break;
//             case 2:
//                 hour   = (( hour   / 10u ) * 10u ) + (( hour   + 9u ) % 10u );
//                 break;
//             case 3:
//                 minute = (  minute + 50u ) % 60u;
//                 break;
//             case 4:
//                 minute = (( minute / 10u ) * 10u ) + (( minute + 9u ) % 10u );
//                 break;
//             default:
//                 break;
//             }
//             break;

//         case K_RIGHT:
//             if ( ++ option > 4u )
//             {
//                 option = 1u;
//             }
//             break;

//         case K_LEFT:
//             if ( -- option < 1u )
//             {
//                 option = 4u;
//             }
//             break;

//         case K_OK:
//             *pTime = ( hour * 60u ) + minute;
//             changed = TRUE;
//             option = 0u;
//             break;

//         case K_ESC:
//             changed = FALSE;
//             option = 0u;
//             break;

// 				case K_OK_UP:	
// 					if ( gray < 2200u )
// 					{
// 						++gray;
// 					}
// 					if( ! releaseKey( K_OK_UP,100 ))
// 					{
// 						while( ! releaseKey( K_OK_UP, 1 ))
// 						{
// 							++gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}
// 					}
// 					graychanged = true;		
// 					break;
// 				case K_OK_DOWN:
// 					if ( gray >  200u )
// 					{
// 						--gray;
// 					}
// 					if( ! releaseKey( K_OK_DOWN, 100 ))
// 					{
// 						while( ! releaseKey( K_OK_DOWN, 1 ))
// 						{
// 							--gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}			
// 					}
// 					graychanged = true;
// 					break;

// 				case K_OK_RIGHT:
// 					if ( gray < ( 2000u - 50u ))
// 					{ 
// 						gray += 100u;
// 					}
// 					graychanged = true;
// 					break;
// 				case K_OK_LEFT:	
// 					if ( gray > ( 200 + 20u ))
// 					{
// 						gray -= 20u;
// 					}
// 					graychanged = true;
// 					break;
// 				default:
// 					break;
// 				}
// 				if( graychanged == true )
// 				{
// 					DisplaySetGrayVolt( gray * 0.01f );
// 					Configure.DisplayGray = gray;
// 					ConfigureSave();
// 					graychanged = FALSE;;
// 				}		

//     }
//     while ( 0u != option );

//     return	changed;
// }

// ///////////////////////////////////////////////////////////////////
// static	uint32_t const	tbl_pow10_I32U[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
// static	FP32	const	tbl_pow10_FP32[] = { 1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8, 1E9 };

// void	ShowFP32( uint16_t yx, FP32   NumFP32, uint16_t fmt, const CHAR * Unit )
// {
//     CHAR	sbuffer[20];

//     sprintf( sbuffer, "%*.*f", fmt / 0x100, fmt % 0x100, NumFP32 );
//     Lputs( yx, sbuffer );
//     if( Unit )
//     {
//         Lputs( yx + strlen( sbuffer ) * 2, Unit );
//     }
// }

// void	ShowI16U( uint16_t yx, uint16_t NumI16U, uint16_t fmt, const CHAR * Unit )
// {
//     FP32	NumFP32 = NumI16U / tbl_pow10_FP32[ fmt % 0x100 ];
//     CHAR	sbuffer[20];

//     sprintf( sbuffer, "%*.*f", fmt / 0x100, fmt % 0x100, NumFP32 );
//     Lputs( yx, sbuffer );
//     if( Unit )
//     {
//         Lputs( yx + strlen( sbuffer ) * 2, Unit );
//     }
// }

// void	ShowPercent( uint16_t yx, FP32 percent )
// {
//     ShowFP32( yx, percent * 100.0f, 0x0501u, "%" );
// }

// void	ShowHEX16( uint16_t yx, uint16_t hex16 )
// {
//     CHAR	sbuffer[10];

//     sprintf( sbuffer, "%04X", hex16 );

//     Lputs( yx, sbuffer );
// }

// ///////////////////////////////////////////////////////////////////
// BOOL	EditI32U( uint16_t yx, uint32_t * pNUM, uint16_t fmt )
// {
//     uint32_t	PowN;
//     uint32_t	Num = *pNUM;
//     uint8_t 	M, N, choice = 0u;
// 		uint16_t gray  = Configure.DisplayGray;
// 		BOOL	graychanged = FALSE;
//     CHAR		sbuffer[20];

//     N = fmt % 0x100u;										//	小数点后的有效位数
//     M = ( N == 0 ) ? ( fmt / 0x100 ) : ( fmt / 0x100 - 1 );	//	有效位数, 即choice 变化范围
//     Num = Num % tbl_pow10_I32U[M];							//	保留低位, 清零高位

//     for (;;)
//     {
//         sprintf( sbuffer, "%0*.*f", ( fmt / 0x100 ), ( fmt % 0x100 ), Num / tbl_pow10_FP32[N] );
//         Lputs( yx, sbuffer );

//         if ( choice < ( M - N ))
//         {
//             LcmMask( yx + choice * 2, 1, NULL );		//	输入位置在小数点之前
//         }
//         else
//         {
//             LcmMask( yx + choice * 2 + 2, 1, NULL );	//	输入位置在小数点之后
//         }

//         if (  M >= ( choice + 1u ))
//         {
//             PowN = tbl_pow10_I32U[ M - ( choice + 1u )];
//         }
//         else
//         {
//             PowN = 1u;
//         }

//         switch ( getKey() )
//         {
//         case K_INC:
//             if( Num / PowN % 10 == 9 )
//             {
//                 Num -= PowN * 9;
//             }
//             else
//             {
//                 Num += PowN;
//             }
//             break;
//         case K_DEC:
//             if( Num / PowN % 10 == 0 )
//             {
//                 Num += PowN * 9;
//             }
//             else
//             {
//                 Num -= PowN;
//             }
//             break;
//         case K_RIGHT:
//         //case K_XCH:
//             choice = ( choice + 1 ) % M;
//             break;

//         case K_LEFT:
//             choice = ( choice + M - 1 ) % M;
//             break;

//         case K_OK:
//             *pNUM = Num;
//             return TRUE;
//         case K_ESC:
//             return FALSE;
// 				case K_OK_UP:	
// 					if ( gray < 2200u )
// 					{
// 						++gray;
// 					}
// 					if( ! releaseKey( K_OK_UP,100 ))
// 					{
// 						while( ! releaseKey( K_OK_UP, 1 ))
// 						{
// 							++gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}
// 					}
// 					graychanged = true;		
// 					break;
// 				case K_OK_DOWN:
// 					if ( gray >  200u )
// 					{
// 						--gray;
// 					}
// 					if( ! releaseKey( K_OK_DOWN, 100 ))
// 					{
// 						while( ! releaseKey( K_OK_DOWN, 1 ))
// 						{
// 							--gray;
// 							DisplaySetGrayVolt( gray * 0.01f );
// 						}			
// 					}
// 					graychanged = true;
// 					break;

// 				case K_OK_RIGHT:
// 					if ( gray < ( 2000u - 50u ))
// 					{ 
// 						gray += 100u;
// 					}
// 					graychanged = true;
// 					break;
// 				case K_OK_LEFT:	
// 					if ( gray > ( 200 + 20u ))
// 					{
// 						gray -= 20u;
// 					}
// 					graychanged = true;
// 					break;
// 				default:
// 					break;
// 				}
// 				if( graychanged == true )
// 				{
// 					DisplaySetGrayVolt( gray * 0.01f );
// 					Configure.DisplayGray = gray;
// 					ConfigureSave();
// 					graychanged = FALSE;;
// 				}		

//     }
// }
// /********  (C) COPYRIGHT 2015 青岛金仕达电子科技有限公司  **** End Of File **********/

