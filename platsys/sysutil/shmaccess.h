//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : ����ƽ̨�������
//  @ File Name : shmaccess.h
//  @ Date : 2013/7/23
//  @ Author : disp
//
//


#if !defined(_CSHMACCESS_H)
#define _CSHMACCESS_H

#include "shmbase.h"

class CDict;
class CAreaLock;

typedef int 	DA_OpenSelect(CDict *pDict,char* pMat);
typedef int		DA_GetDataCount();
typedef int		DA_FetchData(CDict *pDict,int nIndex);
typedef int		DA_CloseSelect();
typedef int		DA_UpdateData(CDict *pDict,char* pMat);

typedef struct 
{
	
	void *pvLibraryHandle;
	DA_OpenSelect 		*pfnOpenSelect;
	DA_GetDataCount 	*pfnGetDataCount;
	DA_FetchData 		*pfnFetchData;
	DA_CloseSelect 		*pfnCloseSelect;
	DA_UpdateData		*pfnUpdateData;
	
}DSEX_ACCESS;

class CShmAccess : public CShmBase
{
public:
	CShmAccess();
	CShmAccess(const char* pFilePath);
	~CShmAccess();
	
public:
    int OpenSelect(CDict* pDict);
    int GetDataCount();
    int FetchData(CDict* pDict, int nIndex);
    void CloseSelect();
    int UpdateData(CDict* pDict);
    
protected:
	CAreaLock* m_pLock;
	char* m_pMatAddress;
	DSEX_ACCESS m_dsex;
	int LoadDsexFn(const char* pFilePaht,DSEX_ACCESS* pDsexLoad);
	int FreeDsexFn(DSEX_ACCESS* pDsexLoad);
	int GetDsInfo(const char* pDataSource,key_t& dskey,CString& strSoPath);
	
};

#endif  //_CSHMACCESS_H