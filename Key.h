#pragma once

/// �L�[�N���X
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

