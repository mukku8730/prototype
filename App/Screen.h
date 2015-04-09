#ifndef _MAHJONG_SCREEN_HEADER_2015_0212_
#define _MAHJONG_SCREEN_HEADER_2015_0212_

class Screen
{
public:
	Screen();
	virtual ~Screen() throw();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual Screen* ChangeScreen() = 0;
	bool GetIsNext() const;

protected:
	int m_frame;
	bool m_isNext;
};

#endif //_MAHJONG_SCREEN_HEADER_2015_0212_
