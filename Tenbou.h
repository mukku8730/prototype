#pragma once
#include "Vector3.h"

class FileMesh;

/// �_�_�N���X
class Tenbou
{
private:
	FileMesh* m_tenbou;
	Vector3 m_position;
	Matrix16 m_rotation;
	Vector3 m_scale;

public:
	Tenbou();
	~Tenbou();

	// �e�N�X�`����ݒ�
	HRESULT SetTexture(int janpaiID);

	// ���W�ݒ�
	void SetPosition(const Vector3& position);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};
