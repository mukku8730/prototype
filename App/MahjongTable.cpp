#include "MahjongTable.h"

#include "Kaze.h"
#include "Place.h"
#include "ChiiHai.h"
#include "PonHai.h"
#include "KanHai.h"
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>

#define CHII_HAI_MAX (3)

static const int INIT_POINTS = 25000;
static const int INIT_HAI_NUMBER = 8;
static const int HAI_SOURCE_NUMBER_MAX = 4;
static const int WANPAI_MAX = 13;
static const int TEHAI_MAX = 13;
static const int PON_HAI_MAX = 3;
static const int KAN_HAI_MAX = 4;
static const int HAIPAI_NUMBERS = 4;

MahjongTable::MahjongTable()
	: m_tablePlacePtrs()
	, m_yamaHais()
	, m_wanpai()
	, m_dora()
	, m_startPlace()
{
	for (int i = 0; i < Place::GetPlaceMax(); i++)
	{
		m_tablePlacePtrs.push_back(std::shared_ptr<TablePlace>(new TablePlace(Place::GetPlace(i))));
		assert(m_tablePlacePtrs.back());
	}
}

MahjongTable::~MahjongTable() throw()
{
}

void MahjongTable::Init()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> placeRd(0, (Place::GetPlaceMax() - 1));
	m_startPlace = Place::GetPlace(placeRd(mt));
	for (std::vector < std::shared_ptr <TablePlace>> ::iterator it = m_tablePlacePtrs.begin(); it != m_tablePlacePtrs.end(); it++)
	{
		(*it)->SetPoints(INIT_POINTS);
	}

}

void MahjongTable::HaiMix()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(m_yamaHais.begin(), m_yamaHais.end(), mt);
}

void MahjongTable::InitHais()
{
	m_dora.clear();
	m_wanpai.clear();
	m_yamaHais.clear();
	for (std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin(); it != m_tablePlacePtrs.end(); it++)
	{
		(*it)->ClearFuurohai();
		(*it)->ClearSutehai();
		(*it)->ClearTehai();
		(*it)->ClearTsumohai();
	}
	for (int i = 0; i < HAI_SOURCE_NUMBER_MAX; i++)
	{
		for (int j = Hai::GetHaiMin(); j < Hai::GetHaiMax(); j++)
		{
			m_yamaHais.push_back(Hai::GetHaiType(j));
		}
	}
	HaiMix();
}

void MahjongTable::StartGame()
{
	InitHais();
	AddDora();
	SetWanpai();
//	for (int i = 0; i < INIT_HAI_NUMBER; i++){
//		for (int j = 0; j < Place::GetPlaceMax(); j++)
//		{
//			Tsumo(Place::GetPlace(j));
//			Discard(Place::GetPlace(j));
//		}
//	}
//	Chii(E_place_1, 0, 1);
//	Chii(E_place_2, 0, 1);
//	Chii(E_place_3, 0, 1);
//	Chii(E_place_4, 0, 1);
//	Pon(E_place_1, RelativePlace_Front, HaiType_man_1);
//	Pon(E_place_2, RelativePlace_Front, HaiType_man_1);
//	Pon(E_place_3, RelativePlace_Front, HaiType_man_1);
//	Pon(E_place_4, RelativePlace_Front, HaiType_man_1);
//	Kan(E_place_1, RelativePlace_Right, HaiType_man_1);
//	Kan(E_place_2, RelativePlace_Right, HaiType_man_1);
//	Kan(E_place_3, RelativePlace_Right, HaiType_man_1);
//	Kan(E_place_4, RelativePlace_Right, HaiType_man_1);
}

void MahjongTable::SetWanpai()
{
	for (int i = 0; i < WANPAI_MAX; i++)
	{
		m_wanpai.push_back(m_yamaHais.back());
		m_yamaHais.pop_back();
	}
}

void MahjongTable::AddDora()
{
	m_dora.push_back(m_yamaHais.back());
	m_yamaHais.pop_back();
}

void MahjongTable::SetHaipai(E_place place)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + place;
	std::multiset<HaiType> tehai = (*it)->GetTehai();
	if ((tehai.size() + HAIPAI_NUMBERS) < TEHAI_MAX)
	{
		for (int j = 0; j < HAIPAI_NUMBERS; j++)
		{
			(*it)->AddTehai(m_yamaHais.back());
			m_yamaHais.pop_back();
		}
	}
	else
	{
		(*it)->AddTehai(m_yamaHais.back());
		m_yamaHais.pop_back();
	}
}

void MahjongTable::Tsumo(E_place place)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	(*it)->AddTsumohai(m_yamaHais.back());
	m_yamaHais.pop_back();
}

void MahjongTable::Chii(E_place place, int haiIndex_1, int haiIndex_2)
{
	if (haiIndex_1 == haiIndex_2)
	{
		assert(false);
	}

	if (haiIndex_1 > haiIndex_2)
	{
		int wk = haiIndex_1;
		haiIndex_1 = haiIndex_2;
		haiIndex_2 = wk;
	}

	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	std::vector<std::shared_ptr<TablePlace>>::iterator prevIt = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(Place::GetPrevPlace(place));
	HaiType hai[3] = { HaiType_none, HaiType_none, HaiType_none };
	if ((*it)->GetTehaiMenber(haiIndex_2))
	{
		hai[2] = (*it)->GetTehaiMenber(haiIndex_2);
		(*it)->ResumeTehai(haiIndex_2);
	}
	if ((*it)->GetTehaiMenber(haiIndex_1))
	{
		hai[1] = (*it)->GetTehaiMenber(haiIndex_1);
		(*it)->ResumeTehai(haiIndex_1);
	}
	if ((*prevIt)->GetLastSutehai())
	{
		hai[0] = (*prevIt)->GetLastSutehai();
		(*prevIt)->ResumeLastSutehai();
	}
	for (int i = 0; i < CHII_HAI_MAX; i++)
	{
		assert(hai[i]);
	}
	(*it)->AddFuurohai(new ChiiHai(hai[0], hai[1], hai[2]));
}

void MahjongTable::Pon(E_place place, RelativePlace relativePlace, HaiType haiType)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator tpIt = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	std::vector<int> haiIndexs;
	std::multiset<HaiType> tehai = (*tpIt)->GetTehai();
	int haiCnt = 0;
	for (std::multiset<HaiType>::iterator tehaiIt = tehai.begin(); tehaiIt != tehai.end(); tehaiIt++)
	{
		if ((*tehaiIt) == haiType)
		{
			haiIndexs.push_back(haiCnt);
		}
		haiCnt++;
	}
	if (haiIndexs.size() >= PON_HAI_MAX)
	{
		int indexCnt = 0;
		for (std::vector<int>::reverse_iterator rIt = haiIndexs.rbegin(); rIt != haiIndexs.rend(); rIt++)
		{
			if (indexCnt < PON_HAI_MAX)
			{
				(*tpIt)->ResumeTehai((*rIt));
			}
			indexCnt++;
		}
		(*tpIt)->AddFuurohai(new PonHai(haiType, relativePlace));
	}

}

void MahjongTable::Kan(E_place place, RelativePlace relativePlace, HaiType haiType)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator tpIt = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	std::vector<int> haiIndexs;
	std::multiset<HaiType> tehai = (*tpIt)->GetTehai();
	int haiCnt = 0;
	for (std::multiset<HaiType>::iterator tehaiIt = tehai.begin(); tehaiIt != tehai.end(); tehaiIt++)
	{
		if ((*tehaiIt) == haiType)
		{
			haiIndexs.push_back(haiCnt);
		}
		haiCnt++;
	}
	if (haiIndexs.size() >= KAN_HAI_MAX)
	{
		int indexCnt = 0;
		for (std::vector<int>::reverse_iterator rIndexIt = haiIndexs.rbegin(); rIndexIt != haiIndexs.rend(); rIndexIt++)
		{
			if (indexCnt < KAN_HAI_MAX)
			{
				(*tpIt)->ResumeTehai((*rIndexIt));
			}
			indexCnt++;
		}
		(*tpIt)->AddFuurohai(new KanHai(haiType, relativePlace));
	}
}

void MahjongTable::Discard(E_place place)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	if ((*it)->GetTsumohai() != HaiType_none)
	{
		(*it)->AddSutehai((*it)->GetTsumohai());
		(*it)->ResumeTsumohai();
	}
}

void MahjongTable::Discard(E_place place, int haiIndex)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	if ((*it)->GetTsumohai() != HaiType_none)
	{
		(*it)->AddSutehai((*it)->GetTehaiMenber(haiIndex));
		(*it)->ResumeTehai(haiIndex);
		(*it)->AddTehai((*it)->GetTsumohai());
		(*it)->ResumeTsumohai();
	}
}

std::vector<std::shared_ptr<TablePlace>> MahjongTable::GetTablePlacePtrs() const
{
	return m_tablePlacePtrs;
}

std::vector<HaiType> MahjongTable::GetWanpai() const
{
	return m_wanpai;
}

std::vector<HaiType> MahjongTable::GetDora() const
{
	return m_dora;
}

int MahjongTable::GetHaiCount() const
{
	return m_yamaHais.size();
}

std::shared_ptr<TablePlace> MahjongTable::GetTablePlace(E_place place) const
{
	std::vector<std::shared_ptr < TablePlace >>::const_iterator it = (m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place));
	return (*it);
}

E_place MahjongTable::GetStartPlace() const
{
	return m_startPlace;
}

int MahjongTable::GetTehaiMax(E_place place)
{
	std::vector<std::shared_ptr<TablePlace>>::iterator it = m_tablePlacePtrs.begin() + Place::GetPlaceNumber(place);
	return ((*it)->GetTehai()).size();
}
