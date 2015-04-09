#ifndef _MAHJONG_TITLE_SCREEN_HEADER_2015_0212_
#define _MAHJONG_TITLE_SCREEN_HEADER_2015_0212_

#pragma once
#include "Screen.h"
#include "../BillboardString.h"
#include "../Sprites.h"
#include<windows.h>


class TitleScreen :
	public Screen
{
public:
	TitleScreen();
	virtual ~TitleScreen() throw();
	void Update();
	void Draw();
	Screen* ChangeScreen();

private:
	SHORT m_pushKeyState;
	BillboardString *m_pTitle;
	BillboardString *m_pTitle2;
	BillboardString *m_pKeyState;
	int m_keyStateColor;
	bool colorFug;
};

#endif //_MAHJONG_TITLE_SCREEN_HEADER_2015_0212_
