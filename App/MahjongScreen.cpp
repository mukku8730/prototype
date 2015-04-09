#include "MahjongScreen.h"
#include "SimulateMahjong.h"
#include "../BillboardString.h"
#include "../DebugFont.h"
#include "../Camera.h"
#include "../Light.h"
#include "../Table.h"
#include "../Field.h"
#include "../Character.h"
#include "../TenbouManager.h"
#include "../Background.h"
#include "../JanpaiManager.h"
#include "../PointManager.h"
#include "../Textures.h"
#include "EndScreen.h"
#include "../Key.h"
#include "../KeyInput.h"
#include <tchar.h>
#include <iostream>
#include <cassert>
#include <windows.h>

//役成否テスト
static bool judg[46] = { false };
//

/**
	コンストラクタ
*/
MahjongScreen::MahjongScreen() : Screen()
, m_simulateMahjongPtr(new SimulateMahjong())
, m_billboardStrPtr(new BillboardString())
, m_cameraPtr(new Camera())
, m_lightPtr(new Light())
, m_tablePtr(new Table())
, m_fieldPtr(new Field())
, m_charaPtr(new Character())
, m_tenbouManagerPtr(new TenbouManager())
, m_bgPtr(new Background())
, m_janpaiManagerPtr(new JanpaiManager())
, m_pointManagerPtr(new PointManager())
, m_eyePoint(Vector3(0.0f, 20.0f, -50.0f))
, m_lookAtPoint(Vector3(0.0f, 0.0f, 0.0f))
, m_pKeyState(0)
, m_resultScreen(new CResuitScreen())
{
	assert(m_simulateMahjongPtr);
	assert(m_billboardStrPtr);
	assert(m_cameraPtr);
	assert(m_lightPtr);
	assert(m_tablePtr);
	assert(m_fieldPtr);
	assert(m_charaPtr);
	assert(m_tenbouManagerPtr);
	assert(m_bgPtr);
	assert(m_janpaiManagerPtr);
	assert(m_pointManagerPtr);
	Textures::GetInstance()->LoadTextures();
}


/**
	デストラクタ
*/
MahjongScreen::~MahjongScreen() throw() {
}


/**
	更新処理
*/
void MahjongScreen::Update()
{
	KeyInput* input = KeyInput::GetInstance();
	input->Update();

	if (input->GetKeys()[DIK_ESCAPE]->IsPushed()) {
		m_isNext = true;
	}

	if (input->GetKeys()[DIK_E]->IsPushed()) {
		m_eyePoint.y += 2.0;
		m_lookAtPoint.y += 2.0;
	}

	if (input->GetKeys()[DIK_F]->IsPushed()) {
		m_eyePoint.y -= 2.0;
		m_lookAtPoint.y -= 2.0;
	}

	if (input->GetKeys()[DIK_W]->IsPushed()) {
		m_eyePoint.z += 2.0;
		m_lookAtPoint.z += 2.0;
	}

	if (input->GetKeys()[DIK_S]->IsPushed()) {
		m_eyePoint.z -= 2.0;
		m_lookAtPoint.z -= 2.0;
	}

	if (input->GetKeys()[DIK_A]->IsPushed()) {
		m_eyePoint.x -= 2.0;
		m_lookAtPoint.x -= 2.0;
	}

	if (input->GetKeys()[DIK_D]->IsPushed()) {
		m_eyePoint.x += 2.0;
		m_lookAtPoint.x += 2.0;
	}

	if (input->GetKeys()[DIK_UP]->IsPushed()) {
		m_lookAtPoint.y += 2.0;
	}

	if (input->GetKeys()[DIK_DOWN]->IsPushed()) {
		m_lookAtPoint.y -= 2.0;
	}

	if (input->GetKeys()[DIK_RIGHT]->IsPushed()) {
		m_lookAtPoint.x += 2.0;
	}

	if (input->GetKeys()[DIK_LEFT]->IsPushed()) {
		m_lookAtPoint.x -= 2.0;
	}

//	if (input->GetKeys()[DIK_L]->IsPushed()){
//		m_frame++;
//		Sleep(100);
//	}
	

	m_cameraPtr->SetPoint(m_eyePoint);
	m_cameraPtr->SetTarget(m_lookAtPoint);
	m_cameraPtr->Look();
	m_billboardStrPtr->SetPosition(540.0f, 0.0f);
	m_billboardStrPtr->SetColor(0x00ff0000);
	m_billboardStrPtr->RegistString(_T("●REC"));
	m_charaPtr->Update();
	m_tenbouManagerPtr->Update();
	m_simulateMahjongPtr->Update();

	if (m_simulateMahjongPtr->IsNext()){
		m_isNext = true;
	}
}

/**
	描画処理
*/
void MahjongScreen::Draw()
{
	m_tablePtr->Draw();
	m_fieldPtr->Draw();
	m_charaPtr->Draw();
	m_tenbouManagerPtr->Draw();
	m_bgPtr->Draw();
	std::shared_ptr<MahjongTable> mtInfo = m_simulateMahjongPtr->GetTableInfo();
	std::vector<HaiType> doras = mtInfo->GetDora();
	std::vector<std::shared_ptr<TablePlace>> tpPtrs = mtInfo->GetTablePlacePtrs();
	std::vector<std::multiset<HaiType>> tehai;
	std::vector<std::vector<HaiType>> suteHai;
	std::vector<std::vector<std::shared_ptr<FuuroHai>>> fuuroHai;
	std::vector<HaiType> tsumoHai;
	std::vector<int> points;
	std::vector<std::shared_ptr<TablePlace>>::iterator it;
	it = tpPtrs.begin();
	for (it = tpPtrs.begin(); it != tpPtrs.end(); it++)
	{
		tehai.push_back((*it)->GetTehai());
		suteHai.push_back((*it)->GetSutehai());
		fuuroHai.push_back((*it)->GetFuurohais());
		tsumoHai.push_back((*it)->GetTsumohai());
		points.push_back((*it)->GetPoints());
	}
	m_janpaiManagerPtr->DrawTehai(tehai);
	m_janpaiManagerPtr->DrawSuteHai(suteHai);
	m_janpaiManagerPtr->DrawFuuroHai(fuuroHai);
	m_janpaiManagerPtr->DrawTsumoHai(tsumoHai);
	m_janpaiManagerPtr->DrawMountainHai(mtInfo->GetHaiCount(), doras.size());
	m_janpaiManagerPtr->DrawDeadWall(doras);
	m_pointManagerPtr->Draw(points);

	m_lightPtr->Illume(Vector3(0, -1, 0));

	m_resultScreen->DrawRole(judg);			//bool型の配列を渡すことで役表示ができる。上でテスト配列がある。

	m_billboardStrPtr->Draw();
	DebugFont::GetInstance()->Draw();
	DebugFont::GetInstance()->Clear();
}

Screen* MahjongScreen::ChangeScreen()
{
	Screen* pScreen = new EndScreen();
	assert((pScreen != NULL) && "Impossible!");
	return pScreen;
}
