#ifndef _MAHJONG_DECIDE_OYA_SCENE_HEADER_2015_0212_
#define _MAHJONG_DECIDE_OYA_SCENE_HEADER_2015_0212_

#include "GameScene.h"

class DecideOyaScene : public GameScene
{
public:
	DecideOyaScene();
	virtual ~DecideOyaScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_DECIDE_OYA_SCENE_HEADER_2015_0212_

