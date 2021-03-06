#pragma once
#include "Vector3.h"

typedef D3DLIGHT9 Light3D;

/// 光源クラス
class Light {
private:
	Light3D m_light;

public:
	Light();
	~Light();

	// 照らす
	void Illume(Vector3 direction);
};

