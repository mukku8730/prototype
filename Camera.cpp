#include "Camera.h"
#include "Graphics.h"


/**
	コンストラクタ
*/
Camera::Camera() : 
m_eyePoint(15.0f, 20.0f, -60.0f), 
m_lookAtPoint(0.0, 0.0, 0.0),
m_fieldOfViewY(D3DXToRadian(60)),
m_nearClip(0.1f),
m_farClip(2000.0f) {
}


/**
	デストラクタ
*/
Camera::~Camera() {}


/**
	カメラ座標設定
	@param eyePoint	カメラ座標
*/
void Camera::SetPoint(const Vector3& eyePoint) {
	m_eyePoint = eyePoint;
}


/**
	注視点設定
	@param lookAtPoint	注視点
*/
void Camera::SetTarget(const Vector3& lookAtPoint) {
	m_lookAtPoint = lookAtPoint;
}


/**
	視野角設定
	@param fieldOfViewY	視野角
*/
void Camera::SetFieldOfViewY(float fieldOfViewY) {
	m_fieldOfViewY = fieldOfViewY;
}


/**
	最近点設定
	@param nearClip	最近点
*/
void Camera::SetNearClip(float nearClip) {
	m_nearClip = nearClip;
}


/**
	最遠点設定
	@param farClip	最遠点
*/
void Camera::SetFarClip(float farClip) {
	m_farClip = farClip;
}


/// 取得系
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
	カメラを向ける
*/
void Camera::Look() {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	const Vector3 upVec = D3DXVECTOR3(0, 1, 0); // 上方ベクトル
	D3DVIEWPORT9 vp;
	if (FAILED(pDevice->GetViewport(&vp))) return;
	const float aspect = (float)vp.Width / (float)vp.Height; // アスペクト比 = ビュー空間の高さ/幅
	D3DXMATRIXA16 matView, matProj;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixLookAtLH(&matView, &m_eyePoint, &m_lookAtPoint, &upVec);
	D3DXMatrixPerspectiveFovLH(&matProj, m_fieldOfViewY, aspect, m_nearClip, m_farClip);
	pDevice->SetTransform(D3DTS_VIEW, &matView);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
