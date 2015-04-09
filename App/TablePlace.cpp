#include "TablePlace.h"
#include <cassert>

TablePlace::TablePlace(E_place place)
	: m_place(place)
	, m_tehai()
	, m_sutehai()
	, m_fuurohaiPtrs()
	, m_tsumohai(HaiType_none)
	, m_points(0)
{
}

TablePlace::~TablePlace() throw()
{
}

void TablePlace::AddTehai(HaiType hai)
{
	m_tehai.insert(hai);
}

void  TablePlace::AddSutehai(HaiType hai)
{
	m_sutehai.push_back(hai);
}

void TablePlace::AddFuurohai(FuuroHai* pFuuroHai)
{
	m_fuurohaiPtrs.push_back(std::shared_ptr<FuuroHai>(pFuuroHai));
	assert(m_fuurohaiPtrs.back());
}

void TablePlace::AddTsumohai(HaiType hai)
{
	if (m_tsumohai == HaiType_none){
		m_tsumohai = hai;
	}
}

void TablePlace::ResumeTehai(int haiIndex)
{
	std::multiset<HaiType>::iterator it = m_tehai.begin();
	for (int i = 0; i < haiIndex; i++)
	{
		it++;
	}
	m_tehai.erase(it);
}

void TablePlace::ResumeSutehai(int haiIndex)
{
	m_sutehai.erase(m_sutehai.begin() + haiIndex);
}

void TablePlace::ResumeLastSutehai()
{
	if (m_sutehai.begin() == m_sutehai.end())
	{
		assert(true);
	}
	m_sutehai.erase(m_sutehai.end() - 1);
}

void TablePlace::ResumeFuurohai(int haiIndex)
{
	m_sutehai.erase(m_sutehai.begin() + haiIndex);
}

void TablePlace::ResumeTsumohai()
{
	m_tsumohai = HaiType_none;
}

std::multiset<HaiType> TablePlace::GetTehai() const
{
	return m_tehai;
}

HaiType TablePlace::GetTehaiMenber(int haiIndex) const
{
	std::multiset<HaiType>::iterator it = m_tehai.begin();
	for (int i = 0; i < haiIndex; i++){
		it++;
	}
	return (*it);
}

std::vector<HaiType> TablePlace::GetSutehai() const
{
	return m_sutehai;
}

HaiType TablePlace::GetLastSutehai()
{
	std::vector<HaiType>::iterator it = m_sutehai.begin();
	if (it != m_sutehai.end()){
		it = m_sutehai.end() - 1;
	}
	else
	{
		assert(true);
	}
	return (*it);
}

std::vector<std::shared_ptr<FuuroHai>> TablePlace::GetFuurohais() const
{
	return m_fuurohaiPtrs;
}

HaiType TablePlace::GetTsumohai() const
{
	return m_tsumohai;
}

void TablePlace::ClearTehai()
{
	m_tehai.clear();
}

void TablePlace::ClearSutehai()
{
	m_sutehai.clear();
}

void TablePlace::ClearFuurohai()
{
	m_fuurohaiPtrs.clear();
}

void TablePlace::ClearTsumohai()
{
	m_tsumohai = HaiType_none;
}

int TablePlace::GetPoints()
{
	return m_points;
}

void TablePlace::SetPoints(int points)
{
	m_points = points;
}
