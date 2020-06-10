//
//
//
//  @ Project : 系统平台头文件
//  @ File Name : gtwsv.h
//  @ Date : 2013/8/21
//  @ Author : disp
//
//

#ifndef __GTWSV_H__
#define __GTWSV_H__


#include "platspub.h"

#include "sysutil/shmaccess.h"
#include "sysutil/queue.h"
#include "sysutil/dictqueue.h"

//重新定义宏，仅仅用于调试，打印屏幕
#define PERROR_D(format,...) 	{ printf(format,##__VA_ARGS__);	 WriteLog(LOGLEVEL_ERROR	,__FILE__, __LINE__,LOGFLAG_PLT,"[ERROR]",format,##__VA_ARGS__);  }
#define PINFO_D(format,...) 	{ printf(format,##__VA_ARGS__);	 WriteLog(LOGLEVEL_INFO	    ,__FILE__, __LINE__,LOGFLAG_PLT,"[INFO ]",format,##__VA_ARGS__);  }
#define PDEBUG_D(format,...) 	{ printf(format,##__VA_ARGS__);	 WriteLog(LOGLEVEL_DEBUG	,__FILE__, __LINE__,LOGFLAG_PLT,"[DEBUG]",format,##__VA_ARGS__);  }

//报文相关定义
typedef unsigned char byte;

typedef struct
{
    byte origin_system;         //PIC X
    byte source_system;         //PIC X     'U'
    byte source_applic;         //PIC X
    byte message_type;          //PIC X     LOW_VALUE
    byte process_id[8];         //PIC 9(8)  PID                 //%08d
    byte symbolic_number[4+1];  //PIC S9(4)                     //-0001 -9821 +0015 +3289
    byte term_type;             //PIC X     '0'
    byte dli[2];                //PIC XX
    byte future_use[9];         //PIC X(9)
    byte client_id[2];          //PIC X(2)
    byte msg_sequence[9];       //PIC 9(9)  ADD 1               //%09d 
    byte end_message_ind;       //PIC X     '0' '1' '2' '3' 'U'
    byte msg_format;            //PIC X
    byte responseq_sysnum;      //PIC X
    byte responseq_type;        //PIC X
    byte responseq_ap;          //PIC 9                         //'0'~'9'
    byte responseq_name[10];    //PIC X(10)
    byte responseq_password[10];//PIC X(10)
    byte responseq_rest[9];     //PIC X(9)
    byte echo_data[64];         //PIC X(64)
    
} DEL_HEADER;

typedef struct
{
    byte code;
    byte data_len[4];
    
} TCP_HEADER;

#define INT_HEADER_SIZE  122

typedef struct
{
    byte data[2049];
    
} MINTCPIO_DATA;

//(1+4) + 122 + 1233 = 5 + 1355 = 1360

typedef struct
{
    DEL_HEADER  del_header;
    byte        msg_data[sizeof(TCP_HEADER)+sizeof(MINTCPIO_DATA)];

}NCBS_QUEIO_DATA;

typedef struct
{
	long mtype;	            //MSGTYPE_NORMAL
	NCBS_QUEIO_DATA data;   //
}NCBS_QUEIO;


#endif // __GTWSV_H__