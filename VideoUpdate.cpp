// VideoUpdate.cpp: implementation of the CVideoUpdate class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "VideoUpdate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMMPointer<Dator<int> > CVideoUpdate::screenWidth=0;
CMMPointer<Dator<int> > CVideoUpdate::screenHeight=0;
CMMPointer<Dator<int> > CVideoUpdate::screenBPP=0;
int CVideoUpdate::scrWidth=800;
int CVideoUpdate::scrHeight=600;
int CVideoUpdate::scrBPP=16;

CVideoUpdate::CVideoUpdate()
{

}

CVideoUpdate::~CVideoUpdate()
{

}

bool CVideoUpdate::Start()
{
	assert(screenWidth && screenHeight && screenBPP);

	if(-1==SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		CLog::Get().Write(LOG_CLIENT,IDS_GENERIC_SUB_INIT_FAIL,"Video",SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	int flags = SDL_OPENGL | SDL_ANYFORMAT | SDL_FULLSCREEN;

	if(!SDL_SetVideoMode(scrWidth, scrHeight, scrBPP, flags))
	{
		CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, scrBPP, SDL_GetError());
		return false;
	}

	//hide the mouse cursor
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

void CVideoUpdate::Update()
{
	SDL_GL_SwapBuffers();
}

void CVideoUpdate::Stop()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}