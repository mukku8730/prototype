#pragma once
#include "Vector3.h"

typedef D3DLIGHT9 Light3D;

/// ŒõŒ¹ƒNƒ‰ƒX
class Light {
private:
	Light3D m_light;

public:
	Light();
	~Light();

	// Æ‚ç‚·
	void Illume(Vector3 direction);
};

