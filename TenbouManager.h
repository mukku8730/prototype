#pragma once
#include <set>

class Tenbou;


/// �_�_���Y�H�ꌓ�Ǘ��N���X
class TenbouManager
{
private:
	Tenbou* m_tenbou;

public:
	TenbouManager();
	~TenbouManager();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};


