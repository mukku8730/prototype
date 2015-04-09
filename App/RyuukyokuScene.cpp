#include "RyuukyokuScene.h"

#include "HaipaiScene.h"
#include <iostream>
#include <algorithm>
#include <random>

static const E_sceneType SCENE_TYPE = E_sceneType_Ryuukyoku;

RyuukyokuScene::RyuukyokuScene() : GameScene()
, m_frame(0)
{
}

RyuukyokuScene::~RyuukyokuScene()  throw()
{
}

void RyuukyokuScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (m_frame >= 10)
	{
		m_isNextScene = true;
	}
	m_frame++;
}

GameScene* RyuukyokuScene::ChangeGameScene()
{
	GameScene* pGameScene = new HaipaiScene();
	return pGameScene;
}

E_sceneType RyuukyokuScene::GetSceneType()
{
	return SCENE_TYPE;
}
