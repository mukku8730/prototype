#ifndef _MAHJONG_DISCARD_SCENE_HEADER_2015_0212_
#define _MAHJONG_DISCARD_SCENE_HEADER_2015_0212_

#include "GameScene.h"
class DiscardScene :
	public GameScene
{
public:
	DiscardScene();
	virtual ~DiscardScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_DISCARD_SCENE_HEADER_2015_0212_

