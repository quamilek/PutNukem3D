// Kernel.cpp: implementation of the CKernel class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "Kernel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKernel::CKernel()
{
	SDL_Init(0);
	//SDLNet_Init();
}

CKernel::~CKernel()
{
	//SDLNet_Quit();
	SDL_Quit();
}

int CKernel::Execute()
{

	while(taskList.size())
	{
		{
			PROFILE("Kernel task loop");

			std::list< CMMPointer<ITask> >::iterator it, thisIt;
			for(it=taskList.begin();it!=taskList.end();)
			{
				ITask *t=(*it);
				it++;
				if(!t->canKill)t->Update();
			}
			//loop again to remove dead tasks
			for(it=taskList.begin();it!=taskList.end();)
			{
				ITask *t=(*it);
				thisIt=it; it++;
				if(t->canKill)
				{
					t->Stop();
					// 25-07-03 - updated this to use erase() rather than remove()
					taskList.erase(thisIt);
					t=0;
				}
			}
			IMMObject::CollectGarbage();
		}
#ifdef _DEBUG
		CProfileSample::Output();
#endif
	}

	return 0;
}

bool CKernel::AddTask(CMMPointer<ITask> t)
{
	if(!t->Start())return false;

	//keep the order of priorities straight
	std::list< CMMPointer<ITask> >::iterator it;
	for(it=taskList.begin();it!=taskList.end();it++)
	{
		CMMPointer<ITask> &comp=(*it);
		if(comp->priority>t->priority)break;
	}
	taskList.insert(it,t);
	return true;
}

void CKernel::SuspendTask(CMMPointer<ITask> &t)
{
	//check that this task is in our list - we don't want to suspend a task that isn't running
	if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end())
	{
		t->OnSuspend();
		taskList.remove(t);
		pausedTaskList.push_back(t);
	}
}

void CKernel::ResumeTask(CMMPointer<ITask> &t)
{
	if(std::find(pausedTaskList.begin(),pausedTaskList.end(),t)!=pausedTaskList.end())
	{
		t->OnResume();
		pausedTaskList.remove(t);
		//keep the order of priorities straight
		std::list< CMMPointer<ITask> >::iterator it;
		for(it=taskList.begin();it!=taskList.end();it++)
		{
			CMMPointer<ITask> &comp=(*it);
			if(comp->priority>t->priority)break;
		}
		taskList.insert(it,t);
	}
}

void CKernel::RemoveTask(CMMPointer<ITask> &t)
{
	if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end())
	{
		t->canKill=true;
	}
}

void CKernel::KillAllTasks()
{
	for(std::list< CMMPointer<ITask> >::iterator it=taskList.begin();it!=taskList.end();it++)
	{
		(*it)->canKill=true;
	}
}
