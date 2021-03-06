//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 技术平台公共类库
//  @ File Name : iniconfig.h
//  @ Date : 2013/7/15
//  @ Author : disp
//
//


#if !defined(_CINICONFIG_H)
#define _CINICONFIG_H


#include <vector>
#include <map>
#include <string>
#include <algorithm>   
#include <functional>   

using namespace std;

class CIniConfig
{
public:
	CIniConfig();
	CIniConfig(const char* pFilePath);
	~CIniConfig();
	
public:
    int Init(const char* pFilePath);
    bool IsInit();
    int GetData(const char* pSection, const char* pKey, char* pData);
    void TestPrint();
    void Uninit();
   
protected:
	map< string, map<string,string> > m_mapdata;	//存储INI各个section中，key=value
	
protected:
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
	inline   bool IsFound(const string src,const string sub)   
	{   
		return (src.find(sub) != string::npos);
	}   
	
	vector<string> GetStrWithDelim(const string src, const string delims);
	string GetStrWithDelim(const string src, const int pos,const string delims);
	string GetStrDivideBetween(const string src, const string leftdelim, const string rightdelim);
	
};

#endif  //_CINICONFIG_H
