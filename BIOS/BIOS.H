/**************** (C) COPYRIGHT 2015 青岛金仕达电子科技有限公司 ****************
* 文 件 名: 
* 创 建 者:  
* 描  述  :  
* 最后修改:  
*********************************** 修订记录 ***********************************/
#ifndef	__bool_true_false_are_defined
	#include <stdbool.h>
	typedef	bool	BOOL;
	#define	TRUE	true
	#define	FALSE	false
#endif
extern  void N5110_Write_Byte( uint8_t dat, bool command );


