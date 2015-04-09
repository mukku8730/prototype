#pragma once

/// キークラス
class Key
{
public:
	Key();
	~Key();
	bool IsPushed();
	void Pushed(bool pushed);

private:
	bool m_isPushed;
};

