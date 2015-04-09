#include "Player.h"


Player::Player(E_place place, std::shared_ptr<MahjongTable> mahjongTablePtr)
	: m_mahjongTablePtr(mahjongTablePtr)
	, m_haiKey(E_haiKey_none)
	, m_selectHaiType(new HaiType[2])
	, m_popupMenuKey(E_popupMenuKey_none)
	, m_place(place)
	, m_kaze()
	, m_sceneType()
	, m_isMyTurn(false)
	, m_hasSelected(false)
{
}

Player::~Player() throw()
{
}

void Player::Update()
{
}

E_haiKey Player::GetHaiKey() const
{
	return m_haiKey;
}

void Player::ClearHaiKey()
{
	m_haiKey = E_haiKey_none;
}

E_popupMenuKey Player::GetPopupMenuKey() const
{
	return m_popupMenuKey;
}

void Player::ClearPopupMenuKey()
{
	m_popupMenuKey = E_popupMenuKey_none;
}

E_kaze Player::GetKaze() const
{
	return m_kaze;
}

void Player::SetKaze(E_kaze kaze)
{
	m_kaze = kaze;
}

void Player::SetSceneType(E_sceneType sceneType)
{
	m_sceneType = sceneType;
}

bool Player::IsMyTurn() const
{
	return m_isMyTurn;
}

void Player::MyTurn(bool isMyTurn)
{
	m_isMyTurn = isMyTurn;
}

E_place Player::GetPlace() const
{
	return m_place;
}

void Player::SetPlace(E_place place)
{
	m_place = place;
}

bool Player::HasSelected()
{
	return m_hasSelected;
}
