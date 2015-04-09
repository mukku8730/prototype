#ifndef _MAHJONG_MAHJONG_SCREEN_HEADER_2015_0212_
#define _MAHJONG_MAHJONG_SCREEN_HEADER_2015_0212_

#include "Screen.h"
#include "../Vector3.h"
#include"CResultScreen.h"
#include <memory>
#include <d3dx9.h>
#include <dinput.h>

/// 前方宣言
class SimulateMahjong;
class BillboardString;
class Camera;
class Light;
class Table;
class Field;
class Character;
class TenbouManager;
class Background;
class JanpaiManager;
class PointManager;
class SceneType;


/// ゲームスクリーン
class MahjongScreen : public Screen
{
private:
	std::unique_ptr<SimulateMahjong> m_simulateMahjongPtr;
	std::unique_ptr<BillboardString> m_billboardStrPtr;
	std::unique_ptr<Camera> m_cameraPtr;
	std::unique_ptr<Light> m_lightPtr;
	std::unique_ptr<Table> m_tablePtr;
	std::unique_ptr<Field> m_fieldPtr;
	std::unique_ptr<Character> m_charaPtr;
	std::unique_ptr<TenbouManager> m_tenbouManagerPtr;
	std::unique_ptr<Background> m_bgPtr;
	std::unique_ptr<JanpaiManager> m_janpaiManagerPtr;
	std::unique_ptr<PointManager> m_pointManagerPtr;
	std::unique_ptr<SceneType> m_sceneType;
	Vector3 m_eyePoint;
	Vector3 m_lookAtPoint;
	SHORT m_pKeyState;
	CResuitScreen *m_resultScreen;

public:
	MahjongScreen();
	virtual ~MahjongScreen() throw();
	void Update();
	void Draw();
	Screen* ChangeScreen();
};

#endif //_MAHJONG_MAHJONG_SCREEN_HEADER_2015_0212_
