#include "SceneType.h"

static const E_sceneType sceneTypeTBL[]
{
	E_sceneType_None,
	E_sceneType_AgariResult,
	E_sceneType_Agari,
	E_sceneType_DecideOya,
	E_sceneType_Discard,
	E_sceneType_Fuuro,
	E_sceneType_Haipai,
	E_sceneType_PopUpMenu,
	E_sceneType_Ryuukyoku,
	E_sceneType_SelectHai,
	E_sceneType_SelectFuuroHai,
	E_sceneType_Tsumo,
	E_sceneType_MAX
};

E_sceneType SceneType::GetSceneType(int sceneTypeNumber)
{
	return sceneTypeTBL[sceneTypeNumber];
}

int SceneType::GetSceneTypeNumber(E_sceneType sceneType)
{
	return sceneType;
}
