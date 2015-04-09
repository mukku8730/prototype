#include "PopUpMenuScene.h"
#include "TsumoScene.h"
#include "RyuukyokuScene.h"
#include "AgariScene.h"
#include "SelectFuuroHaiScene.h"
#include "AgariJudgement.h"
#include "FuuroJudgement.h"
#include <memory>
#include "../Key.h"
#include "../KeyInput.h"
#include "../BillboardString.h"
#include <iostream>
#define STANDBY_TIME (30)

static const wchar_t* buttonTable[] = {
	L"ポン", L"カン", L"チー", L"ロン", L"ツモ", L"リーチ", L"パス", L"\0"
};

static const E_sceneType SCENE_TYPE = E_sceneType_PopUpMenu;
static const int MAX_BUTTON_INDEX = 7;
typedef std::vector<const wchar_t*> ButtonList;


PopUpMenuScene::PopUpMenuScene() : 
GameScene(),
m_frame(0)
{
}

PopUpMenuScene::~PopUpMenuScene()  throw()
{
}

void PopUpMenuScene::Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer)
{
//	BillboardString* pButtons[MAX_BUTTON_INDEX] = { NULL };
//	ButtonList buttonList;
//	int roleCount = 0;
//	int roleIndex = 0;
//	int beside = -1;
//	int height = 0;
//
//	buttonList.push_back(buttonTable[]);
//
//
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
//			m_popMenuFrag.set(CursorType_Right);
//		}
//		else if (input->GetKeys()[DIK_LEFT]->IsPushed()) {
//			m_isPushed = true;
//			m_popMenuFrag.set(CursorType_Left);
//		}
//		else if (input->GetKeys()[DIK_UP]->IsPushed()) {
//			m_isPushed = true;
//			m_popMenuFrag.set(CursorType_Up);
//		}
//		else if (input->GetKeys()[DIK_DOWN]->IsPushed()) {
//			m_isPushed = true;
//			m_popMenuFrag.set(CursorType_Down);
//		}
//		else if (input->GetKeys()[DIK_RETURN]->IsPushed()) {
//			m_isPushed = true;
//			m_popMenuFrag.set(CursorType_Enter);
//		}
//
//	}


	if (IsFirst())
	{

		for (SharedPlayers::iterator spIt = pSharedPlayers->begin(); spIt != pSharedPlayers->end(); spIt++)
		{
			E_place place = (*spIt)->GetPlace();
			if (place != (*pOwnerPlayer)->GetPlace())
			{
				E_place owerPlace = (*pOwnerPlayer)->GetPlace();
				E_place prevPlace = Place::GetPrevPlace(place);
				std::multiset<HaiType> tehai = (pMahjongTable->GetTablePlace(place))->GetTehai();
				HaiType ownerLastSutehai = pMahjongTable->GetTablePlace(owerPlace)->GetLastSutehai();
				if ((AgariJudgement::JudgeAgari(tehai, ownerLastSutehai)))
				{
					(*spIt)->MyTurn(true);
				}
				else if ((FuuroJudgement::JudgePon(tehai, pMahjongTable->GetTablePlace(owerPlace)->GetLastSutehai())))
				{
					(*spIt)->MyTurn(true);
				}
				else if ((FuuroJudgement::JudgeMinkan(tehai, pMahjongTable->GetTablePlace(owerPlace)->GetLastSutehai())))
				{
					(*spIt)->MyTurn(true);
				}
				else if (owerPlace == prevPlace)
				{
					if ((FuuroJudgement::JudgeChii(tehai, pMahjongTable->GetTablePlace(owerPlace)->GetLastSutehai())))
					{
						(*spIt)->MyTurn(true);
					}
				}
				else
				{
					(*spIt)->MyTurn(false);
				}
			}
		}
	}
	
	bool isNextScene = true;
	for (SharedPlayers::iterator it = pSharedPlayers->begin(); it != pSharedPlayers->end(); it++)
	{
		// TODO:使ってない by karino
		//const int placeNum = Place::GetPlaceNumber((*it)->GetPlace());
		
		if ((*it)->IsMyTurn())
		{
			if (!(*it)->HasSelected())
			{
				isNextScene = false;
				break;
			}
			else
			{
				switch ((*it)->GetPopupMenuKey())
				{
				case E_popupMenuKey_none:
					break;
				case E_popupMenuKey_Chii:
					NextFuuro(true);
					break;
				case E_popupMenuKey_Pon:
					NextFuuro(true);
					break;
				case E_popupMenuKey_Kan:
					NextFuuro(true);
					break;
				case E_popupMenuKey_Ron:
					NextAgari(true);
					break;
				case E_popupMenuKey_Tsumo:
					NextAgari(true);
					break;
				case E_popupMenuKey_Cancel:
					break;
				default:
					break;
				}
			}
		}
	}
	if (pMahjongTable->GetHaiCount() <= 0)
	{
		NextRyuukyoku(true);
	}
	NextScene(isNextScene);
}

GameScene* PopUpMenuScene::ChangeGameScene()
{
	GameScene* pGameScene = NULL;
	if (m_isNextAgari)
	{
		m_isNextAgari = false;
		m_isNextRyuukyoku = false;
		m_isNextFuuro = false;
		pGameScene = new AgariScene();
	}

	else if (m_isNextRyuukyoku)
	{
		m_isNextRyuukyoku = false;
		m_isNextFuuro = false;
		pGameScene = new RyuukyokuScene();
	}

	else if (m_isNextFuuro)
	{
		m_isNextFuuro = false;
		pGameScene = new SelectFuuroHaiScene();
	}

	else
	{
		pGameScene = new TsumoScene();
	}

	return pGameScene;
}

E_sceneType PopUpMenuScene::GetSceneType()
{
	return SCENE_TYPE;
}
