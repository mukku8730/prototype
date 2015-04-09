#include "SimulateMahjong.h"
#include "RealUser.h"
#include "RyuukyokuScene.h"
#include "DecideOyaScene.h"
#include "Place.h"
#include "../CursorKey.h"
#include <iostream>
#include <cassert>
#include <typeinfo>

static const int FRAME_MAX = 10000;

SimulateMahjong::SimulateMahjong()
	: m_mahjongTablePtr(new MahjongTable())
	, m_gameScenePtr(new DecideOyaScene())
	, m_cursorKeyPtr(new CursorKey())
	, m_playerPtrs()
	, m_ownerPlayer()
	, m_isNext(false)
	, m_isFirst(true)
	, m_frame(0)
{
	for (int i = 0; i < Place::GetPlaceMax(); i++)
	{
		Player* pPlayer = new RealUser(Place::GetPlace(i), m_mahjongTablePtr);
		m_playerPtrs.push_back(SharedPlayer(pPlayer));
		assert(m_playerPtrs.back());
	}
}

SimulateMahjong::~SimulateMahjong() throw()
{
}

void SimulateMahjong::Update()
{
	if (m_isFirst)
	{
		Init();
		m_isFirst = false;
	}
	
	m_gameScenePtr->Update(m_mahjongTablePtr.get(), &m_playerPtrs, &m_ownerPlayer);
	if (m_gameScenePtr->IsNextScene())
	{
		m_gameScenePtr.reset(m_gameScenePtr->ChangeGameScene());
	}
	if ((m_frame % FRAME_MAX) == (FRAME_MAX - 1))
	{
		m_isNext = true;
	}

	m_cursorKeyPtr->Update();
	CursorType cursorKey = m_cursorKeyPtr->GetCursor();

	for (SharedPlayers::iterator it = m_playerPtrs.begin(); it != m_playerPtrs.end(); it++)
	{
		(*it)->SetSceneType(m_gameScenePtr->GetSceneType());
//		if (typeid(*it) == typeid(RealUser)) (*it)->SetCursorKey(cursorKey);
		(*it)->Update();
	}
	m_frame++;
}

bool SimulateMahjong::IsNext() const
{
	return m_isNext;
}

std::shared_ptr<MahjongTable> SimulateMahjong::GetTableInfo() const
{
	return m_mahjongTablePtr;
}

void SimulateMahjong::Init()
{
	m_mahjongTablePtr->Init();
}
