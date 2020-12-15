//
//
//
//  @ Project : 通用工具 杂项 
//  @ File Name : utilmisc.cpp
//  @ Date : 2013/5/30
//  @ Author : disp
//
//


#include "utilmisc.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CUtilMisc::CUtilMisc()
{

}


CUtilMisc::~CUtilMisc()
{

}

/*
	例如：0x0102，0x01是高位的，0x02是低位的
	内存地址增大方向 --->
	大端字节序:   0x01 0x02 （Big endian：   将高序字节存储在起始地址）RS/6000 AIX, SUN
	小端字节序：  0x02 0x01 （Little endian：将低序字节存储在起始地址）X86
*/

int CUtilMisc::IsBigEndian()
{
	int nBigEndian=-1;
	
	//AIX 6.1 64bit ：大端字节序 类型长度
	union{
		short s;
		char c[sizeof(short)];
	}un;
	
	un.s=0x0102;
	if(sizeof(short) ==2)
	{
		if(un.c[0] == 0x01 && un.c[1]==0x02)
			nBigEndian = 1; //printf("-> big.endian(大端字节序)\n");
		else if(un.c[0]==0x02 && un.c[1]==0x01)
			nBigEndian = 0; //printf("-> little.endian(小端字节序)\n");
		else
			nBigEndian = -1; //printf("-> unknow\n");
	}

	return nBigEndian;
	
/*	
	//类型长度
	printf("sizeof(char)=%d\n",sizeof(char));				//1
	printf("sizeof(short)=%d\n",sizeof(short));				//2
	printf("sizeof(int)=%d\n",sizeof(int));					//4
	printf("sizeof(long)=%d\n",sizeof(long));				//8
	printf("sizeof(float)=%d\n",sizeof(float));				//4
	printf("sizeof(double)=%d\n",sizeof(double));			//8
	printf("sizeof(long long)=%d\n",sizeof(long long));		//8
	printf("sizeof(long double)=%d\n",sizeof(long double));	//8
	//uint8_t, uint16_t, uint32_t, uint64_t		
	
	//取值范围
	printf("INT_MAX:%ld\n",INT_MAX);        //2147483647
	printf("LONG_MIN:%ld\n",LONG_MIN);		//-9223372036854775808
	printf("LONG_MAX:%ld\n",LONG_MAX);		// 9223372036854775807
	printf("ULONG_MAX:%lu\n",ULONG_MAX);	//18446744073709551615
	
	FLT_MAX:340282346638528859811704183484516925400.00000
    FLT_MIN:0.000000
    DBL_MAX:1.797693e+308
    DBL_MIN:2.225074e-308	
	
	
	//当前环境浮点数精度（100次比较操作）
    double d1=1000.012000000000011;   //显示d1==d3，15位小数时double出现误差
    double d3=1000.012000000000012;	
    double d1=1000.01200000000011;    //显示d1< d3，14位小数时double是准确的
    double d3=1000.01200000000012;	
		
    float d1=1000.012011;             //显示d1==d3，6位小数时float出现误差
    float d3=1000.012012;			
    float d1=1000.01211;              //显示d1< d3，5位小数时float是准确的
    float d3=1000.01212;	
		
    
    在DB2字段类型DECIMAL(m,n)置中，整数的位数不能大于(m-n)，否则数据库报错：超长;
    但小数位可以大于n，但会从大于n的有效位开始截断。
    例如：DB2 decimal(17,3) 99999999999999.999   
	
	
	#define FLT_EQ(f1,f2)   ( fabs(f2-f1) < FLT_EPSILON ) 	

	double dTmp1 = 99999999999999.993; 
    double dTmp2 = 1.0e+14; 
	if(FLT_EQ(dTmp1,dTmp2))	    
	    printf("dTmp1 == dTmp2\n");     //运行结果是相等，对应dbio insert 'dTemp1'应该会报错
	else if(dTmp1 < dTmp2)
	    printf("dTmp1 < dTmp2\n");  
	    	
	return -1;
	
*/
	
}

int CUtilMisc::IsBitSelected(char chaEditMask[4],int nBit)
{
	  if(nBit < 0 || nBit >31)
	  	return -1;
	  	
		union{
			uint32_t nValue;
			char cha[4];			//sizeof(uint32_t)];
		}un;
/*			
		//大端字节序
		cha[]      cha[0]    cha[1]   cha[2]    em[3]
		nValue   31 <------------------------------   0
		         11111111  11111111  11111111  11111111
*/
		
	for(int n=0;n<4;n++)
		un.cha[n] = chaEditMask[n];
		
	return BIT_CHECK(un.nValue,nBit)==0 ? 0:1;
		
}

void CUtilMisc::Sleep(unsigned int sec, unsigned int millisec)
{
    
#ifdef OS_WIN
    int millisec = 1000 * sec + microsec / 1000;
    SleepEx(millisec, 0);
#else
	unsigned int microsec = 1000 * millisec;	//毫秒->微妙
    struct timeval tv;
    tv.tv_sec  = sec;		//秒
    tv.tv_usec = microsec;	//微妙
    (void) select (1, 0, 0, 0, &tv);
#endif
    
}

char* CUtilMisc::GetArgWithBreak(const char* pSrc,int nGetNo/*=0*/,char chBreak/*=','*/)
{
	static char szTemp[1024];
	memset(szTemp,0,1024);
	if(pSrc == NULL)
		return NULL;

	strcpy(szTemp,pSrc);
	int nLen = strlen(szTemp);
	char *p = NULL;
	int m,n;
	for(n=0,m=0;n<nLen;n++)
	{
		if(szTemp[n] == chBreak)
		{ 
			if(m == 0)
				p = szTemp;

			if(m == nGetNo)
			{
				szTemp[n]='\0';
				break;
			}
			else
			{
				p = &(szTemp[n+1]);
			}

			m++;

		}

	}
	
	//2014.4.2 update 针对nGetNo的取值
	if(m ==0 && nGetNo ==0) //不存在chBreak
	    p = &(szTemp[0]);
	    
	if(nGetNo > m)          //nGetNo取值溢出
	    p=NULL;

	return p;

}

long CUtilMisc::GetTimeInterval(int nEnd)
{
	static struct timeval tpstart;
	
	if(nEnd == 0) //start timer
	{
		gettimeofday(&tpstart,NULL);
		return 0;
	}
	else
	{
		struct timeval tpend;
		gettimeofday(&tpend,NULL);
		long nTimeInterval=1000000 * (tpend.tv_sec - tpstart.tv_sec);
		nTimeInterval += tpend.tv_usec - tpstart.tv_usec;   //nTimeInterval 微妙级的时间跨度		
		//printf("TimeInterval: %d ms\n",nTimeInterval/1000);
		return 	nTimeInterval;
	}	

    /*		
        1970年1月1日至今的秒数s，及微秒数μs 
        1秒＝1000毫秒，     
        1毫秒＝1000微秒，
        1微秒＝1000纳秒，
        1纳秒＝1000皮秒。
        秒用s表现,毫秒用ms,微秒用μs表示，纳秒用ns表示，皮秒用ps表示	
    */	
}

int CUtilMisc::GetCurrentDateTime(char * pDate,char *pTime)
{
    //日期格式YYYYMMDD，时间格式HHMMSSmmm

    /*
	time_t curtime = time(NULL);
	if(curtime == 0)
		return -1;
	*/
		
	struct timeval tp;
	gettimeofday(&tp,NULL);
	time_t curtime = tp.tv_sec;

    struct tm *tm_now;
    tm_now=localtime(&curtime);
    tm_now->tm_year += 1900;
    tm_now->tm_mon ++;
    sprintf(pDate,"%04d%02d%02d",tm_now->tm_year,tm_now->tm_mon,tm_now->tm_mday);
    sprintf(pTime,"%02d%02d%02d%03d",tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec,tp.tv_usec/1000);
        
	//sDate=string(temp);
	
	return 0;
	
}

int CUtilMisc::GetCurrentTime(char *pTime)
{
    //时间格式HH:MM:SS

    /*
	time_t curtime = time(NULL);
	if(curtime == 0)
		return -1;
	*/
		
	struct timeval tp;
	gettimeofday(&tp,NULL);
	time_t curtime = tp.tv_sec;
	

    struct tm *tm_now;
    tm_now=localtime(&curtime);
    sprintf(pTime,"%02d:%02d:%02d",tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);
        
	
	return 0;
	
}