#ifndef _THROW_DICE_CLASS_HEADER_20150225_
#define _THROW_DICE_CLASS_HEADER_20150225_


///�T�C�R���N���X
class CThrowDice{
public:
	CThrowDice();
	virtual ~CThrowDice() throw();

	int GetDiceNumber() const;

	void ThrowDice();
	void Reset();

private:
	int m_diceNumber;			//�T�C�R���̐��l
};


#endif //_THROW_DICE_CLASS_HEADER_20150225_
