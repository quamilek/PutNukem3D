// CmdLineParser.cpp: implementation of the CSettingsParser class.
//
//////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "settings.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingsManager::CSettingsManager()
{
	settingMap.clear();
	CreateStandardSettings();
}

CSettingsManager::~CSettingsManager()
{
	DestroyStandardSettings();
}

void CSettingsManager::RegisterVariable(std::string name, CMMPointer<BaseDator> var)
{
	settingMap[name]=var;
}

void CSettingsManager::SetVariable(std::string &name, std::string &value, int bias)
{
	if(!settingMap[name])return; //setting doesn't exist
	if(settingMap[name]->hasMultipleValues())
	{
		std::list<std::string> valueList;
		valueList.clear();

		//check for semicolon-seperated values
		if(value.find(';')!=-1)
		{
			//split the string into semicolor-seperated chunks
			int first=0, last;
			while((last=value.find(';',first))!=-1)
			{
				valueList.push_back(value.substr(first,last-first));
				first=last+1;
			}
			valueList.push_back(value.substr(first));
		}else{
			valueList.push_back(value);
		}

		for(std::list<std::string>::iterator it=valueList.begin(); it!=valueList.end(); it++)
		{
			if(bias>0)
			{
				(*settingMap[name])+=(*it);
			}else if(bias<0)
			{
				(*settingMap[name])-=(*it);
			}else{
				(*settingMap[name])=(*it);
			}
		}
	}else{
		//just assign the value
		(*settingMap[name])=value;
	}
}

void CSettingsManager::ParseSetting(std::string str)
{
	int bias=0; std::string name, value;
	//test for bias
	if((str[0]=='+')||(str[0]=='-'))
	{
		bias=((str[0]=='+')*2)-1; //+ maps to 1*2-1=1, - maps to 0*2-1=-1
		str=str.substr(1); //remove the first character from the string
	}
	//test for '='
	int eqPos=str.find('=');
	if(eqPos!=-1)
	{
		//there's an = sign in there
		//so split either side of it
		name=str.substr(0,eqPos);
		value=str.substr(eqPos+1);
	}else{
		//there's no equal sign
		//we use the bias to construct a boolean value
		//so that flags can be +flag (mapping to flag=1) or -flag (mapping to flag=0)
		name=str;
		char szBuf[5];
		sprintf(szBuf,"%i",(bias+1)/2);
		value=szBuf;
	}
	//set the variable
	SetVariable(name,value,bias);
}

void CSettingsManager::ParseFile(std::string filename)
{
	std::ifstream in(filename.c_str());
	if(!in.is_open())return; //couldn't open
	while(!in.eof())
	{
		char szBuf[1024];
		in.getline(szBuf,1024);
		ParseSetting(szBuf);
	}
}

#define SETTING(type, target, var, name) target=new Dator<type>(var); RegisterVariable(std::string(name),CMMPointer<BaseDator>(target));
#define LIST(type, target, var, name) target=new ListDator<type>(var); RegisterVariable(std::string(name),CMMPointer<BaseDator>(target));

void CSettingsManager::CreateStandardSettings()
{
	SETTING(int,	CVideoUpdate::screenWidth,		CVideoUpdate::scrWidth,		"screenX"	);
	SETTING(int,	CVideoUpdate::screenHeight,		CVideoUpdate::scrHeight,	"screenY"	);
	SETTING(int,	CVideoUpdate::screenBPP,		CVideoUpdate::scrBPP,		"screenBPP"	);
}

void CSettingsManager::DestroyStandardSettings()
{
	CVideoUpdate::screenWidth	= 0;
	CVideoUpdate::screenHeight	= 0;
	CVideoUpdate::screenBPP		= 0;

}
