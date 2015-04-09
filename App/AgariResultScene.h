#ifndef _MAHJONG_AGARI_RESULT_SCENE_HEADER_2015_0212_
#define _MAHJONG_AGARI_RESULT_SCENE_HEADER_2015_0212_

#include "GameScene.h"


class AgariResultScene : public GameScene
{
public:
	AgariResultScene();
	virtual ~AgariResultScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);
	GameScene* ChangeGameScene();
	E_sceneType GetSceneType();
	void DrawRole(bool *RoleJudgment);
private:
	int m_frame;
};

#endif //_MAHJONG_AGARI_RESULT_SCENE_HEADER_2015_0212_

