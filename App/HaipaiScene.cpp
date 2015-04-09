#include "HaipaiScene.h"

#include "AgariResultScene.h"

#include "TsumoScene.h"
#include <iostream>
#include <windows.h>

static const E_sceneType SCENE_TYPE = E_sceneType_Haipai;
static const int TEHAI_MAX = 13;

HaipaiScene::HaipaiScene() : GameScene()
, m_frame(0)
{
}

HaipaiScene::~HaipaiScene()  throw()
{
}

void HaipaiScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (IsFirst())
	{
		pMahjongTable->StartGame();
	}
	std::shared_ptr<TablePlace> tablePlacePtr = pMahjongTable->GetTablePlace((*pOwnerPlayer)->GetPlace());
	std::multiset<HaiType> tehai = tablePlacePtr->GetTehai();
	if (tehai.size() < TEHAI_MAX)
	{
		pMahjongTable->SetHaipai((*pOwnerPlayer)->GetPlace());
		for (std::vector<std::shared_ptr<Player>>::iterator it = pSharedPlayers->begin(); it != pSharedPlayers->end(); it++)
		{
			if (Place::GetNextPlace((*it)->GetPlace()) == (*pOwnerPlayer)->GetPlace())
			{
				std::shared_ptr<TablePlace> nextTablePlacePtr = pMahjongTable->GetTablePlace((*pOwnerPlayer)->GetPlace());
				std::multiset<HaiType> nextTehai = nextTablePlacePtr->GetTehai();
				if (nextTehai.size() < TEHAI_MAX)
				{
					(*pOwnerPlayer) = (*it);
				}
				break;
			}
		}
	}
	else
	{
		int a = pMahjongTable->GetHaiCount();
		m_isNextScene = true;

	}
	Sleep(200);
}

GameScene* HaipaiScene::ChangeGameScene()
{
	GameScene* pGameScene = new TsumoScene();
	return pGameScene;
}

E_sceneType HaipaiScene::GetSceneType()
{
	return SCENE_TYPE;
}
