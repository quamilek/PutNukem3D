// SoundTask.h: interface for the CSoundTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDTASK_H__5021E1A5_CCF3_4204_A058_D434A089A307__INCLUDED_)
#define AFX_SOUNDTASK_H__5021E1A5_CCF3_4204_A058_D434A089A307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Kernel.h"

class CSoundTask : public ITask  
{
public:
	CSoundTask();
	virtual ~CSoundTask();

	bool Start();
	void OnSuspend();
	void Update();
	void OnResume();
	void Stop();

	AUTO_SIZE;

protected:
	CMMPointer<CMMDynamicBlob<bool> > isPaused;
};

#endif // !defined(AFX_SOUNDTASK_H__5021E1A5_CCF3_4204_A058_D434A089A307__INCLUDED_)
