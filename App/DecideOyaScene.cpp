#include "DecideOyaScene.h"

#include "HaipaiScene.h"
#include <iostream>
#include <algorithm>
#include <random>

static const E_sceneType SCENE_TYPE = E_sceneType_DecideOya;

DecideOyaScene::DecideOyaScene() : GameScene()
, m_frame(0)
{
}

DecideOyaScene::~DecideOyaScene()  throw()
{
}

void DecideOyaScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (m_frame >= 10)
	{
		m_isNextScene = true;
	}
	m_frame++;
	
	if (IsFirst())
	{
		pMahjongTable->Init();
		for (SharedPlayers::iterator it = pSharedPlayers->begin(); it != pSharedPlayers->end(); it++)
		{
			if ((*it)->GetPlace() == pMahjongTable->GetStartPlace())
			{
				(*pOwnerPlayer) = (*it);
				break;
			}
		}
	}
}

GameScene* DecideOyaScene::ChangeGameScene()
{
	GameScene* pGameScene = new HaipaiScene();
	return pGameScene;
}

E_sceneType DecideOyaScene::GetSceneType()
{
	return SCENE_TYPE;
}
