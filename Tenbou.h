#pragma once
#include "Vector3.h"

class FileMesh;

/// 点棒クラス
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

	// テクスチャを設定
	HRESULT SetTexture(int janpaiID);

	// 座標設定
	void SetPosition(const Vector3& position);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};
