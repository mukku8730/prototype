#include "TsumoScene.h"

#include "SelectHaiScene.h"
#include <iostream>

static const E_sceneType SCENE_TYPE = E_sceneType_Tsumo;

TsumoScene::TsumoScene() : GameScene()
, m_frame(0)
{
}

TsumoScene::~TsumoScene()  throw()
{
}

void TsumoScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (IsFirst())
	{
		if ((pMahjongTable->GetHaiCount() > 0))
		{
			for (SharedPlayers::iterator it = pSharedPlayers->begin(); it != pSharedPlayers->end(); it++)
			{
				if ((*it)->GetPlace() == Place::GetNextPlace((*pOwnerPlayer)->GetPlace()))
				{
					(*pOwnerPlayer) = (*it);
					break;
				}
			}
			(*pOwnerPlayer)->MyTurn(true);
		}
	}
	if (m_frame >= 6)
	{
		m_isNextScene = true;
	}
	m_frame++;
}

GameScene* TsumoScene::ChangeGameScene()
{
	GameScene* pGameScene = new SelectHaiScene();
	return pGameScene;
}

E_sceneType TsumoScene::GetSceneType()
{
	return SCENE_TYPE;
}
