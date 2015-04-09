#pragma once
#include "app/Hai.h"
#include "app/FuuroHai.h"
#include <vector>
#include <set>
#include <memory>

class Janpai;
class BillboardString;


/// –ƒ”v¶YHêŒ“ŠÇ—ƒNƒ‰ƒX
class JanpaiManager
{
private:
	static const int m_mahjongTilesNum;
	Janpai* m_janpai;
	enum DirectionType {
		DirectionType_South,
		DirectionType_East,
		DirectionType_North,
		DirectionType_West,

		DirectionType_Max,
	};


public:
	JanpaiManager();
	~JanpaiManager();

	// XVˆ—
	void Update();

	// è”v‚ğ•`‰æ
	void DrawTehai(std::vector<std::multiset<HaiType>> tehai);

	// Ì”v‚ğ•`‰æ
	void DrawSuteHai(std::vector<std::vector<HaiType>> fuuroHai);

	// •›˜I”v‚ğ•`‰æ
	void DrawFuuroHai(std::vector<std::vector<std::shared_ptr<FuuroHai>>> fuuroHai);

	// ƒcƒ‚”v‚ğ•`‰æ
	void DrawTsumoHai(const std::vector<HaiType>& tsumoHai);

	//”v‚ÌR‚ğ•`‰æ
	void DrawMountainHai(int maxHaiCount, int doraSize);

	//‰¤”v‚ÌR‚ğ•`‰æ
	void DrawDeadWall(std::vector<HaiType> doras);

};
