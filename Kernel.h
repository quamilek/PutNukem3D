// Kernel.h: interface for the CKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNEL_H__4E822B7D_1078_4F70_BC8F_3BB4F83ED0AF__INCLUDED_)
#define AFX_KERNEL_H__4E822B7D_1078_4F70_BC8F_3BB4F83ED0AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "singleton.h"

class CClient;
class CServer;

class ITask;

class CKernel : public Singleton<CKernel>
{
public:
	CKernel();
	virtual ~CKernel();

	int Execute();

	bool AddTask(CMMPointer<ITask> t);
	void SuspendTask(CMMPointer<ITask> &t);
	void ResumeTask(CMMPointer<ITask> &t);
	void RemoveTask(CMMPointer<ITask> &t);
	void KillAllTasks();

protected:
	std::list< CMMPointer<ITask> > taskList;
	std::list< CMMPointer<ITask> > pausedTaskList;
};

class ITask : public IMMObject
{
public:
	ITask(){canKill=false;priority=5000;}
	virtual bool Start()=0;
	virtual void OnSuspend(){};
	virtual void Update()=0;
	virtual void OnResume(){};
	virtual void Stop()=0;

	bool canKill;
	long priority;
};

#endif // !defined(AFX_KERNEL_H__4E822B7D_1078_4F70_BC8F_3BB4F83ED0AF__INCLUDED_)
