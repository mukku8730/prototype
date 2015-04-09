#ifndef _MAHJONG_END_SCREEN_HEADER_2015_0212_
#define _MAHJONG_END_SCREEN_HEADER_2015_0212_
#include "Screen.h"
class EndScreen :
	public Screen
{
public:
	EndScreen();
	virtual ~EndScreen() throw();
	void Update();
	void Draw();
	Screen* ChangeScreen();
};

#endif //_MAHJONG_END_SCREEN_HEADER_2015_0212_
