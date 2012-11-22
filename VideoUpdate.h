// VideoUpdate.h: interface for the CVideoUpdate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOUPDATE_H__FB4B263B_4FA7_4700_BB70_EE5CB1768E83__INCLUDED_)
#define AFX_VIDEOUPDATE_H__FB4B263B_4FA7_4700_BB70_EE5CB1768E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"

class CVideoUpdate : public ITask  
{
public:
	CVideoUpdate();
	virtual ~CVideoUpdate();
	AUTO_SIZE;

	static int scrWidth, scrHeight, scrBPP;
	static CMMPointer<Dator<int> > screenWidth, screenHeight, screenBPP;

	bool Start();
	void Update();
	void Stop();
};

#endif // !defined(AFX_VIDEOUPDATE_H__FB4B263B_4FA7_4700_BB70_EE5CB1768E83__INCLUDED_)
