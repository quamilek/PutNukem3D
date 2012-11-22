// GlobalTimer.cpp: implementation of the CGlobalTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "GlobalTimer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

float CGlobalTimer::dT=0;
unsigned long CGlobalTimer::lastFrameIndex=0;
unsigned long CGlobalTimer::thisFrameIndex=0;

CGlobalTimer::CGlobalTimer()
{

}

CGlobalTimer::~CGlobalTimer()
{

}

bool CGlobalTimer::Start()
{
	thisFrameIndex=SDL_GetTicks();
	lastFrameIndex=thisFrameIndex;
	dT=0;
	return true;
}

void CGlobalTimer::Update()
{
	lastFrameIndex=thisFrameIndex;
	thisFrameIndex=SDL_GetTicks();
	dT=((float)(thisFrameIndex-lastFrameIndex))/1000.0f;
}

void CGlobalTimer::Stop()
{

}