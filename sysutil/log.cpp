

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 

#include "log.h"
#include "simplelog.h"

int 		g_nLogLevel = DEFAULT_LOG_LEVEL;
char 		g_szAppName[255]="";
CSimpleLog	g_SimpleLog[4];	//LOGFLAG_APP+1

int			g_nAutoAddLF = 1;

bool GetCurrentDateTime(string& sDate,string& sTime,bool bFlag)
{
	time_t curtime = time(NULL);
	if(curtime == 0)
		return false;

	char temp[24];
    struct tm *tm_now;
    tm_now=localtime(&curtime);
    tm_now->tm_year += 1900;
    tm_now->tm_mon ++;
    if(bFlag)
    	sprintf(temp,"%04d-%02d-%02d",tm_now->tm_year,tm_now->tm_mon,tm_now->tm_mday);
    else
        sprintf(temp,"%04d%02d%02d",tm_now->tm_year,tm_now->tm_mon,tm_now->tm_mday);
	sDate=string(temp);
	
    if(bFlag)	
    	sprintf(temp,"%02d:%02d:%02d",tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);
    else
    	sprintf(temp,"%02d%02d%02d",tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);
   	sTime=string(temp);
   	
	return true;
}

int InitLoger(const char* szAppName,int nLogLevel,int nAutoAddLF)
{
	g_nLogLevel = nLogLevel;
	g_nAutoAddLF = nAutoAddLF;
	

	string sDate,sTime;
	GetCurrentDateTime(sDate,sTime,false);
	string sHomeDir = getenv("NCBS_HOME");
    sHomeDir+="/log";
	
	char szFilePath[4][255],szFilePathOld[4][255],szLockFile[4][255];	
	if(szAppName == NULL)
	{
	    sprintf(szFilePath[LOGFLAG_PLT],"%s/plt_%s_%s.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	    sprintf(szFilePathOld[LOGFLAG_PLT],"%s/plt_%s_%s_1.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	    sprintf(szLockFile[LOGFLAG_PLT],"%s/.plt_%s_%s.lck",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	}
	else
	{
	    sprintf(szFilePath[LOGFLAG_PLT],"%s/plt_%s_%s_%s.log",sHomeDir.c_str(),szAppName,sDate.c_str(),sTime.c_str());
	    sprintf(szFilePathOld[LOGFLAG_PLT],"%s/plt_%s_%s_%s_1.log",sHomeDir.c_str(),szAppName,sDate.c_str(),sTime.c_str());
	    sprintf(szLockFile[LOGFLAG_PLT],"%s/.plt_%s_%s_%s.lck",sHomeDir.c_str(),szAppName,sDate.c_str(),sTime.c_str());
	}
	
	sprintf(szFilePath[LOGFLAG_TRC],"%s/trc_%s_%s.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	sprintf(szFilePathOld[LOGFLAG_TRC],"%s/trc_%s_%s_1.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	sprintf(szLockFile[LOGFLAG_TRC],"%s/.trc_%s_%s.lck",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	
	sprintf(szFilePath[LOGFLAG_COM],"%s/com_%s_%s.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	sprintf(szFilePathOld[LOGFLAG_COM],"%s/com_%s_%s_1.log",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	sprintf(szLockFile[LOGFLAG_COM],"%s/.com_%s_%s.lck",sHomeDir.c_str(),sDate.c_str(),sTime.c_str());
	
	if(szAppName == NULL)
		g_szAppName[0]='\0';
	else
	{
		strcpy(g_szAppName,szAppName);
		string sAppDir = sHomeDir+"/"+szAppName;
		
		struct  stat statDir;   
       	memset( &statDir,0x00,sizeof(struct  stat) );
	    if( stat( sAppDir.c_str(),&statDir )!=0 )  /*检查目录是否存在，如果不存在则创建*/
		{	
			if( mkdir( sAppDir.c_str(), S_IRWXU|S_IRGRP|S_IROTH) ) //744
			{	
				printf("应用日志文件目录[%s]创建失败\n",sAppDir.c_str());
				return -1;
			}		
		} 		
		
		sprintf(szFilePath[LOGFLAG_APP],"%s/app_%s_%s.log",sAppDir.c_str(),sDate.c_str(),sTime.c_str());
		sprintf(szFilePathOld[LOGFLAG_APP],"%s/app_%s_%s_1.log",sAppDir.c_str(),sDate.c_str(),sTime.c_str());
		sprintf(szLockFile[LOGFLAG_APP],"%s/.app_%s_%s.lck",sAppDir.c_str(),sDate.c_str(),sTime.c_str());
	}
	
	int nRetp = g_SimpleLog[LOGFLAG_PLT].Init(szFilePath[LOGFLAG_PLT],szFilePathOld[LOGFLAG_PLT],szLockFile[LOGFLAG_PLT]);
	//int nRett = g_SimpleLog[LOGFLAG_TRC].Init(szFilePath[LOGFLAG_TRC],szFilePathOld[LOGFLAG_TRC],szLockFile[LOGFLAG_TRC]);
	int nRetc = g_SimpleLog[LOGFLAG_COM].Init(szFilePath[LOGFLAG_COM],szFilePathOld[LOGFLAG_COM],szLockFile[LOGFLAG_COM]);
	int nReta = 0;
	if(szAppName != NULL)
	    nReta = g_SimpleLog[LOGFLAG_APP].Init(szFilePath[LOGFLAG_APP],szFilePathOld[LOGFLAG_APP],szLockFile[LOGFLAG_APP]);
	
	if(	nRetp == -1 ||  nRetc==-1 ||  nReta==-1)
	{
	    printf("日志文件初始化失败[%d,%d,%d]\n",nRetp,nRetc,nReta);
		return -1;
	}
		
	return 0;			
}

int GetLogLevel()
{
	return g_nLogLevel;
}

void SetLogLevel(int nLevel)
{
	g_nLogLevel=nLevel;
}

int  GetLogAutoAddLF()
{
	return g_nAutoAddLF;
}

void SetLogAutoAddLF(int nAuto)
{
	g_nAutoAddLF = nAuto;
}

int WriteLog(int nLevel,const char* file,int line,int flag,const char* tag,const char* fmt,...)
{
	if(nLevel > g_nLogLevel)
		return 0;
	
	/*	
	//printf("WriteLog: level=%d,g_nLogLevel=%d\n",nLevel,g_nLogLevel);
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	vprintf(fmt,arg_ptr);
	*/
	
	string sDate,sTime;
	GetCurrentDateTime(sDate,sTime,true);
	char szLogHead[200];
	
	if(flag == LOGFLAG_PLT || flag == LOGFLAG_APP)
		sprintf(szLogHead,"%s %s %s:%d PID=%d %s :",sDate.c_str(),sTime.c_str(),file,line,getpid(),tag);
	else	
		sprintf(szLogHead,"%s %s PID=%d %s :",sDate.c_str(),sTime.c_str(),getpid(),tag);
	
	const int BUF_SIZE = 8*1024;	
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	char szLogText[BUF_SIZE];
	//vsprintf(szLogText,fmt,arg_ptr);
	vsnprintf(szLogText,BUF_SIZE,fmt,arg_ptr);
	va_end(arg_ptr);
	
	string strText;
	if(g_nAutoAddLF)
		strText = string(szLogHead) + string(szLogText) + "\n";
	else
		strText = string(szLogHead) + string(szLogText);	
	
	return g_SimpleLog[flag].Write( strText );
	
}


void UninitLoger()
{
	g_SimpleLog[LOGFLAG_PLT].Uninit();
	g_SimpleLog[LOGFLAG_TRC].Uninit();
	g_SimpleLog[LOGFLAG_COM].Uninit();
	g_SimpleLog[LOGFLAG_APP].Uninit();	
	
}

/*
	可变参数及宏使用总结：
	1. __VA_ARGS__不能出现在函数中，只能在宏中使用
	2. 要将可变参数在函数中传递，要看被传入的函数有没有一个va_list参数的版本，如：vprintf
	3. 变长参数表是...，它和va_list还不一样。
*/


/*
//旧式C用法
//#include <varargs.h>

void WriteLog_old(  nLevel ,va_alist)
int nLevel;
va_dcl
{
	printf("WriteLog: level=%d,g_nLogLevel=%d\n",nLevel,g_nLogLevel);
	
	if(nLevel <= g_nLogLevel)
	{
		va_list arg_ptr;
		va_start(arg_ptr);
		printf(arg_ptr);
		va_end(arg_ptr);
		printf("[log end]\n");
	}
	
}
*/
