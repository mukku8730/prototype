#pragma once
#include "Vector3.h"

class FileMesh;

class Field {
private:
	FileMesh* m_field;
	Vector3 m_position;
	Matrix16 m_rotation;

public:
	Field();
	~Field();

	// �`�揈��
	void Draw();
};
