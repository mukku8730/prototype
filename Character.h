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

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 座標を取得
	Vector3 GetPosition() const;

	// 座標を設定
	void SetPosition(const Vector3& position);
};
