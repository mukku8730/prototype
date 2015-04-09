#include "DiscardScene.h"

#include "PopUpMenuScene.h"
#include <iostream>

static const E_sceneType SCENE_TYPE = E_sceneType_Discard;

DiscardScene::DiscardScene() : GameScene()
, m_frame(0)
{
}

DiscardScene::~DiscardScene()  throw()
{
}

void DiscardScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (m_frame >= 6)
	{
		m_isNextScene = true;
	}
	std::cout << "ŽÌ‚Ä”vƒtƒŒ[ƒ€F" << m_frame << std::endl;
	m_frame++;
	
	if (IsFirst())
	{
		(*pOwnerPlayer)->MyTurn(true);
	}
}

GameScene* DiscardScene::ChangeGameScene()
{
	GameScene* pGameScene = new PopUpMenuScene();
	return pGameScene;
}

E_sceneType DiscardScene::GetSceneType()
{
	return SCENE_TYPE;
}
