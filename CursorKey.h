#pragma once
#include <bitset>

/// カーソルタイプ
enum CursorType {
	CursorType_None,
	CursorType_Left,
	CursorType_Right,
	CursorType_Up,
	CursorType_Down,
	CursorType_Enter,

	CursorType_Max
};


/// カーソルキー管理
class CursorKey
{
private:
	std::bitset<CursorType_Max> m_cursor;
	int m_frame;
	bool m_isPushed;

public:
	CursorKey();
	~CursorKey();
	void Update();
	CursorType GetCursor();
};

