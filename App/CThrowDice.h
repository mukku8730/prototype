#ifndef _THROW_DICE_CLASS_HEADER_20150225_
#define _THROW_DICE_CLASS_HEADER_20150225_


///サイコロクラス
class CThrowDice{
public:
	CThrowDice();
	virtual ~CThrowDice() throw();

	int GetDiceNumber() const;

	void ThrowDice();
	void Reset();

private:
	int m_diceNumber;			//サイコロの数値
};


#endif //_THROW_DICE_CLASS_HEADER_20150225_
