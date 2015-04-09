#pragma once
#include "Vector3.h"
#include <d3dx9.h>

class FileMesh;


/// �w�i�N���X
class Background {
private:
	FileMesh* m_table;
	Vector3 m_position;
	D3DXMATRIX m_rotation;

public:
	Background();
	~Background();

	// �`�揈��
	void Draw();
};

