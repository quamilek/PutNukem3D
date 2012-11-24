// ProfileLogHandler.cpp: implementation of the CProfileLogHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "ProfileLogHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CProfileLogHandler::BeginOutput(float tTime)
{

	CLog::Get().Write(LOG_APP,IDS_PROFILE_HEADER1,tTime/*, 60.0f/tTime*/);
	CLog::Get().Write(LOG_APP,IDS_PROFILE_HEADER2);
}

void CProfileLogHandler::Sample(/*float rootTime,*/float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount)
{
	//char szBuf[100];
	//for(int i=0;i<parentCount;i++){szBuf[i]=' ';}
	//szBuf[parentCount]=0;
	char namebuf[256], indentedName[256];
	char avg[16], min[16], max[16], num[16], time[16], fps[16];

	sprintf(avg, "%3.1f", fAvg);
	sprintf(min, "%3.1f", fMin);
	sprintf(max, "%3.1f", fMax);
	sprintf(time,"%3.1f", tAvg);
	//sprintf(fps, "%3.1f", 60.0f/rootTime);
	sprintf(num, "%3d",   callCount);

	strcpy( indentedName, name.c_str());
	for( int indent=0; indent<parentCount; ++indent )
	{
		sprintf(namebuf, " %s", indentedName);
		strcpy( indentedName, namebuf);
	}

	CLog::Get().Write(LOG_APP,IDS_PROFILE_SAMPLE,min,avg,max,time,/*fps,*/num,indentedName);
}

void CProfileLogHandler::EndOutput()
{
	CLog::Get().Write(LOG_APP,"\n");
}
