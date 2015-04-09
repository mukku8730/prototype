#ifndef _MAHJONG_AGARI_JUDGEMENT_HEADER_2015_0225_
#define _MAHJONG_AGARI_JUDGEMENT_HEADER_2015_0225_

#include "Judgement.h"
#include "Hai.h"
#include "FuuroHai.h"
#include <memory>
#include <vector>

class AgariJudgement : Judgement
{
public:
	AgariJudgement();
	virtual ~AgariJudgement() throw();
	static bool JudgeAgari(std::multiset<HaiType> tehai, HaiType hai);
private:
	static bool JudgeAgariNormal(std::multiset<HaiType> tehai, HaiType hai);
};

#endif //_MAHJONG_AGARI_JUDGEMENT_HEADER_2015_0225_
