#ifndef _MAHJONG_SIMULATE_MARJONG_HEADER_2015_0212_
#define _MAHJONG_SIMULATE_MARJONG_HEADER_2015_0212_

#include "MahjongTable.h"
#include "Player.h"
#include "SharedPlayers.h"
#include "GameScene.h"
#include "Kaze.h"
#include <vector>
#include <memory>

/// ëOï˚êÈåæ
class CursorKey;


class SimulateMahjong
{
public:
	SimulateMahjong();
	virtual ~SimulateMahjong() throw();
	void Update();
	bool IsNext() const;
	std::shared_ptr<MahjongTable> GetTableInfo() const;
private:
	void Init();
	std::shared_ptr<MahjongTable> m_mahjongTablePtr;
	std::shared_ptr<GameScene> m_gameScenePtr;
	std::unique_ptr<CursorKey> m_cursorKeyPtr;
	SharedPlayers m_playerPtrs;
	SharedPlayer m_ownerPlayer;
	bool m_isNext;
	bool m_isFirst;
	int m_frame;
};

#endif //_MAHJONG_SIMULATE_MARJONG_HEADER_2015_0212_
