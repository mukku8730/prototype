#pragma once
#include "Vector3.h"

class FileMesh;

class Table {
private:
	FileMesh* m_table;
	Vector3 m_position;
	Matrix16 m_rotation;
	Vector3 m_scale;

public:
	Table();
	~Table();

	// •`‰æˆ—
	void Draw();
};

