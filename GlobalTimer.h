// GlobalTimer.h: interface for the CGlobalTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALTIMER_H__90C3FE42_3400_4978_8BC5_7D905F3C8E63__INCLUDED_)
#define AFX_GLOBALTIMER_H__90C3FE42_3400_4978_8BC5_7D905F3C8E63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"

class CGlobalTimer : public ITask
{
public:
	CGlobalTimer();
	virtual ~CGlobalTimer();
	AUTO_SIZE;
	
	static float dT;
	static unsigned long lastFrameIndex;
	static unsigned long thisFrameIndex;

	bool Start();
	void Update();
	void Stop();
};

#endif // !defined(AFX_GLOBALTIMER_H__90C3FE42_3400_4978_8BC5_7D905F3C8E63__INCLUDED_)
