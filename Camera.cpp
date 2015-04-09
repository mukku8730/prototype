#include "Camera.h"
#include "Graphics.h"


/**
	�R���X�g���N�^
*/
Camera::Camera() : 
m_eyePoint(15.0f, 20.0f, -60.0f), 
m_lookAtPoint(0.0, 0.0, 0.0),
m_fieldOfViewY(D3DXToRadian(60)),
m_nearClip(0.1f),
m_farClip(2000.0f) {
}


/**
	�f�X�g���N�^
*/
Camera::~Camera() {}


/**
	�J�������W�ݒ�
	@param eyePoint	�J�������W
*/
void Camera::SetPoint(const Vector3& eyePoint) {
	m_eyePoint = eyePoint;
}


/**
	�����_�ݒ�
	@param lookAtPoint	�����_
*/
void Camera::SetTarget(const Vector3& lookAtPoint) {
	m_lookAtPoint = lookAtPoint;
}


/**
	����p�ݒ�
	@param fieldOfViewY	����p
*/
void Camera::SetFieldOfViewY(float fieldOfViewY) {
	m_fieldOfViewY = fieldOfViewY;
}


/**
	�ŋߓ_�ݒ�
	@param nearClip	�ŋߓ_
*/
void Camera::SetNearClip(float nearClip) {
	m_nearClip = nearClip;
}


/**
	�ŉ��_�ݒ�
	@param farClip	�ŉ��_
*/
void Camera::SetFarClip(float farClip) {
	m_farClip = farClip;
}


/// �擾�n
const Vector3* Camera::GetPoint() const {
	return &m_eyePoint;

}

const Vector3* Camera::GetTarget() const {
	return &m_lookAtPoint;
}

float Camera::GetFieldOfViewY() const {
	return m_fieldOfViewY;
}

float Camera::GetNearClip() const {
	return m_nearClip;
}

float Camera::GetFarClip() const {
	return m_farClip;
}


/**
	�J������������
*/
void Camera::Look() {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	const Vector3 upVec = D3DXVECTOR3(0, 1, 0); // ����x�N�g��
	D3DVIEWPORT9 vp;
	if (FAILED(pDevice->GetViewport(&vp))) return;
	const float aspect = (float)vp.Width / (float)vp.Height; // �A�X�y�N�g�� = �r���[��Ԃ̍���/��
	D3DXMATRIXA16 matView, matProj;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixLookAtLH(&matView, &m_eyePoint, &m_lookAtPoint, &upVec);
	D3DXMatrixPerspectiveFovLH(&matProj, m_fieldOfViewY, aspect, m_nearClip, m_farClip);
	pDevice->SetTransform(D3DTS_VIEW, &matView);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
