#include "AgariResultScene.h"
#include "../BillboardString.h"
#include "TsumoScene.h"

#include<iostream>


static const E_sceneType SCENE_TYPE = E_sceneType_AgariResult;

AgariResultScene::AgariResultScene() : GameScene()
, m_frame(0)
{
}

AgariResultScene::~AgariResultScene()  throw()
{
}

void AgariResultScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
//	if (m_frame >= 8)
//	{
//		m_isNextScene = true;
//	}
//	std::cout << "上がり結果フレーム：" << m_frame << std::endl;
//	m_frame++;
//	
//	if (IsFirst())
//	{
//		(*pOwnerPlayer)->MyTurn(true);
//	}
}

GameScene* AgariResultScene::ChangeGameScene()
{
	GameScene* pGameScene = new TsumoScene();
	return pGameScene;
}

E_sceneType AgariResultScene::GetSceneType()
{
	return SCENE_TYPE;
}

