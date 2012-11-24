// InputTask.cpp: implementation of the CInputTask class.
//
//////////////////////////////////////////////////////////////////////

#include "InputTask.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

unsigned char *CInputTask::keys=0;
CMMPointer<CMMDynamicBlob<unsigned char> > CInputTask::oldKeys=0;
int CInputTask::keyCount=0;
int CInputTask::dX=0;
int CInputTask::dY=0;
unsigned int CInputTask::buttons=0;
unsigned int CInputTask::oldButtons=0;

CInputTask::CInputTask()
{

}

CInputTask::~CInputTask()
{

}

bool CInputTask::Start()
{
	keys=SDL_GetKeyState(&keyCount);
	oldKeys=new CMMDynamicBlob<unsigned char>(keyCount);
	dX=dY=0;
	SDL_PumpEvents(); SDL_PumpEvents();
	return true;
}

void CInputTask::Update()
{
    PROFILE("InputTask update");

	SDL_PumpEvents();
	oldButtons=buttons;
	buttons=SDL_GetRelativeMouseState(&dX,&dY);
	memcpy((unsigned char*)(*oldKeys),keys,sizeof(unsigned char)*keyCount);
	keys=SDL_GetKeyState(&keyCount);
}

void CInputTask::Stop()
{
	keys=0;
	oldKeys=0;
}
