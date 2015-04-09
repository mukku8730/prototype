#include "RealUser.h"
#include "../Key.h"
#include "../KeyInput.h"
#include <random>
#include <algorithm> 
#include <cassert>

#include "../DebugFont.h"

struct S_key
{
	E_place place;
	int keyLeft;
	int keyRight;
	int keyEnter;
	int number;
};

static const S_key keyTBL[]
{
	{ E_place_1, DIK_5, DIK_7, DIK_6 , 0},
	{ E_place_2, DIK_8, DIK_0, DIK_9 , 1},
	{ E_place_3, DIK_T, DIK_U, DIK_Y , 2},
	{ E_place_4, DIK_I, DIK_P, DIK_O , 3},
};

RealUser::RealUser(E_place place, std::shared_ptr<MahjongTable> mahjongTablePtr) : Player(place, mahjongTablePtr)
{
}

RealUser::~RealUser() throw()
{
}

void RealUser::Update()
{
	KeyInput* input = KeyInput::GetInstance();
	if (input->GetKeys()[DIK_N]->IsPushed())
	{
		if (HaiKey::GetHaiKey(HaiKey::GetHaiKeyNumber(m_haiKey)) > E_haiKey_Tehai_1)
		{
			m_haiKey = HaiKey::GetHaiKey(HaiKey::GetHaiKeyNumber(m_haiKey) - 1);
		}
	}

	if (input->GetKeys()[DIK_M]->IsPushed())
	{
		if (HaiKey::GetHaiKey(HaiKey::GetHaiKeyNumber(m_haiKey)) < E_haiKey_Tsumohai)
		{
			m_haiKey = HaiKey::GetHaiKey(HaiKey::GetHaiKeyNumber(m_haiKey) + 1);
		}
	}

//	DebugFont::Option option;

	// デバック用
	DebugFont::GetInstance()->DebugFont::Print(70, (60 + (keyTBL[m_place].number * 20)), 0xffffffff, "HaiKey:%d...MenuKey:%d", HaiKey::GetHaiKeyNumber(m_haiKey), PopupMenuKey::GetPopupMenuKeyNumber(m_popupMenuKey));
	// 右寄せ
//	option.clip = true;
//	option.clipWidth = 120;
//	option.align = DebugFont::Option::RIGHT;
//	DebugFont::GetInstance()->Print(70, 150, 0xffffff00, option, "Clipping and Alignment: w = %d, Right alignment.", option.clipWidth);

	if (m_isMyTurn)
	{
//		std::random_device rd;
//		std::mt19937 mt(rd());
//		std::uniform_int_distribution<int> haiKeyRd(1, 10);
//		m_haiKey = HaiKey::GetHaiKey(haiKeyRd(mt));
		switch (m_sceneType)
		{
		case E_sceneType_None:
			break;

		case E_sceneType_AgariResult:
			m_isMyTurn = false;
			m_hasSelected = false;
			break;

		case E_sceneType_Agari:
			break;

		case E_sceneType_DecideOya:
			break;

		case E_sceneType_Discard:
			if (m_hasSelected)
			{
				switch (m_haiKey)
				{
				case E_haiKey_none:
					break;
				case E_haiKey_Tsumohai:
					m_mahjongTablePtr->Discard(m_place);
					m_isMyTurn = false;
					m_hasSelected = false;
					break;
				default:
					if ((HaiKey::GetHaiKeyNumber(m_haiKey) - 1) < m_mahjongTablePtr->GetTehaiMax(m_place))
					{
						//牌選択用の仮想キーの取得したい数値が１からのため（E_haiKey_None = 0）、数値-１をする
						m_mahjongTablePtr->Discard(m_place, HaiKey::GetHaiKeyNumber(m_haiKey) - 1);
						m_isMyTurn = false;
						m_hasSelected = false;
					}
					break;
				}
			}
			break;

		case E_sceneType_Fuuro:
			if (m_hasSelected){
				switch (m_popupMenuKey)
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
				m_hasSelected = false;
			}
			m_isMyTurn = false;
			break;

		case E_sceneType_Haipai:
			break;

		case E_sceneType_PopUpMenu:
			if (input->GetKeys()[keyTBL[m_place].keyLeft]->IsPushed() && !m_hasSelected)
			{
				if (PopupMenuKey::GetPopupMenuKey(PopupMenuKey::GetPopupMenuKeyNumber(m_popupMenuKey) - 1) != E_popupMenuKey_none)
				{
					m_popupMenuKey = PopupMenuKey::GetPopupMenuKey(PopupMenuKey::GetPopupMenuKeyNumber(m_popupMenuKey) - 1);
				}
			}

			if (input->GetKeys()[keyTBL[m_place].keyRight]->IsPushed() && !m_hasSelected)
			{
				if (PopupMenuKey::GetPopupMenuKey(PopupMenuKey::GetPopupMenuKeyNumber(m_popupMenuKey) + 1) != E_popupMenuKey_MAX)
				{
					m_popupMenuKey = PopupMenuKey::GetPopupMenuKey(PopupMenuKey::GetPopupMenuKeyNumber(m_popupMenuKey) + 1);
				}
			}

			if (input->GetKeys()[keyTBL[m_place].keyEnter]->IsPushed() && !m_hasSelected)
			{
				m_isMyTurn = false;
				m_hasSelected = true;
			}
			break;

		case E_sceneType_SelectHai:
			if (input->GetKeys()[DIK_L]->IsPushed())
			{
				switch (m_haiKey)
				{
				case E_haiKey_none:
					break;
				case E_haiKey_Tsumohai:
					m_isMyTurn = false;
					m_hasSelected = true;
					break;
				default:
					if ((HaiKey::GetHaiKeyNumber(m_haiKey) - 1) < m_mahjongTablePtr->GetTehaiMax(m_place))
					{
						//牌選択用の仮想キーの取得したい数値が１からのため（E_haiKey_None = 0）、数値-１をする
						m_isMyTurn = false;
						m_hasSelected = true;
					}
					break;
				}
			}
			break;

		case E_sceneType_SelectFuuroHai:
			break;
		case E_sceneType_Tsumo:
			if (m_hasSelected)
			{
				m_isMyTurn = false;
				m_hasSelected = false;
			}
			if (m_isMyTurn)
			{
				m_mahjongTablePtr->Tsumo(m_place);
				m_isMyTurn = false;
			}
			break;

		case E_sceneType_MAX:
			break;

		default:
			break;

		}
	}
}
