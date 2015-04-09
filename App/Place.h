#ifndef _MAHJONG_PLACE_HEADER_2015_0212_
#define _MAHJONG_PLACE_HEADER_2015_0212_

enum E_place
{
	E_place_1,
	E_place_2,
	E_place_3,
	E_place_4,
	E_place_MAX
};

class Place
{
public:
	static E_place GetPlace(int placeNumber);
	static int GetPlaceNumber(E_place place);
	static E_place GetNextPlace(E_place place);
	static E_place GetPrevPlace(E_place place);
	static int GetPlaceMax();
};

#endif //_MAHJONG_PLACE_HEADER_2015_0212_
