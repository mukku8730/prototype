#ifndef _MAHJONG_FUURO_SCENE_HEADER_2015_0212_
#define _MAHJONG_FUURO_SCENE_HEADER_2015_0212_

#include "GameScene.h"
class FuuroScene :
	public GameScene
{
public:
	FuuroScene();
	virtual ~FuuroScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_FUURO_SCENE_HEADER_2015_0212_

