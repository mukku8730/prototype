#include "Kaze.h"

static const E_kaze kazeTBL[]
{
	E_kaze_Ton,
	E_kaze_Nan,
	E_kaze_Sha,
	E_kaze_Pee,
	E_kaze_MAX

};

struct bakazeStruct
{
	E_bakaze bakaze;
	E_kaze kaze;
	int number;
};

static const bakazeStruct bakazeTBL[]
{
	{ E_bakaze_Ton_1, E_kaze_Ton, 0},
	{ E_bakaze_Ton_2, E_kaze_Ton, 1},
	{ E_bakaze_Ton_3, E_kaze_Ton, 2},
	{ E_bakaze_Ton_4, E_kaze_Ton, 3},
	{ E_bakaze_Nan_1, E_kaze_Nan, 4},
	{ E_bakaze_Nan_2, E_kaze_Nan, 5},
	{ E_bakaze_Nan_3, E_kaze_Nan, 6},
	{ E_bakaze_Nan_4, E_kaze_Nan, 7},
};

E_kaze Kaze::GetKaze(int kazeNumber)
{
	return kazeTBL[kazeNumber];
}

int Kaze::GetKazeNumber(E_kaze kaze)
{
	return kaze;
}

E_kaze Kaze::GetNextKaze(E_kaze kaze)
{
	if (GetKaze(GetKazeNumber(kaze) + 1) == E_kaze_MAX)
	{
		return E_kaze_Ton;
	}
	return  GetKaze(GetKazeNumber(kaze) + 1);
}

int Kaze::GetKazeMax()
{
	return E_kaze_MAX;
}

static E_bakaze GetBakaze(int bakazeNumber)
{
	return bakazeTBL[bakazeNumber].bakaze;
}

static int GetBakazeNumber(E_bakaze bakaze)
{
	return bakazeTBL[bakaze].bakaze;
}

static E_bakaze GetNextBakaze(E_bakaze bakaze)
{
	if (GetBakaze(GetBakazeNumber(bakaze)) == E_bakaze_MAX)
	{
		return E_bakaze_MAX;
	}
	return  GetBakaze(GetBakazeNumber(bakaze) + 1);
}

static int GetBakazeMax()
{
	return E_bakaze_MAX;
}
