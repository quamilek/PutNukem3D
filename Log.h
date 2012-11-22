// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__78348862_06C2_4FAA_B192_13F09596E2FD__INCLUDED_)
#define AFX_LOG_H__78348862_06C2_4FAA_B192_13F09596E2FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"
#include "mmanager.h"

const int LOG_APP=1;
const int LOG_CLIENT=2;
const int LOG_SERVER=4;
const int LOG_USER=8;

#define MAX_LOG_STRINGS 256

class CLog  
{
protected:
	CLog();

	std::ofstream appLog;
	std::ofstream clientLog;
	std::ofstream serverLog;

	std::string logStrings[MAX_LOG_STRINGS];
	bool LoadStrings();

public:
	static CLog &Get();

	bool Init();

	void Write(int target, const char *msg, ...);
	void Write(int target, unsigned long msgID, ...);
};

#endif // !defined(AFX_LOG_H__78348862_06C2_4FAA_B192_13F09596E2FD__INCLUDED_)
