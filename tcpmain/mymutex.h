#ifndef _MYMUTEX_H
#define _MYMUTEX_H

#ifdef WIN32 
#include <winsock.h> 
#else 
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <iostream>
#endif


#include <string>

using namespace std;



class CMyMutex
{
public:
	CMyMutex(void);
	~CMyMutex(void);
	
protected:
#ifdef WIN32
	HANDLE	m_hMutex;
#else
	string m_sMutexFile;
	int m_fd;
#endif	

	string m_sErrorStr;

public:
    void SetMutexFile(const char* name);
	bool InitMutex(void);
	bool KillProcess(void);
	string GetErrorStr(){return m_sErrorStr;};	
};

#endif
