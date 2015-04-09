#include "SelectHaiScene.h"
#include "../BillboardString.h"
#include "DiscardScene.h"
#include "../Character.h"
#include "../Key.h"
#include "../KeyInput.h"
#include <iostream>
#include <cassert>
#define STANDBY_TIME (30)
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

static const E_sceneType SCENE_TYPE = E_sceneType_SelectHai;

SelectHaiScene::SelectHaiScene() : 
GameScene(),
m_character(new Character()),
m_tehai(),
m_order(1),
m_frame(0),
m_isPushed(false)
{
	assert(m_character != NULL);
}


SelectHaiScene::~SelectHaiScene()  throw()
{
	SAFE_DELETE(m_character);
}

void SelectHaiScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
//	if (m_isPushed) {
//		m_frame++;
//		if (m_frame > STANDBY_TIME) {
//			m_frame = 0;
//			m_isPushed = false;
//		}
//	}
//	else {
//		KeyInput* input = KeyInput::GetInstance();
//		input->Update();
//
//		if (input->GetKeys()[DIK_RIGHT]->IsPushed()) {
//			m_isPushed = true;
//			m_order++;
//			Vector3 position = m_character->GetPosition();
//			if (m_order > m_tehai.size()) {
//				m_order = 1;
//				position.x -= (m_tehai.size() - 1) * 1.9f;
//			}
//			else {
//				position.x += 1.9f;
//			}
//			m_character->SetPosition(position);
//		}
//
//		if (input->GetKeys()[DIK_LEFT]->IsPushed()) {
//			m_isPushed = true;
//			m_order++;
//			Vector3 position = m_character->GetPosition();
//			if (m_order > m_tehai.size()) {
//				m_order = 1;
//				position.x += (m_tehai.size() - 1) * 1.9f;
//			}
//			else {
//				position.x -= 1.9f;
//			}
//			m_character->SetPosition(position);
//		}
//
//		if (input->GetKeys()[DIK_RETURN]->IsPushed()) {
//			m_isPushed = true;
//		}
//
//	}

	if (IsFirst())
	{
		(*pOwnerPlayer)->MyTurn(true);
	}
	if ((*pOwnerPlayer)->HasSelected())
	{
		NextScene(true);
	}
}


GameScene* SelectHaiScene::ChangeGameScene()
{
	GameScene* pGameScene = new DiscardScene();
	return pGameScene;
}

E_sceneType SelectHaiScene::GetSceneType()
{
	return SCENE_TYPE;
}

/**
	è”v‚ğİ’è
	@param tehai	è”v
*/
void SelectHaiScene::SetTehai(std::vector<HaiType> tehai) {
	m_tehai = tehai;
}


/**
	‘I‘ğ‚µ‚½”v‚ğæ“¾
*/
HaiType SelectHaiScene::GetSelectHai() {
	return m_tehai[m_order - 1]; // ”z—ñ‚Ì“Y‚¦š‚ÉƒAƒNƒZƒX‚·‚é‚½‚ß(-1)
}
