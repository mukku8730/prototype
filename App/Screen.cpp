#include "Screen.h"

Screen::Screen()
	:m_frame(0)
	,m_isNext(false)
{
}

Screen::~Screen() throw()
{
}

bool Screen::GetIsNext() const
{
	return m_isNext;
}


