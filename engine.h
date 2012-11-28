#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#pragma warning ( disable : 4786 )


#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <list>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <cassert>
#include <sstream>
#include <cmath>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#endif


//even though resource.h is technically a Win32-resource file, it's just a bunch of defines, so it's ok (and necessary)
#include "resource.h"

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include "glew.h"
#include <sdl/sdl.h>
#include <sdl/sdl_opengl.h>
#include <sdl/sdl_net.h>
#include <sdl/sdl_image.h>
#include <sdl/sdl_ttf.h>
#include <GL/glfw.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fmod.h>

//foundation layer headers
#include "log.h"
#include "mmanager.h"
#include "singleton.h"
#include "functor.h"
#include "dator.h"
#include "kernel.h"
#include "settings.h"
#include "profiler.h"
#include "profileloghandler.h"


//task pool
#include "videoupdate.h"
#include "globalTimer.h"
#include "inputtask.h"
#include "soundtask.h"
#include "rendertask.h"

//misc
#include "misc.h"
#include "math.h"

#endif
