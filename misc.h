#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <algorithm>

using namespace std;

inline float clamp(float val, float minVal, float maxVal)
{
	return min(max(val,minVal),maxVal);
}

struct frect
{
	float x1, y1, x2, y2;
	frect(){x1=y1=x2=y1=0;}
	frect(float ux1, float uy1, float ux2, float uy2){x1=ux1; y1=uy1; x2=ux2; y2=uy2; Normalize();}
	void Normalize(){if(x1>x2)std::swap(x1,x2); if(y1>y2)std::swap(y1,y2);}
	frect &operator =(frect &rc){x1=rc.x1; y1=rc.y1; x2=rc.x2; y2=rc.y2; return *this;}
};

float inline pow(float base, int power)
{
	if(power==1)return base;
	if(power==0)return 1;
	float powerf = power;
	return base*pow(base, powerf-1);
}

float inline frand(int precis=4)
{
	int val=(int)pow(10,precis);
	return (rand()%val)/(float)val;
}

void inline InitRandomNumbers()
{
	srand((unsigned int)time(0));
}

template<class T>
T qAbs(T v)
{
	return (v>0)?v:-v;
}

class rgba
{
public:
	float r,g,b,a;
	rgba(){r=g=b=a=0.0f;}
	rgba &operator =(rgba &c){r=c.r; g=c.g; b=c.b; a=c.a; return *this;}
};



#endif
