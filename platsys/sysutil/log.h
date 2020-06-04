

#ifndef _CLOG_H__
#define _CLOG_H__


/********************************************************************************
* LOGLEVEL_FATAL	1 //错误已经无法修复，系统无法继续运行
* LOGLEVEL_ERROR	2 //进行修复性的工作，仍无法确定系统是否可以继续运行
* LOGLEVEL_WARN		3 //进行修复性的工作，系统可以恢复正常，继续运行
* LOGLEVEL_INFO		4 //用来反馈系统的当前状态给最终用户
* LOGLEVEL_DEBUG	5 //最低级别，实际运行中不输出。调试了解系统运行状态，变量等等
* 
* 注：建议使用ERROR WARN INFO DEBUG
*********************************************************************************/
#define LOGLEVEL_OFF		0
#define LOGLEVEL_FATAL		1
#define LOGLEVEL_ERROR		2
#define LOGLEVEL_WARN		3
#define LOGLEVEL_INFO		4
#define LOGLEVEL_DEBUG		5
#define LOGLEVEL_ALL		100

//默认的日志级别
#define DEFAULT_LOG_LEVEL 	4

//各类日志标识
#define LOGFLAG_PLT		0
#define LOGFLAG_TRC		1
#define LOGFLAG_COM		2
#define LOGFLAG_APP		3

int InitLoger(const char* szAppName=NULL,int nLogLevel=DEFAULT_LOG_LEVEL,int nAutoAddLF=1);
int WriteLog(int nLevel,const char* file,int line,int flag,const char* tag,const char* fmt,...);
void UninitLoger();

int GetLogLevel();
void SetLogLevel(int nLevel);
int  GetLogAutoAddLF();
void SetLogAutoAddLF(int nAuto);


//平台日志
#define PERROR(format,...) 	{	WriteLog(LOGLEVEL_ERROR	,__FILE__, __LINE__,LOGFLAG_PLT,"[ERROR]",format,##__VA_ARGS__);  }
#define PINFO(format,...) 	{ 	WriteLog(LOGLEVEL_INFO	,__FILE__, __LINE__,LOGFLAG_PLT,"[INFO ]",format,##__VA_ARGS__);  }
#define PDEBUG(format,...) 	{	WriteLog(LOGLEVEL_DEBUG	,__FILE__, __LINE__,LOGFLAG_PLT,"[DEBUG]",format,##__VA_ARGS__);  }

//交易日志，无级别
#define TRCLOG(format,...) 	{ 	WriteLog(LOGLEVEL_OFF	,__FILE__, __LINE__,LOGFLAG_TRC,"",format,##__VA_ARGS__);  }

//通讯报文日志，无级别
#define COMLOG(format,...) 	{ 	WriteLog(LOGLEVEL_OFF	,__FILE__, __LINE__,LOGFLAG_COM,"",format,##__VA_ARGS__);  }

//应用日志
#define ERROR(format,...)  	{	WriteLog(LOGLEVEL_ERROR	,__FILE__, __LINE__,LOGFLAG_APP,"[ERROR]",format,##__VA_ARGS__);  }
#define INFO(format,...)  	{  	WriteLog(LOGLEVEL_INFO	,__FILE__, __LINE__,LOGFLAG_APP,"[INFO ]",format,##__VA_ARGS__);  }
#define DEBUG(format,...) 	{ 	WriteLog(LOGLEVEL_DEBUG	,__FILE__, __LINE__,LOGFLAG_APP,"[DEBUG]",format,##__VA_ARGS__);  }


#endif // _CLOG_H__

