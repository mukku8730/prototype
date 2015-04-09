#pragma once
#include "Vector3.h"
#include <d3dx9.h>

class FileMesh;


/// ”wŒiƒNƒ‰ƒX
class Background {
private:
	FileMesh* m_table;
	Vector3 m_position;
	D3DXMATRIX m_rotation;

public:
	Background();
	~Background();

	// •`‰æˆ—
	void Draw();
};

