#ifndef FUNCTOR_H_INCLUDED
#define FUNCTOR_H_INCLUDED

#include "mmanager.h"

class Functor : public IMMObject
{
public:
	virtual int operator ()()=0;
};

template<class T>
class ObjFunctor : public Functor
{
protected:
	T *obj;
	typedef int (T::*funcType)();
	funcType func;
public:
	AUTO_SIZE;

	ObjFunctor(T *o, funcType f) 
	{ obj=o; func=f; }

	int operator ()() 
	{ return (obj->*func)(); }
};

template<class T>
class MMObjFunctor : public Functor
{
protected:
	CMMPointer<T> obj;
	typedef int (T::*funcType)();
	funcType func;
public:
	AUTO_SIZE;

	MMObjFunctor(T *o, funcType f) 
	{ obj=o; func=f; }

	int operator ()() 
	{ return (obj->*func)(); }
};

#endif