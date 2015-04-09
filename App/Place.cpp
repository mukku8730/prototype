#include "Place.h"

static const E_place placeTBL[]
{
	E_place_1,
	E_place_2,
	E_place_3,
	E_place_4,
	E_place_MAX
};

E_place Place::GetPlace(int placeNumber)
{
	return placeTBL[placeNumber];
}

int Place::GetPlaceNumber(E_place place)
{
	return place;
}

E_place Place::GetNextPlace(E_place place)
{
	if (GetPlace(GetPlaceNumber(place) + 1) == E_place_MAX)
	{
		return E_place_1;
	}
	return  GetPlace(GetPlaceNumber(place) + 1);
}

E_place Place::GetPrevPlace(E_place place)
{
	if (GetPlace(GetPlaceNumber(place)) == E_place_1)
	{
		return E_place_4;
	}
	return  GetPlace(GetPlaceNumber(place) - 1);
}

int Place::GetPlaceMax()
{
	return E_place_MAX;
}
