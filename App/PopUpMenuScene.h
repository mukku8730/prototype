#ifndef _MAHJONG_POP_UP_MENU_SCENE_HEADER_2015_0212_
#define _MAHJONG_POP_UP_MENU_SCENE_HEADER_2015_0212_

#include "GameScene.h"

class PopUpMenuScene :
	public GameScene
{
public:
	PopUpMenuScene();
	virtual ~PopUpMenuScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
private:
	int m_frame;

};

#endif //_MAHJONG_POP_UP_MENU_SCENE_HEADER_2015_0212_

