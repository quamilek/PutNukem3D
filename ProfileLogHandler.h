// ProfileLogHandler.h: interface for the CProfileLogHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILELOGHANDLER_H__CAD57C2F_2BF7_492C_8ED3_EFE606EF3EAC__INCLUDED_)
#define AFX_PROFILELOGHANDLER_H__CAD57C2F_2BF7_492C_8ED3_EFE606EF3EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "profiler.h"

class CProfileLogHandler : public IProfilerOutputHandler  
{
public:
	void BeginOutput(float tTime);
	void EndOutput();
	void Sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount);
};

#endif // !defined(AFX_PROFILELOGHANDLER_H__CAD57C2F_2BF7_492C_8ED3_EFE606EF3EAC__INCLUDED_)
