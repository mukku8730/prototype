#include "Light.h"
#include "Graphics.h"


/**
	�R���X�g���N�^
*/
Light::Light() : m_light() {
	const D3DCOLORVALUE diffuse = { 0.9f, 0.9f, 0.9f, 1.0f };	// �f�B�t���[�Y
	const D3DCOLORVALUE specular = { 0.7f, 0.7f, 0.7f, 1.0f };	// �X�y�L�����[
	const D3DCOLORVALUE ambient = { 0.0f, 0.0f, 0.0f, 0.0f };	// �A���r�G���g
	const float range = 200.0f;							// ����
	const Vector3 direction(-0.1f, -1.0f, -0.1f);	// ����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Ambient = ambient;
	m_light.Diffuse = diffuse;
	m_light.Specular = specular;
	m_light.Range = range;
	m_light.Direction = direction;
}


/**
	�f�X�g���N�^
*/
Light::~Light() {}


/**
	�Ƃ炷
	@param direction	�Ƃ炷����
*/
void Light::Illume(Vector3 direction) {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	m_light.Direction = direction;

	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xff808080);		// �A���r�G���g���C�g�i�����j��ݒ肷��
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
}
