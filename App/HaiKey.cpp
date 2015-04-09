#include "HaiKey.h"

static const E_haiKey placeTBL[]
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

E_haiKey HaiKey::GetHaiKey(int haiKeyNumber)
{
	return placeTBL[haiKeyNumber];
}

int HaiKey::GetHaiKeyNumber(E_haiKey haiKey)
{
	return haiKey;
}
