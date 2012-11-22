#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "engine.h"

class CApplication : public Singleton<CApplication>
{
public:
	CMMPointer<CVideoUpdate> videoTask;
	CMMPointer<CGlobalTimer> globalTimer;
	CMMPointer<CInputTask> inputTask;
	CMMPointer<CSoundTask> soundTask;

	void Run(int argc, char *argv[]);
};

#endif