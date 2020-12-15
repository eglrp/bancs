//
//
//
//  @ Project : 通用工具 杂项
//  @ File Name : utilmisc.h
//  @ Date : 2013/5/30
//  @ Author : disp
//
//


#if !defined(_CUTILMISC_H)
#define _CUTILMISC_H

#include <float.h>

/*
    For EPSILON, you can use the constants FLT_EPSILON, which is defined for float as 1.192092896e-07F, 
    or DBL_EPSILON, which is defined for double as 2.2204460492503131e-016. 
    You need to include float.h for these constants.
    These constants are defined as the smallest positive number x, such that x+1.0 is not equal to 1.0.
    Because this is a very small number, you should employ user-defined tolerance 
    for calculations involving very large numbers.
    
    //AIX v6.0, 64bit ,xlC IBM(2010)
    //#define FLT_EPSILON                1.19209290E-07F
    //#define LDBL_EPSILON               1.084202172485504E-19  
    
*/

//判断浮点数（float/doublue）是否为零， 以及是否相同   
#define FLT_ZERO(f1)    ( fabs(f1) < FLT_EPSILON ) 
#define FLT_EQ(f1,f2)   ( fabs(f2-f1) < FLT_EPSILON ) 


//C中几种操作位的方法，简便的方法是使用宏来封装：
#define BIT_SET(a,b)    ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b)  ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b)   ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b)  ((a) & (1<<(b)))

class CUtilMisc
{
	
// Constructors, destructor
public:
	CUtilMisc();
	~CUtilMisc();
	
//methods
public:
	static int IsBitSelected(char chaEditMask[4],int nBit);	//检测指定位数是否被选中（为1）
	static int IsBigEndian();
	
	static char* GetArgWithBreak(const char* pSrc,int nGetNo=0,char chBreak=',');

//methods
public:
	static void Sleep(unsigned int sec, unsigned int millisec);
	static long GetTimeInterval(int nEnd);
	static int GetCurrentDateTime(char * pDate,char *pTime);
	static int GetCurrentTime(char *pTime);		
	
protected:
    

private:
 	
};

#endif  //_CUTILMISC_H
