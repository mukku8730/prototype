#ifndef _MAHJONG_HAI_HEADER_2015_0212_
#define _MAHJONG_HAI_HEADER_2015_0212_

enum HaiType
{
	HaiType_none,
	HaiType_man_1,
	HaiType_man_2,
	HaiType_man_3,
	HaiType_man_4,
	HaiType_man_5,
	HaiType_man_6,
	HaiType_man_7,
	HaiType_man_8,
	HaiType_man_9,
	HaiType_pin_1,
	HaiType_pin_2,
	HaiType_pin_3,
	HaiType_pin_4,
	HaiType_pin_5,
	HaiType_pin_6,
	HaiType_pin_7,
	HaiType_pin_8,
	HaiType_pin_9,
	HaiType_sou_1,
	HaiType_sou_2,
	HaiType_sou_3,
	HaiType_sou_4,
	HaiType_sou_5,
	HaiType_sou_6,
	HaiType_sou_7,
	HaiType_sou_8,
	HaiType_sou_9,
	HaiType_ton,
	HaiType_nan,
	HaiType_sha,
	HaiType_pee,
	HaiType_haku,
	HaiType_hatsu,
	HaiType_chun,
	HaiType_MAX
};

enum HaiColor
{
	HaiColor_none,
	HaiColor_manzu,
	HaiColor_pinzu,
	HaiColor_souzu,
	HaiColor_jihai,
	HaiColor_MAX
};

enum SuuHai
{
	SuuHai_none,
	SuuHai_1,
	SuuHai_2,
	SuuHai_3,
	SuuHai_4,
	SuuHai_5,
	SuuHai_6,
	SuuHai_7,
	SuuHai_8,
	SuuHai_9,
	SuuHai_MAX
};

enum Jihai
{
	Jihai_ton,
	Jihai_nan,
	Jihai_sha,
	Jihai_pee,
	Jihai_haku,
	Jihai_hatsu,
	Jihai_chun,
	Jihai_MAX
};

class Hai{
public:
	static HaiType GetHaiType(int haiNumber);
	static HaiColor GetHaiColor(HaiType haiType);
	static int GetHaiNum(HaiType haiType);
	static int GetHaiNumber(HaiType haiType);
	static int GetHaiMin();
	static int GetHaiMax();
};

#endif //_MAHJONG_HAI_HEADER_2015_0212_
