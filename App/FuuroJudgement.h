#ifndef _MAHJONG_FUURO_JUDGEMENT_HEADER_2015_0225_
#define _MAHJONG_FUURO_JUDGEMENT_HEADER_2015_0225_

#include "Judgement.h"
#include "Hai.h"
#include "FuuroHai.h"
#include <memory>
#include <vector>
#include <set>

class FuuroJudgement : Judgement
{
public:
	FuuroJudgement();
	virtual ~FuuroJudgement() throw();
	static bool JudgeChii(std::multiset<HaiType> tehai, HaiType hai);
	static bool JudgePon(std::multiset<HaiType> tehai, HaiType hai);
	static bool JudgeAnkan(std::multiset<HaiType> tehai, HaiType hai);
	static bool JudgeMinkan(std::multiset<HaiType> tehai, HaiType hai);
	static bool JudgeKakan(std::vector<std::shared_ptr<FuuroHai>> fuuroHais, std::multiset<HaiType> tehai, HaiType hai);
};

#endif //_MAHJONG_FUURO_JUDGEMENT_HEADER_2015_0225_
