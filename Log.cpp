// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "Log.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CMMPointer< CSettingVariable<std::string> > CLog::appLogName=0;
CMMPointer< CSettingVariable<std::string> > CLog::clientLogName=0;
CMMPointer< CSettingVariable<std::string> > CLog::serverLogName=0;
*/

CLog::CLog()
{

}

CLog &CLog::Get()
{
	static CLog log;
	return log;
}

bool CLog::Init()
{
	appLog.open("applog.txt");
	clientLog.open("clntlog.txt");
	serverLog.open("srvrlog.txt");
	//user errors get logged to client

	//load the strings file
	if(!LoadStrings())return false;

	return true;
}

void CLog::Write(int target, const char *msg, ...)
{
	va_list args; va_start(args,msg);
	char szBuf[1024];
	vsprintf(szBuf,msg,args);

	if(target&LOG_APP)
	{
		appLog<<szBuf<<"\n";
#ifdef _DEBUG
		appLog.flush();
#endif
	}
	if(target&LOG_CLIENT)
	{
		clientLog<<szBuf<<"\n";
#ifdef _DEBUG
		clientLog.flush();
#endif
	}
	if(target&LOG_SERVER)
	{
		serverLog<<szBuf<<"\n";
#ifdef _DEBUG
		serverLog.flush();
#endif
	}
	if(target&LOG_USER)
	{
#ifdef WIN32
		MessageBox(NULL,szBuf,"Message",MB_OK);
#else
#error User-level logging is not implemented for this platform.
#endif
	}
	va_end(args);
}

void CLog::Write(int target, unsigned long msgID, ...)
{
	va_list args; va_start(args, msgID);
	char szBuf[1024];
	vsprintf(szBuf,logStrings[msgID].c_str(),args);
	Write(target,szBuf);
	va_end(args);
}

#ifdef WIN32
//under Win32, the strings get read in from a string table resource
bool CLog::LoadStrings()
{
	for(unsigned long i=0;i<MAX_LOG_STRINGS;i++)
	{
		char szBuf[1024];
		if(!LoadString(GetModuleHandle("engine"),i,szBuf,1024))break; //returning 0 means no more strings
		logStrings[i]=szBuf;
	}
	return true;
}

#else
//other platforms load the strings in from strings.txt
bool CLog::LoadStrings()
{
	std::ifstream in("strings.txt");
	if(!in.is_open())return false;

	unsigned long index=0;

	while(!in.eof())
	{
		char szBuf[1024];
		in.getline(szBuf,1024);
		logStrings[index++]=szBuf;
	}

	return true;
}

#endif
