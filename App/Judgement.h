#ifndef _MAHJONG_JUDGEMENT_HEADER_2015_0225_
#define _MAHJONG_JUDGEMENT_HEADER_2015_0225_

#include "Hai.h"
#include <set>
#include <memory>

class Judgement
{
public:
	Judgement();
	virtual ~Judgement() throw();
protected:
	static void CountHaiTypes(int** haiTypes, std::multiset<HaiType> hais);
};

#endif //_MAHJONG_JUDGEMENT_HEADER_2015_0225_
