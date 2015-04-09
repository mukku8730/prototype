#include "Hai.h"
#include <cassert>
struct HaiStruct{
	HaiType haiType;
	HaiColor color;
	int number;
};

static const HaiStruct HaiTBL[]
{
	{ HaiType_none, HaiColor_none, SuuHai_none },
	{ HaiType_man_1, HaiColor_manzu, SuuHai_1 },
	{ HaiType_man_2, HaiColor_manzu, SuuHai_2 },
	{ HaiType_man_3, HaiColor_manzu, SuuHai_3 },
	{ HaiType_man_4, HaiColor_manzu, SuuHai_4 },
	{ HaiType_man_5, HaiColor_manzu, SuuHai_5 },
	{ HaiType_man_6, HaiColor_manzu, SuuHai_6 },
	{ HaiType_man_7, HaiColor_manzu, SuuHai_7 },
	{ HaiType_man_8, HaiColor_manzu, SuuHai_8 },
	{ HaiType_man_9, HaiColor_manzu, SuuHai_9 },
	{ HaiType_pin_1, HaiColor_pinzu, SuuHai_1 },
	{ HaiType_pin_2, HaiColor_pinzu, SuuHai_2 },
	{ HaiType_pin_3, HaiColor_pinzu, SuuHai_3 },
	{ HaiType_pin_4, HaiColor_pinzu, SuuHai_4 },
	{ HaiType_pin_5, HaiColor_pinzu, SuuHai_5 },
	{ HaiType_pin_6, HaiColor_pinzu, SuuHai_6 },
	{ HaiType_pin_7, HaiColor_pinzu, SuuHai_7 },
	{ HaiType_pin_8, HaiColor_pinzu, SuuHai_8 },
	{ HaiType_pin_9, HaiColor_pinzu, SuuHai_9 },
	{ HaiType_sou_1, HaiColor_souzu, SuuHai_1 },
	{ HaiType_sou_2, HaiColor_souzu, SuuHai_2 },
	{ HaiType_sou_3, HaiColor_souzu, SuuHai_3 },
	{ HaiType_sou_4, HaiColor_souzu, SuuHai_4 },
	{ HaiType_sou_5, HaiColor_souzu, SuuHai_5 },
	{ HaiType_sou_6, HaiColor_souzu, SuuHai_6 },
	{ HaiType_sou_7, HaiColor_souzu, SuuHai_7 },
	{ HaiType_sou_8, HaiColor_souzu, SuuHai_8 },
	{ HaiType_sou_9, HaiColor_souzu, SuuHai_9 },
	{ HaiType_ton, HaiColor_jihai, Jihai_ton },
	{ HaiType_nan, HaiColor_jihai, Jihai_nan },
	{ HaiType_sha, HaiColor_jihai, Jihai_sha },
	{ HaiType_pee, HaiColor_jihai, Jihai_pee },
	{ HaiType_haku, HaiColor_jihai, Jihai_haku },
	{ HaiType_hatsu, HaiColor_jihai, Jihai_hatsu },
	{ HaiType_chun, HaiColor_jihai, Jihai_chun },
};
HaiType Hai::GetHaiType(int haiNumber)
{
	return HaiTBL[haiNumber].haiType;
}

HaiColor Hai::GetHaiColor(HaiType haiType)
{
	if (HaiTBL[haiType].color > HaiColor_MAX){
		assert(0);
	}
	return HaiTBL[haiType].color;
}

int Hai::GetHaiNum(HaiType haiType)
{
	bool yaku[46];
	if (HaiTBL[haiType].number > SuuHai_MAX){
		assert(0);
	}
	return HaiTBL[haiType].number;
}

int Hai::GetHaiNumber(HaiType haiType)
{
	if (HaiTBL[haiType].number > SuuHai_MAX){
		assert(0);
	}
	return haiType;
}

int Hai::GetHaiMin()
{
	return HaiType_man_1;
}

int Hai::GetHaiMax()
{
	return HaiType_MAX;
}
