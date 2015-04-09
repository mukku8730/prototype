#include"CThrowDice.h"

#include<iostream>


/**
	コンストラクタ
	@note	特に無し
	@see	特に無し
*/
CThrowDice::CThrowDice():
m_diceNumber(0)
{

}

/**
	デストラクタ
	@note	特に無し
	@see	特に無し
*/
CThrowDice::~CThrowDice(){

}

/**
	サイコロの数値を取得する関数
	@return	今まで降ってきた数のサイコロの目の総数を返します
	@note	特に無し
	@see	特に無し
*/
int CThrowDice::GetDiceNumber() const{
	return m_diceNumber;
}

/**
	サイコロをふる関数
	@note	サイコロを降る度に加算されます。
			リセットしたい場合はReset関数を使用して下さい。
	@see	特に無し
*/
void CThrowDice::ThrowDice(){
	int diceNum = rand()%6 + 1;

	m_diceNumber += diceNum;
}

/**
	リセット関数
	@note	加算されたサイコロの合計値をリセットする関数
	@see	特に無し
*/
void CThrowDice::Reset(){
	m_diceNumber = 0;
}

