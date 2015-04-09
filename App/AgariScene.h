#ifndef _MAHJONG_AGARI_SCENE_HEADER_2015_0212_
#define _MAHJONG_AGARI_SCENE_HEADER_2015_0212_

#include "GameScene.h"
class AgariScene :
	public GameScene
{
public:
	AgariScene();
	virtual ~AgariScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_AGARI_SCENE_HEADER_2015_0212_

