#include "FuuroScene.h"
#include "SelectHaiScene.h"
#include "TsumoScene.h"

static const E_sceneType SCENE_TYPE = E_sceneType_Fuuro;

FuuroScene::FuuroScene() : GameScene()
, m_frame(0)
{
}

FuuroScene::~FuuroScene()  throw()
{
}

void FuuroScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
	if (m_frame >= 10)
	{
		m_isNextScene = true;
	}
	m_frame++;
	switch ((*pOwnerPlayer)->GetPopupMenuKey())
	{
	case E_popupMenuKey_none:
		break;
	case E_popupMenuKey_Chii:
		break;
	case E_popupMenuKey_Pon:
		break;
	case E_popupMenuKey_Kan:
		break;
	case E_popupMenuKey_Ron:
		break;
	case E_popupMenuKey_Tsumo:
		break;
	case E_popupMenuKey_Cancel:
		break;
	default:
		break;
	}
	if (IsFirst())
	{
		(*pOwnerPlayer)->MyTurn(true);
	}
}

GameScene* FuuroScene::ChangeGameScene()
{
//	GameScene* pGameScene = new SelectHaiScene();
	GameScene* pGameScene = new TsumoScene();
	return pGameScene;
}

E_sceneType FuuroScene::GetSceneType()
{
	return SCENE_TYPE;
}
