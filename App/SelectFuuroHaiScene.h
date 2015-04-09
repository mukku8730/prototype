#ifndef _MAHJONG_SELECT_FUURO_HAI_SCENE_HEADER_2015_0226_
#define _MAHJONG_SELECT_FUURO_HAI_SCENE_HEADER_2015_0226_

#include "GameScene.h"
class SelectFuuroHaiScene :
	public GameScene
{
public:
	SelectFuuroHaiScene();
	virtual ~SelectFuuroHaiScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_SELECT_FUURO_HAI_SCENE_HEADER_2015_0226_
