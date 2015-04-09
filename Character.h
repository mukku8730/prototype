#pragma once
#include "Vector3.h"

class FileMesh;


class Character
{
private:
	FileMesh* m_chara;
	Vector3 m_position;
	Matrix16 m_rotation;
	Vector3 m_scale;

public:
	Character();
	~Character();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// ���W���擾
	Vector3 GetPosition() const;

	// ���W��ݒ�
	void SetPosition(const Vector3& position);
};
