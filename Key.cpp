#include "Key.h"


/**
	コンストラクタ
*/
Key::Key() : m_isPushed(false) {}

/**
	デストラクタ
*/
Key::~Key() {}


/**
	キーが押されているか否か
	@reutrn true or false
*/
bool Key::IsPushed()
{
	return m_isPushed;
}

/**
	押されたフラグ
	@param isPushed	押されたフラグ
*/
void Key::Pushed(bool isPushed)
{
	m_isPushed = isPushed;
}
