#pragma once
#include "Vector3.h"


/// �J�����N���X
/// 3D��Ԃ̎��_���Ǘ�
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

	// �J�������W�ݒ�
	void SetPoint(const Vector3& eyePoint);

	// �����_�ݒ�
	void SetTarget(const Vector3& lookAtPoint);

	// ����p�ݒ�
	void SetFieldOfViewY(float);

	// �ŋߓ_�ݒ�
	void SetNearClip(float);

	// �ŉ��_�ݒ�
	void SetFarClip(float);

	// �擾�n
	const Vector3* GetPoint() const;
	const Vector3* GetTarget() const;
	float GetFieldOfViewY() const;
	float GetNearClip() const;
	float GetFarClip() const;

	// �J������������
	void Look();
};

