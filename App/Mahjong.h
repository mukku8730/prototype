#ifndef _MAHJONG_SIMULATE_MARJONG_HEADER_2015_0216_
#define _MAHJONG_SIMULATE_MARJONG_HEADER_2015_0216_

#include "Screen.h"
#include <memory>

class Mahjong
{
public:
	Mahjong();
	virtual ~Mahjong() throw();
	void Update();
	void Draw();
private:
	std::unique_ptr<Screen> m_screenPtr;
};

#endif //_MAHJONG_MARJONG_HEADER_2015_0216_
