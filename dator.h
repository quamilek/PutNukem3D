#ifndef DATOR_H_INCLUDED
#define DATOR_H_INCLUDED

#include "mmanager.h"

class BaseDator : public IMMObject
{
protected:
	BaseDator(){}
	BaseDator(BaseDator &b){(*this)=b;}
public:
	virtual BaseDator &operator =(std::string &s)=0;
	virtual BaseDator &operator +=(std::string &s)=0;
	virtual BaseDator &operator -=(std::string &s)=0;
	virtual bool operator ==(std::string &s)=0;
	virtual bool operator !=(std::string &s)=0;

	virtual bool hasMultipleValues()=0;

	virtual operator std::string()=0;
};

template<class T>
class Dator : public BaseDator
{
protected:
	T& target;
	T toVal(std::string &s)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str<<s;
		T res;
		str>>res;
		return res;
	}
	std::string toString(T &val)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str<<val;
		std::string res;
		str>>res;
		return res;
	}
public:
	Dator(T& t) : target(t) {}
	BaseDator &operator =(std::string &s) { target=toVal(s); return *this; }
	BaseDator &operator +=(std::string &s) { target+=toVal(s); return *this; }
	BaseDator &operator -=(std::string &s) { target-=toVal(s); return *this; }
	bool operator ==(std::string &s) { return (s==(std::string)(*this)); }
	bool operator !=(std::string &s) { return (s!=(std::string)(*this)); }
	operator std::string() { return toString(target); }

	bool hasMultipleValues() { return false; }

	AUTO_SIZE;
};

template<class T>
class ListDator : public BaseDator
{
protected:
	std::list<T> &values;
	T toVal(std::string &s)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str<<s;
		T res;
		str>>res;
		return res;
	}
	std::string toString(T &val)
	{
		std::stringstream str;
		str.unsetf(std::ios::skipws);
		str<<val;
		std::string res;
		str>>res;
		return res;
	}
public:
	ListDator(std::list<T> &v) : values(v) { }
	BaseDator &operator =(std::string &s) { values.clear(); values.push_back(toVal(s)); return *this; }
	BaseDator &operator +=(std::string &s) { values.push_back(toVal(s)); return *this; }
	BaseDator &operator -=(std::string &s) { values.remove(toVal(s)); return *this; }
	bool operator ==(std::string &s) { return (std::find(values.begin(),values.end(),toVal(s))!=values.end()); }
	bool operator !=(std::string &s) { return !((*this)==s); }
	
	operator std::string() { return toString(values.back()); }
	operator std::list<T>&() { return values; }

	bool hasMultipleValues(){return true;}

	AUTO_SIZE;


};

#endif