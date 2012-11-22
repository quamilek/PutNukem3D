// InputTask.h: interface for the CInputTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYBOARDTASK_H__4953EF06_7C18_4433_B590_47E045E43576__INCLUDED_)
#define AFX_KEYBOARDTASK_H__4953EF06_7C18_4433_B590_47E045E43576__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engine.h"

class CInputTask : public ITask  
{
public:
	CInputTask();
	virtual ~CInputTask();

	bool Start();
	void Update();
	void Stop();

	static unsigned char *keys;
	static CMMPointer<CMMDynamicBlob<unsigned char> > oldKeys;
	static int keyCount;
	
	static int dX,dY;
	static unsigned int buttons;
	static unsigned int oldButtons;

	static bool inline curKey(int index) { return (keys[index]!=0); }
	static bool inline oldKey(int index) { return ((*oldKeys)[index]!=0); }

	//some helper functions to make certain things easier
	static bool inline keyDown(int index)		{ return ( curKey(index))&&(!oldKey(index)); }
	static bool inline keyStillDown(int index)	{ return ( curKey(index))&&( oldKey(index)); }
	static bool inline keyUp(int index)		{ return (!curKey(index))&&( oldKey(index)); }
	static bool inline keyStillUp(int index)	{ return (!curKey(index))&&(!oldKey(index)); }

	static bool inline curMouse(int button) { return (buttons&SDL_BUTTON(button))!=0; }
	static bool inline oldMouse(int button) { return (oldButtons&SDL_BUTTON(button))!=0; }

	static bool inline mouseDown(int button)	{ return ( curMouse(button))&&(!oldMouse(button)); }
	static bool inline mouseStillDown(int button)	{ return ( curMouse(button))&&( oldMouse(button)); }
	static bool inline mouseUp(int button)		{ return (!curMouse(button))&&( oldMouse(button)); }
	static bool inline mouseStillUp(int button)	{ return (!curMouse(button))&&(!oldMouse(button)); }

	AUTO_SIZE;
};

#endif // !defined(AFX_KEYBOARDTASK_H__4953EF06_7C18_4433_B590_47E045E43576__INCLUDED_)
