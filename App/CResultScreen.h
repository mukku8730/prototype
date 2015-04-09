#ifndef _CRESULT_SCREEN_CLASS_HEADER_20150227_
#define _CRESULT_SCREEN_CLASS_HEADER_20150227_

#include<tchar.h>
#include<iostream>
#include<vector>

class CResuitScreen{
public:
	CResuitScreen();
	virtual ~CResuitScreen() throw();

	void DrawRole(bool *RoleJudgment);

private:

};


#endif //_CRESULT_SCREEN_CLASS_HEADER_20150227_
