#include"CThrowDice.h"

#include<iostream>


/**
	�R���X�g���N�^
	@note	���ɖ���
	@see	���ɖ���
*/
CThrowDice::CThrowDice():
m_diceNumber(0)
{

}

/**
	�f�X�g���N�^
	@note	���ɖ���
	@see	���ɖ���
*/
CThrowDice::~CThrowDice(){

}

/**
	�T�C�R���̐��l���擾����֐�
	@return	���܂ō~���Ă������̃T�C�R���̖ڂ̑�����Ԃ��܂�
	@note	���ɖ���
	@see	���ɖ���
*/
int CThrowDice::GetDiceNumber() const{
	return m_diceNumber;
}

/**
	�T�C�R�����ӂ�֐�
	@note	�T�C�R�����~��x�ɉ��Z����܂��B
			���Z�b�g�������ꍇ��Reset�֐����g�p���ĉ������B
	@see	���ɖ���
*/
void CThrowDice::ThrowDice(){
	int diceNum = rand()%6 + 1;

	m_diceNumber += diceNum;
}

/**
	���Z�b�g�֐�
	@note	���Z���ꂽ�T�C�R���̍��v�l�����Z�b�g����֐�
	@see	���ɖ���
*/
void CThrowDice::Reset(){
	m_diceNumber = 0;
}

