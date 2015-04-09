#ifndef _MAHJONG_MAHJONG_TABLE_HEADER_2015_0212_
#define _MAHJONG_MAHJONG_TABLE_HEADER_2015_0212_

#include "Hai.h"
#include "Place.h"
#include "TablePlace.h"
#include <memory>

class MahjongTable
{
public:
	MahjongTable();
	virtual ~MahjongTable() throw();
	void Init();
	void HaiMix();
	void InitHais();
	void StartGame();
	void Tsumo(E_place place);
	void Discard(E_place place);
	void Discard(E_place place, int haiIndex);
	void Chii(E_place place, int haiIndex_1, int haiIndex_2);
	void Pon(E_place place, RelativePlace relativePlace, HaiType haiType);
	void Kan(E_place place, RelativePlace relativePlace, HaiType haiType);
	std::vector<std::shared_ptr<TablePlace>> GetTablePlacePtrs() const;
	std::vector<HaiType> GetWanpai() const;
	std::vector<HaiType> GetDora() const;
	int GetHaiCount() const;
	std::shared_ptr<TablePlace> GetTablePlace(E_place place) const;
	E_place GetStartPlace() const;
	int GetTehaiMax(E_place place);
	void SetHaipai(E_place place);
private:
	void SetWanpai();
	void AddDora();
	std::vector<std::shared_ptr<TablePlace>> m_tablePlacePtrs;
	std::vector<HaiType> m_yamaHais;
	std::vector<HaiType> m_wanpai;
	std::vector<HaiType> m_dora;
	E_place m_startPlace;
};

#endif //_MAHJONG_MAHJONG_TABLE_HEADER_2015_0212_
