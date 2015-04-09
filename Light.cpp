#include "Light.h"
#include "Graphics.h"


/**
	コンストラクタ
*/
Light::Light() : m_light() {
	const D3DCOLORVALUE diffuse = { 0.9f, 0.9f, 0.9f, 1.0f };	// ディフューズ
	const D3DCOLORVALUE specular = { 0.7f, 0.7f, 0.7f, 1.0f };	// スペキュラー
	const D3DCOLORVALUE ambient = { 0.0f, 0.0f, 0.0f, 0.0f };	// アンビエント
	const float range = 200.0f;							// 距離
	const Vector3 direction(-0.1f, -1.0f, -0.1f);	// 方向
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Ambient = ambient;
	m_light.Diffuse = diffuse;
	m_light.Specular = specular;
	m_light.Range = range;
	m_light.Direction = direction;
}


/**
	デストラクタ
*/
Light::~Light() {}


/**
	照らす
	@param direction	照らす方向
*/
void Light::Illume(Vector3 direction) {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	m_light.Direction = direction;

	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライトを有効にする
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xff808080);		// アンビエントライト（環境光）を設定する
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// スペキュラ（鏡面反射）を有効にする
}
