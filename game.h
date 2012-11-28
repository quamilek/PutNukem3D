#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include "engine.h"
//#include "RenderTask.h"

class CApplication : public Singleton<CApplication>
{
public:
	CMMPointer<CVideoUpdate> videoTask;
	CMMPointer<CGlobalTimer> globalTimer;
	CMMPointer<CInputTask> inputTask;
	CMMPointer<CSoundTask> soundTask;
    CMMPointer<CRenderTask> renderTask;

	void Run(int argc, char *argv[]);
};

#endif
