#ifndef _MAHJONG_HAI_KEY_HEADER_2015_0216_
#define _MAHJONG_HAI_KEY_HEADER_2015_0216_

enum E_haiKey
{
	E_haiKey_none,
	E_haiKey_Tehai_1,
	E_haiKey_Tehai_2,
	E_haiKey_Tehai_3,
	E_haiKey_Tehai_4,
	E_haiKey_Tehai_5,
	E_haiKey_Tehai_6,
	E_haiKey_Tehai_7,
	E_haiKey_Tehai_8,
	E_haiKey_Tehai_9,
	E_haiKey_Tehai_10,
	E_haiKey_Tehai_11,
	E_haiKey_Tehai_12,
	E_haiKey_Tehai_13,
	E_haiKey_Tsumohai,
	E_haiKey_MAX
};

class HaiKey
{
public:
	static E_haiKey GetHaiKey(int haiKeyNumber);
	static int GetHaiKeyNumber(E_haiKey haiKey);
};

#endif //_MAHJONG_HAI_KEY_HEADER_2015_0216_
