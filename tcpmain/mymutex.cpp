
#include "mymutex.h"

CMyMutex::CMyMutex()
{
#ifdef WIN32
	m_hMutex=NULL;
#else
	m_sMutexFile = "./.running";
	m_fd = -1;
#endif
}

CMyMutex::~CMyMutex(void)
{
#ifdef WIN32
	if(m_hMutex)
		CloseHandle(m_hMutex);
#else
	if(m_fd != -1)
		close(m_fd);
#endif

}
void CMyMutex::SetMutexFile(const char* name)
{
#ifdef WIN32

#else
	m_sMutexFile = name;
#endif    
}
    
bool CMyMutex::InitMutex()
{
#ifdef _WIN32

	char szExeFullPath[MAX_PATH]="";
	GetModuleFileName(NULL,szExeFullPath,MAX_PATH);
	for(int n=0;n<MAX_PATH;n++)
		if(szExeFullPath[n]=='\\')
			szExeFullPath[n]='_';

	m_hMutex=::CreateMutex(NULL,TRUE,szExeFullPath);
	if(m_hMutex == NULL)
	{
		char tmp[48]="";
		sprintf(tmp,"Error: Can not create the mutex(%d).Maybe the tuxeuamt service is running.",GetLastError());
		m_sErrorStr = tmp;
		return false;
	}
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		m_sErrorStr="The tuxeuamt has been running aready.";
		return false;
	}
 
#else  
  
    //S_IRWXG	组可以读写执行
    //S_IRWXO	其他人可以读、写、执行
    //umask(S_IRWXG|S_IRWXO);
    umask(0);
    
    //O_RDWR	以读写的方式打开文件
    //O_CREAT	创建一个文件
    //S_IRWXU	用户可以读、写、执行
	int m_fd=open(m_sMutexFile.c_str(),O_RDWR|O_CREAT,0770);//S_IRWXU);
    if(m_fd < 0)
    {
        m_sErrorStr = "Error1: Failure when open file.  ";
        //cerr<<strerror(errno)<<endl;
                            
        return false;
    }
    if(lockf(m_fd,F_TLOCK,0)==-1)
    {                
        m_sErrorStr = "Error1: Another tcpmain is running. ";
        return false;
    }


    pid_t cur_pid=getpid();
    if(cur_pid==-1)
    {
        m_sErrorStr = "Error1: Can not get pid.";
        return false;
    }
    if(write(m_fd,reinterpret_cast<void *>(&cur_pid),sizeof(pid_t))==-1)
    {
        m_sErrorStr="Error1: Failure when write file ";
        return false;              
    }
#endif

	return true;
}

bool CMyMutex::KillProcess(void)
{

#ifdef _WIN32
      ;         
#else       

        int fd_flag=open(m_sMutexFile.c_str(),O_RDWR|O_CREAT);
        if(fd_flag < 0)
        {
            m_sErrorStr="Error2: Failure when open file.";
            //cerr<<strerror(errno)<<endl;
            return false;
        }
        if(lockf(fd_flag,F_TEST,0)==0)
        {                
            m_sErrorStr="Error2: Don't find the tcpmain. ";            
            close(fd_flag);
            return false;
        }
        pid_t pid=0;
        if(read(fd_flag,&pid,sizeof(pid_t))!=sizeof(pid_t))
        {
            m_sErrorStr="Error2: Failure when read file. ";
            close(fd_flag);
            return false;
        }        
        if(kill(pid, SIGTERM)==-1)
        {
            char szTmp[1024];
            sprintf(szTmp,"Error2: Failure when SIGTERM to the tcpmain.[%d %s]",errno, strerror(errno));
            m_sErrorStr=szTmp;
            close(fd_flag);
            return false;
        }        

		close(fd_flag);
		        
#endif //_WIN32

		return true;

}
