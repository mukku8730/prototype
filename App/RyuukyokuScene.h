#ifndef _MAHJONG_RYUUKYOKU_SCENE_HEADER_2015_0212_
#define _MAHJONG_RYUUKYOKU_SCENE_HEADER_2015_0212_

#include "GameScene.h"

class RyuukyokuScene:
	public GameScene
{
public:
	RyuukyokuScene();
	virtual ~RyuukyokuScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_RYUUKYOKU_SCENE_HEADER_2015_0212_

