#include "Key.h"


/**
	�R���X�g���N�^
*/
Key::Key() : m_isPushed(false) {}

/**
	�f�X�g���N�^
*/
Key::~Key() {}


/**
	�L�[��������Ă��邩�ۂ�
	@reutrn true or false
*/
bool Key::IsPushed()
{
	return m_isPushed;
}

/**
	�����ꂽ�t���O
	@param isPushed	�����ꂽ�t���O
*/
void Key::Pushed(bool isPushed)
{
	m_isPushed = isPushed;
}
