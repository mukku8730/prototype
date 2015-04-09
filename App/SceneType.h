#ifndef _MAHJONG_SCENE_TYPE_HEADER_2015_0212_
#define _MAHJONG_SCENE_TYPE_HEADER_2015_0212_

enum E_sceneType
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

class SceneType
{
public:
	static E_sceneType GetSceneType(int sceneNumber);
	static int GetSceneTypeNumber(E_sceneType place);
};

#endif //_MAHJONG_SCENE_TYPE_HEADER_2015_0212_
