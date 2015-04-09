#ifndef _MAHJONG_KAZE_HEADER_2015_0220_
#define _MAHJONG_KAZE_HEADER_2015_0220_

enum E_kaze
{
	E_kaze_Ton,
	E_kaze_Nan,
	E_kaze_Sha,
	E_kaze_Pee,
	E_kaze_MAX
};

enum E_bakaze
{
	E_bakaze_Ton_1,
	E_bakaze_Ton_2,
	E_bakaze_Ton_3,
	E_bakaze_Ton_4,
	E_bakaze_Nan_1,
	E_bakaze_Nan_2,
	E_bakaze_Nan_3,
	E_bakaze_Nan_4,
	E_bakaze_MAX
};

class Kaze
{
public:
	static E_kaze GetKaze(int kaze);
	static int GetKazeNumber(E_kaze kaze);
	static E_kaze GetNextKaze(E_kaze kaze);
	static int GetKazeMax();
	static E_bakaze GetBakaze(int bakazeNumber);
	static int GetBakazeNumber(E_bakaze bakaze);
	static E_bakaze GetNextBakaze(E_bakaze bakaze);
	static int GetBakazeMax();
};

#endif //_MAHJONG_KAZE_HEADER_2015_0220_
