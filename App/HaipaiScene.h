#ifndef _MAHJONG_HAIPAI_SCENE_HEADER_2015_0212_
#define _MAHJONG_HAIPAI_SCENE_HEADER_2015_0212_

#include "GameScene.h"
#include "Kaze.h"

class HaipaiScene :
	public GameScene
{
public:
	HaipaiScene();
	virtual ~HaipaiScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_kaze GetKazeOya();
	E_sceneType GetSceneType();
private:
	int m_frame;
};

#endif //_MAHJONG_HAIPAI_SCENE_HEADER_2015_0212_
