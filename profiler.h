#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#define MAX_PROFILER_SAMPLES 50

class IProfilerOutputHandler;
class CProfileSample;

class CProfileSample
{
public:
	CProfileSample(std::string sampleName);
	~CProfileSample();

	static void Output();

	static void ResetSample(std::string sampleName);
	static void ResetAll();

	static IProfilerOutputHandler *outputHandler;

	static bool bProfilerIsRunning;

protected:
	//index into the array of samples
	int iSampleIndex;
	int iParentIndex;

	inline float GetTime(){ return ((float)SDL_GetTicks())/1000.0f; }

	static struct profileSample
	{
		profileSample()
		{
			bIsValid=false; 
			dataCount=0;
			averagePc=minPc=maxPc=-1;
		}

		bool bIsValid;		//whether or not this sample is valid (for use with fixed-size arrays)
		bool bIsOpen;		//is this sample currently being profiled?
		unsigned int callCount;	//number of times this sample has been profiled this frame
		std::string name;	//name of the sample
		
		float startTime;	//starting time on the clock, in seconds
		float totalTime;	//total time recorded across all profiles of this sample
		float childTime;	//total time taken by children of this sample

		int parentCount;	//number of parents this sample has (useful for indenting)

		float averagePc;	//average percentage of game loop time taken up
		float minPc;		//minimum percentage of game loop time taken up
		float maxPc;		//maximum percentage of game loop time taken up
		unsigned long dataCount;//number of percentage values that have been stored
	} samples[MAX_PROFILER_SAMPLES];
	static int lastOpenedSample;
	static int openSampleCount;
	static float rootBegin, rootEnd;
};

class IProfilerOutputHandler
{
public:
	virtual void BeginOutput(float tTotal)=0;
	virtual void Sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount)=0;
	virtual void EndOutput()=0;
};

#ifdef _DEBUG
#define PROFILE(name) CProfileSample _profile_sample(name);
#else
#define PROFILE(name)
#endif

#endif