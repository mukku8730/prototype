#pragma once
#include "Vector3.h"

typedef D3DLIGHT9 Light3D;

/// �����N���X
class Light {
private:
	Light3D m_light;

public:
	Light();
	~Light();

	// �Ƃ炷
	void Illume(Vector3 direction);
};

