#pragma once
#include "Vector3.h"


/// カメラクラス
/// 3D空間の視点を管理
class Camera {
private:
	Vector3 m_eyePoint;
	Vector3 m_lookAtPoint;
	float m_fieldOfViewY;
	float m_nearClip;
	float m_farClip;

public:
	Camera();

	~Camera();

	// カメラ座標設定
	void SetPoint(const Vector3& eyePoint);

	// 注視点設定
	void SetTarget(const Vector3& lookAtPoint);

	// 視野角設定
	void SetFieldOfViewY(float);

	// 最近点設定
	void SetNearClip(float);

	// 最遠点設定
	void SetFarClip(float);

	// 取得系
	const Vector3* GetPoint() const;
	const Vector3* GetTarget() const;
	float GetFieldOfViewY() const;
	float GetNearClip() const;
	float GetFarClip() const;

	// カメラを向ける
	void Look();
};

