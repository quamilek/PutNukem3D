// CmdLineParser.h: interface for the CCmdLineParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDLINEPARSER_H__D966E309_9B9F_4FD0_B991_6A096F743669__INCLUDED_)
#define AFX_CMDLINEPARSER_H__D966E309_9B9F_4FD0_B991_6A096F743669__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "singleton.h"
#include "dator.h"

class CSettingsManager : public Singleton<CSettingsManager>
{
public:
	CSettingsManager();
	virtual ~CSettingsManager();

	void RegisterVariable(std::string name, CMMPointer<BaseDator> var);
	void SetVariable(std::string &name, std::string &value, int bias=0);

	void CreateStandardSettings();
	void DestroyStandardSettings();

	void ParseSetting(std::string str);
	void ParseFile(std::string filename);

protected:
	std::map<std::string, CMMPointer<BaseDator> > settingMap;
};



#endif // !defined(AFX_CMDLINEPARSER_H__D966E309_9B9F_4FD0_B991_6A096F743669__INCLUDED_)
