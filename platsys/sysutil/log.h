

#ifndef _CLOG_H__
#define _CLOG_H__


/********************************************************************************
* LOGLEVEL_FATAL	1 //�����Ѿ��޷��޸���ϵͳ�޷���������
* LOGLEVEL_ERROR	2 //�����޸��ԵĹ��������޷�ȷ��ϵͳ�Ƿ���Լ�������
* LOGLEVEL_WARN		3 //�����޸��ԵĹ�����ϵͳ���Իָ���������������
* LOGLEVEL_INFO		4 //��������ϵͳ�ĵ�ǰ״̬�������û�
* LOGLEVEL_DEBUG	5 //��ͼ���ʵ�������в�����������˽�ϵͳ����״̬�������ȵ�
* 
* ע������ʹ��ERROR WARN INFO DEBUG
*********************************************************************************/
#define LOGLEVEL_OFF		0
#define LOGLEVEL_FATAL		1
#define LOGLEVEL_ERROR		2
#define LOGLEVEL_WARN		3
#define LOGLEVEL_INFO		4
#define LOGLEVEL_DEBUG		5
#define LOGLEVEL_ALL		100

//Ĭ�ϵ���־����
#define DEFAULT_LOG_LEVEL 	4

//������־��ʶ
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


//ƽ̨��־
#define PERROR(format,...) 	{	WriteLog(LOGLEVEL_ERROR	,__FILE__, __LINE__,LOGFLAG_PLT,"[ERROR]",format,##__VA_ARGS__);  }
#define PINFO(format,...) 	{ 	WriteLog(LOGLEVEL_INFO	,__FILE__, __LINE__,LOGFLAG_PLT,"[INFO ]",format,##__VA_ARGS__);  }
#define PDEBUG(format,...) 	{	WriteLog(LOGLEVEL_DEBUG	,__FILE__, __LINE__,LOGFLAG_PLT,"[DEBUG]",format,##__VA_ARGS__);  }

//������־���޼���
#define TRCLOG(format,...) 	{ 	WriteLog(LOGLEVEL_OFF	,__FILE__, __LINE__,LOGFLAG_TRC,"",format,##__VA_ARGS__);  }

//ͨѶ������־���޼���
#define COMLOG(format,...) 	{ 	WriteLog(LOGLEVEL_OFF	,__FILE__, __LINE__,LOGFLAG_COM,"",format,##__VA_ARGS__);  }

//Ӧ����־
#define ERROR(format,...)  	{	WriteLog(LOGLEVEL_ERROR	,__FILE__, __LINE__,LOGFLAG_APP,"[ERROR]",format,##__VA_ARGS__);  }
#define INFO(format,...)  	{  	WriteLog(LOGLEVEL_INFO	,__FILE__, __LINE__,LOGFLAG_APP,"[INFO ]",format,##__VA_ARGS__);  }
#define DEBUG(format,...) 	{ 	WriteLog(LOGLEVEL_DEBUG	,__FILE__, __LINE__,LOGFLAG_APP,"[DEBUG]",format,##__VA_ARGS__);  }


#endif // _CLOG_H__

