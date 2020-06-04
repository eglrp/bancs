
#include "platspub.h"
#include "mqmanage.h"

#include <vector>
#include <map>
#include <string>
#include <algorithm>   
#include <functional>  
 
#include <string.h>
#include "syscfg/sysc.h"

using namespace std;

// 清除屏幕
#define CLEAR() printf("\033[2J")

// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))

// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))

// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))

// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))

// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

// 光标复位
#define RESET_CURSOR() printf("\033[H")

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")

// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

//反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")

bool g_bSEndFlag = false;

void SignalCleanup(int sig)
{
   switch(sig)
    {
        case SIGTERM:
        case SIGINT:
			{
				g_bSEndFlag = true;
			}
			break;
        default:
            break;;          
    }
    
    	
}

inline  string& LeftTrim(string& s)
{
	string::iterator   p=find_if(s.begin(),s.end(),not1(ptr_fun(iswspace))); 
	s.erase(s.begin(),p);   
	return  s;   
}
inline  string&  RightTrim(string   &s)   
{   
	string::reverse_iterator  p=find_if(s.rbegin(),s.rend(),not1(ptr_fun(iswspace)));   
	s.erase(p.base(),s.end());   
	return   s;   
}   
inline   string   Trim(string   s)   
{   
	LeftTrim(RightTrim(s));   
	return   s;   
}   
	
string GetStrWithDelim(const string src, const int pos,const string delims)
{
    char szSrc[1024]="";
    strcpy(szSrc,src.c_str());
    const char* pDelims = delims.c_str();
    char* token = strtok( szSrc, pDelims);

    int n=0;
    string target;
    while( token != NULL )
    {
        if(pos == n++)
        {
            target = token;
            break;
        }

        token = strtok( NULL, pDelims);
    }
    return target;


}



#include <pwd.h>
#include <grp.h>


int GetTprocStatus(const char* szSName,const char* szUser)
{
    
    FILE *fp=NULL;    
    char buff[1024];  
    memset(buff,0,sizeof(buff));
    
    CString strTmp;
    strTmp.Format("ps -ef|grep 'tproc %s'|grep '%s'|grep -v 'grep'",szSName,szUser);
    
    fp = popen(strTmp.c_str(),"r");
    if(fp==NULL)    
    {   
        fprintf(stderr,"execute command failed: %s",strerror(errno));    
        return -1;    
    }   
    
    int nCount=0;
    do
    {
        if(feof(fp))
            break;
            
        if(fgets(buff, sizeof(buff), fp))   
        {   	
 
            for(int i=0;i<strlen(buff);i++)
                if(buff[i]=='\n')
                    buff[i]=0;   

            
            strTmp = buff;
            if(strTmp.Find("tproc") !=-1)
                nCount++;
            
        }  
        
    }while(1); 

    pclose(fp);  
    
    
    return nCount;
    
    
}

int ShowStatus(int nMaxRow,int nMaxCol)
{
    CMqManage mq;
    if(mq.InitCfg()== -1)
        return -1;
    
	char szKey[255];

	
	//printf(" MQMAX=%d\n",nMqmax);
	int x = 0,y=2;
	MOVETO(++x,y); 
    printf("%120s\n"," ");  
    
	MOVETO(++x,y); 
	
	char chSysid = CSysc::GetActiveSysNum();
	char szSysid[20]="未知";
	if( chSysid == DAY_SYSNUM)
	    strcpy(szSysid,"日模式");
	else if( chSysid == NIGHT_SYSNUM)
	    strcpy(szSysid,"夜模式");
	else if( chSysid == CTRL_SYSNUM)	    	
	    strcpy(szSysid,"控制模式");
	    
	//printf("APPQ STATUS:  (ActiveSysNum=%c,%s)",chSysid,szSysid);    
	printf("APPQ STATUS:  (ActiveSysNum=%c)",chSysid);  		
	
	HIGHT_LIGHT();
	MOVETO(++x,y); 
	printf(" %-15s %-10s   %-15s  %10s  %10s  %10s    %10s    \n","APP_SNAME","TPROC_REPC"," TRAN_CODE","MQ_KEY","CBYTES","QNUM","QBYTES");
    UN_HIGHT_LIGHT();
    
 	MOVETO(++x,y);    
    printf("-------------------------------------------------------------------------------------------------\n");
	
	int nShow=0;
		
	map<CString,int> mapApps = mq.GetAppsMap();
	map<CString,int>::iterator its; 
	for (its = mapApps.begin(); its != mapApps.end(); its++ ) 
	{

	            
	    CString strSName = its->first;
	    int nMqIndex     = its->second;
	    
		if(strSName.GetLength()<3 || nMqIndex<MQMINDEX_MIN || nMqIndex>MQMINDEX_MAX)
			continue;
			
		CString strCode1 		= " ";
		CString strCode2 		= " ";
		CString strLName 		= "          ";
		CString strRemark 		= " ";
		
		key_t mqkey = mq.GetAppQKey(nMqIndex);
		
		CDictQueue queue;
		struct msqid_ds dsbuf;
		if(queue.SelectQueue(mqkey) != -1 && queue.GetStat(&dsbuf) == 0)
		{
		    
            if( dsbuf.msg_qnum >0 || (strSName == "DEP" || strSName == "LON"  || strSName == "COM" \
                 || strSName == "PFM"  || strSName == "GEN"  || strSName == "IBD" ))
             {
                
 	            MOVETO(++x,y); 
 	            
 	            int nFindQd = GetTprocStatus(strSName.c_str(),"ncbsoqd"); 
 	            int nFindPd = GetTprocStatus(strSName.c_str(),"ncbsopd");
 	            CString strP,strQ;  	            
 	            for(int n=0;n<nFindQd;n++)
     	                strQ += 'Q';
 	            for(int n=0;n<nFindPd;n++)
     	                strP += 'P';     	       
     	        
   	        
     	        if(  nFindQd > 0 ||   nFindPd> 0)     
     	            strLName.Format("[%-3s][%-3s]",strQ.c_str(),strP.c_str());
     	                

           	printf(" (%02d) %-10s %-10s %-6s - %-6s    %#10.8x  %10d  %10d   %10d\n",nMqIndex,strSName.c_str(),
            	strLName.c_str(),strCode1.c_str(),strCode2.c_str(),	
            		dsbuf.msg_perm.key,
            		dsbuf.msg_cbytes,
            		dsbuf.msg_qnum,
            		dsbuf.msg_qbytes);	
            		
 		        nShow++;  
 		                 		
             }
             
		}
		/*
		else 
		{
			printf(" (%02d) %-10s %10s %80s\n",nMqIndex,strSName.c_str(),"  "," ");
			
		}	
		*/
		

		if(nShow >= 10)
		    break;		
			
			
	}//end for

/*
	x++;
	MOVETO(++x,y); 
	printf("TRMQ STATUS:");
    	
	HIGHT_LIGHT();
	MOVETO(++x,y); 
	printf(" %-15s %-10s  %10s  %10s    %10s\n","TRMQ_NAME","PID","CBYTES","QNUM","QBYTES");
    UN_HIGHT_LIGHT();
    
 	MOVETO(++x,y);    
    printf("-------------------------------------------------------------------------------------------------\n");
*/
	
	x+=1;
	MOVETO(++x,y); 
	printf("PROCESS AND TRMQ STATUS:");
	
	HIGHT_LIGHT();
	MOVETO(++x,y); 
	printf(" %-65s  %-50s","PROCESS","TRMQ");
    UN_HIGHT_LIGHT();
         
 	MOVETO(++x,y);    
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    
    FILE *fp=NULL;    
    char buff[1024];  
    memset(buff,0,sizeof(buff));  
    fp = popen("ps -ef|grep 'tcpmain start'|grep -v 'grep' |sort -k4","r");
    if(fp==NULL)    
    {   
        fprintf(stderr,"execute command failed: %s",strerror(errno));    
        return -1;    
    }   
    
    do
    {
        if(feof(fp))
            break;
            
        if(fgets(buff, sizeof(buff), fp))   
        {   	
            MOVETO(++x,y);  
            
            for(int i=0;i<strlen(buff);i++)
                if(buff[i]=='\n')
                    buff[i]=0;   
            printf("%s",buff); 
            
            string sLine = Trim(buff);
            string sPid = Trim(GetStrWithDelim(sLine,1," "));
             
            int pid = atoi(sPid.c_str());
     		key_t mqkey = mq.GetTrmQKey(pid);
    		
    		CDictQueue queue;
    		struct msqid_ds dsbuf;
    		if(queue.SelectQueue(mqkey) != -1 && queue.GetStat(&dsbuf) == 0)
    		{
    				
    			printf(" |  %#10.8x  %10d  %5d  %10d                            \n",	
    				dsbuf.msg_perm.key,
    				dsbuf.msg_cbytes,
    				dsbuf.msg_qnum,
    				dsbuf.msg_qbytes);	
    		}
    		else
    		{
    		    printf(" |  n/a                                                                  \n");  
    		}           
            
            
            
            
        }  
    }while(1); 

    pclose(fp);  
    
    for(int m=x+1;m<=nMaxRow;m++)
    {
        MOVETO(m,y);  
        printf("%120s\n"," ");        
    }

	
	//全屏32+1行
	return 0;
	
}

int GetTcAttr(int& nMaxRow,int& nMaxCol)
{
    FILE *fp=NULL;    
    char buff[1024];  
    memset(buff,0,sizeof(buff));  
    fp = popen("stty -a","r");
    if(fp==NULL)    
    {   
        fprintf(stderr,"execute command failed: %s",strerror(errno));    
        return -1;    
    }   
    
    do
    {
        if(feof(fp))
            break;
            
        if(fgets(buff, sizeof(buff), fp))   
        {   	
            //speed 9600 baud; 34 rows; 134 columns;

            string sLine = Trim(buff);
            if(sLine.find("rows")>=0 && sLine.find("columns")>=0)
            {
                string sRow = Trim(GetStrWithDelim(sLine,1,";"));
                int nFind = sRow.find("rows");
                if(nFind >0)
                {
                    //basic_string substr( size_type index, size_type num = npos ); 
                    string s = sRow.substr(0,nFind);
                    nMaxRow = atoi(s.c_str());
                    
                }
                
                string sCol = Trim(GetStrWithDelim(sLine,2,";"));     
                nFind = sCol.find("columns");
                if(nFind >0)
                {
                    //basic_string substr( size_type index, size_type num = npos ); 
                    string s = sCol.substr(0,nFind);
                    nMaxCol = atoi(s.c_str());
                    
                }                
                
              break;  
            }        
      
            
            
            
            
        }  
    }while(1); 

    pclose(fp);    
    
    return 0;  
    
}

#include <unistd.h>
#include <sys/types.h>

int main(int argc,char **argv)
{
	
	//CUtilMisc::GetTimeInterval(0);
 	//CUtilMisc::Sleep(1,203);
	//printf("TimeInterval: %d ms\n\n",CUtilMisc::GetTimeInterval(1)/1000);
	
    int nMaxRow = 19,nMaxCol = 80;  
    GetTcAttr(nMaxRow,nMaxCol);    
    //printf(" row =%d,col=%d",nMaxRow,nMaxCol); 
    if(nMaxRow <25 || nMaxCol<120)
    {
      printf("错误：当前终端窗口设置过小；请设置当前终端窗口至少可以显示25行，120列，以保证显示效果。\n");
      return -1;  
        
    }	

    signal(SIGINT,SignalCleanup);
    signal(SIGTERM,SignalCleanup);  
    
    CLEAR();    
    HIDE_CURSOR();
    
          	
    while(!g_bSEndFlag)
    {
        ShowStatus(nMaxRow-2,nMaxCol);
        
        time_t nowtime;  
        nowtime = time(NULL);   
        struct tm *ptm;  
        ptm=localtime(&nowtime);  //获取当前系统时间
        
        MOVETO(nMaxRow-1,2);           
        printf("系统时间：%02d:%02d:%02d    刷新频率：%d ms     %70s\n",ptm->tm_hour,ptm->tm_min,ptm->tm_sec,500,"消息队列监控工具 Ver: 1.02");  
     
                      
        CUtilMisc::Sleep(0,500);
            
        if(ptm->tm_sec%10 == 0)
        {
             CLEAR();             
             GetTcAttr(nMaxRow,nMaxCol); 
        }    
          
    }

    SHOW_CURSOR();
    CLEAR();
    
 	printf("\n");
 			              
    return 0;
        	

}