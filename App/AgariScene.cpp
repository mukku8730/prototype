#include "AgariScene.h"

#include "AgariResultScene.h"
#include <iostream>

static const E_sceneType SCENE_TYPE = E_sceneType_Agari;

AgariScene::AgariScene() : GameScene()
, m_frame(0)
{
}

AgariScene::~AgariScene()  throw()
{
}

void AgariScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (IsFirst())
	{
		(*pOwnerPlayer)->MyTurn(true);
	}
	if (m_frame >= 2)
	{
		m_isNextScene = true;
	}
	m_frame++;
}

GameScene* AgariScene::ChangeGameScene()
{
	GameScene* pGameScene = new AgariResultScene();
	return pGameScene;
}

E_sceneType AgariScene::GetSceneType()
{
	return SCENE_TYPE;
}
