#ifndef _MAHJONG_TABLE_PLACE_HEADER_2015_0212_
#define _MAHJONG_TABLE_PLACE_HEADER_2015_0212_

#include "Place.h"
#include "Hai.h"
#include "FuuroHai.h"
#include <vector>
#include <memory>
#include <set>
class TablePlace
{
public:
	TablePlace(E_place place);
	virtual ~TablePlace() throw();
	void AddTehai(HaiType hai);
	void AddSutehai(HaiType hai);
	void AddFuurohai(FuuroHai* pFuuroHaiPtr);
	void AddTsumohai(HaiType hai);
	void ResumeTehai(int haiIndex);
	void ResumeSutehai(int haiIndex);
	void ResumeLastSutehai();
	void ResumeFuurohai(int haiIndex);
	void ResumeTsumohai();
	void ClearTehai();
	void ClearSutehai();
	void ClearFuurohai();
	void ClearTsumohai();
	std::multiset<HaiType> GetTehai() const;
	HaiType GetTehaiMenber(int haiIndex) const;
	std::vector<HaiType> GetSutehai() const;
	HaiType GetLastSutehai();
	std::vector<std::shared_ptr<FuuroHai>> GetFuurohais() const;
	HaiType GetTsumohai() const;
	int GetPoints();
	void SetPoints(int points);

private:
	E_place m_place;
	std::multiset<HaiType> m_tehai;
	std::vector<HaiType> m_sutehai;
	std::vector<std::shared_ptr<FuuroHai>> m_fuurohaiPtrs;
	HaiType m_tsumohai;
	int m_points;
};

#endif //_MAHJONG_TABLE_PLACE_HEADER_2015_0212_
