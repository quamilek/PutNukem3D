// SoundTask.cpp: implementation of the CSoundTask class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"

///////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CSoundTask::CSoundTask()
{

}

CSoundTask::~CSoundTask()
{

}

bool CSoundTask::Start()
{

	if(FALSE==FSOUND_Init(44100, 32, 0))return false;
	return true;
}

void CSoundTask::OnSuspend()
{
	//pause all channels, storing the pause state in the isPaused array
	//once the states are stored we can use FSOUND_ALL to pause all channels the easy way
	int chCount=FSOUND_GetMaxChannels();
	isPaused=new CMMDynamicBlob<bool>(chCount);
	for(int i=0;i<chCount;i++)
	{
		if(FSOUND_IsPlaying(i))
		{
			isPaused[i]=true;
		}else{
			isPaused[i]=false;
		}
	}
	FSOUND_SetPaused(FSOUND_ALL,TRUE);
}

void CSoundTask::Update()
{
	//we don't need to do anything, FMOD does it all for us :)
}

void CSoundTask::OnResume()
{
	//unpause all the flagged channels
	if(isPaused)
	{
		int chCount=FSOUND_GetMaxChannels();
		for(int i=0;i<chCount;i++)
		{
			if(isPaused[i])FSOUND_SetPaused(i,FALSE);
		}
		isPaused=0;
	}
}

void CSoundTask::Stop()
{
	FSOUND_Close();
}
*/
