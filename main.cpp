#include "engine.h"
#include "game.h"



class CPongTask : public ITask
{
public:
	float p1pos, p2pos;
	float paddleWidth, paddleHeight;
	float ballX, ballY, ballVX, ballVY;
	float ballSize;

	bool Start()
		{


			InitRandomNumbers();

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glShadeModel(GL_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

			paddleWidth=0.1f; paddleHeight=0.01f;
			p1pos=p2pos=0.5f;
			ballX=0.5f; ballY=0.5f;
			ballVX=(float)(rand()%20-10)/20;
			ballVY=(float)(rand()%20-10)/20;
			ballSize=0.01f;


			return true;
		}
	void Update()
		{
		    PROFILE("PongTask Update");
			glClear(GL_COLOR_BUFFER_BIT);
			if(CInputTask::mouseDown(SDL_BUTTON_LEFT))CKernel::GetSingleton().KillAllTasks();

			glBegin(GL_QUADS);
			{
				glColor4f(1.0f,1.0f,1.0f,1.0f);

				//draw the ball
				glVertex2f(ballX-ballSize, ballY-ballSize);
				glVertex2f(ballX+ballSize, ballY-ballSize);
				glVertex2f(ballX+ballSize, ballY+ballSize);
				glVertex2f(ballX-ballSize, ballY+ballSize);

				//paddles
				glVertex2f(p2pos-paddleWidth, 0);
				glVertex2f(p2pos+paddleWidth, 0);
				glVertex2f(p2pos+paddleWidth, paddleHeight);
				glVertex2f(p2pos-paddleWidth, paddleHeight);

				glVertex2f(p1pos-paddleWidth, 1-paddleHeight);
				glVertex2f(p1pos+paddleWidth, 1-paddleHeight);
				glVertex2f(p1pos+paddleWidth, 1);
				glVertex2f(p1pos-paddleWidth, 1);
			}
			glEnd();

			p1pos+=((float)CInputTask::dX)/200.0f;
			if(p1pos<paddleWidth)p1pos=paddleWidth;
			if(p1pos>1-paddleWidth)p1pos=1-paddleWidth;

			ballX+=ballVX*CGlobalTimer::dT; ballY+=ballVY*CGlobalTimer::dT;
			if(ballX<ballSize)ballVX=qAbs(ballVX);
			if(ballX>1-ballSize)ballVX=-qAbs(ballVX);
			if(ballY<ballSize+paddleHeight)
			{
				if((ballX>p2pos-paddleWidth)&&(ballX<p2pos+paddleWidth))
				{
					ballVY=qAbs(ballVY);
				}else{
					CKernel::GetSingleton().KillAllTasks();
				}
			}
			if(ballY>1-ballSize-paddleHeight)
			{
				if((ballX>p1pos-paddleWidth)&&(ballX<p1pos+paddleWidth))
				{
					ballVY=-qAbs(ballVY);
				}else{
					CKernel::GetSingleton().KillAllTasks();
				}
			}

			if(ballX>p2pos)p2pos+=0.1f*CGlobalTimer::dT;
			if(ballX<p2pos)p2pos-=0.1f*CGlobalTimer::dT;
			if(p2pos<paddleWidth)p2pos=paddleWidth;
			if(p2pos>1-paddleWidth)p2pos=1-paddleWidth;

		}
	void Stop()
	{

	};
	AUTO_SIZE;
};

void CApplication::Run(int argc, char *argv[])
{

	//open logfiles
	if(!CLog::Get().Init())return;


	//create a couple of singletons
	new CSettingsManager();
	new CKernel();
	new CObjLoader();
	new CMeshManager();

	//parse the 'settings.eng' file
	CSettingsManager::GetSingleton().ParseFile("settings.esf");

	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc>1)
		for(int i=1;i<argc;i++)
			CSettingsManager::GetSingleton().ParseSetting(std::string(argv[i]));

	videoTask = new CVideoUpdate();
	videoTask->priority=10000;
	CKernel::GetSingleton().AddTask(CMMPointer<ITask>(videoTask));

	inputTask = new CInputTask();
	inputTask->priority=20;
	CKernel::GetSingleton().AddTask(CMMPointer<ITask>(inputTask));

	//soundTask = new CSoundTask();
	//soundTask->priority=50;
	//CKernel::GetSingleton().AddTask(CMMPointer<ITask>(soundTask));

	globalTimer=new CGlobalTimer();
	globalTimer->priority=10;
	CKernel::GetSingleton().AddTask(CMMPointer<ITask>(globalTimer));

	/*CPongTask pong;
	pong.priority=100;
	CKernel::GetSingleton().AddTask(CMMPointer<ITask>(&pong));*/

    //render the state of the game
	renderTask=new CRenderTask();
	renderTask->priority = 101;
	CKernel::GetSingleton().AddTask(CMMPointer<ITask>(renderTask));

	//set up the profiler with an output handler
	CProfileLogHandler profileLogHandler;
	CProfileSample::outputHandler=&profileLogHandler;

	//main game loop
	CKernel::GetSingleton().Execute();

    CProfileSample::Output();

	//clean up singletons
	delete CKernel::GetSingletonPtr();
	delete CSettingsManager::GetSingletonPtr();
}

int main(int argc, char *argv[])
{

	new CApplication();
	CApplication::GetSingleton().Run(argc,argv);
	delete CApplication::GetSingletonPtr();



	//clean up any remaining unreleased objects
	IMMObject::CollectRemainingObjects(true);

	return 0;
}
