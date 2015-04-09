#include "SelectFuuroHaiScene.h"

#include "FuuroScene.h"
#include <iostream>

static const E_sceneType SCENE_TYPE = E_sceneType_SelectFuuroHai;

SelectFuuroHaiScene::SelectFuuroHaiScene() : GameScene()
, m_frame(0)
{
}


SelectFuuroHaiScene::~SelectFuuroHaiScene()  throw()
{
}

void SelectFuuroHaiScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (m_frame >= 10)
	{
		m_isNextScene = true;
	}
//	if (IsFirst())
//	{
//		(*pOwnerPlayer)->MyTurn(true);
//	}
//	if ((*pOwnerPlayer)->HasSelected())
//	{
		NextScene(true);
//	}
}

GameScene* SelectFuuroHaiScene::ChangeGameScene()
{
	GameScene* pGameScene = new FuuroScene();
	return pGameScene;
}

E_sceneType SelectFuuroHaiScene::GetSceneType()
{
	return SCENE_TYPE;
}
