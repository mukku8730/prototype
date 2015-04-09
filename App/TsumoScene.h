#ifndef _MAHJONG_TSUMO_SCENE_HEADER_2015_0212_
#define _MAHJONG_TSUMO_SCENE_HEADER_2015_0212_

#include "GameScene.h"
class TsumoScene :
	public GameScene
{
public:
	TsumoScene();
	virtual ~TsumoScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_TSUMO_SCENE_HEADER_2015_0212_

