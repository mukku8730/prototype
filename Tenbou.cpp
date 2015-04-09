#include "Tenbou.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Tenbou::Tenbou() :
m_tenbou(new FileMesh(TEXT("Material/tenbou.x"))),
m_position(0.0f, 0.0f, 0.0f),
m_rotation(),
m_scale(0.1f, 0.1f, 0.1f) {
	assert(m_tenbou != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	デストラクタ
*/
Tenbou::~Tenbou()
{
	SAFE_DELETE(m_tenbou);
}


/**
	テクスチャを設定
	@param janpaiID	指定したID
*/
HRESULT Tenbou::SetTexture(int janpaiID) {
	if (FAILED(m_tenbou->SetTexture(janpaiID))) return E_FAIL;
	return S_OK;
}


/**
	座標設定
	@param position	座標
*/
void Tenbou::SetPosition(const Vector3& position) {
	m_position = position;
}


/**
	更新処理
*/
void Tenbou::Update() {
	D3DXMatrixRotationY(&m_rotation, D3DX_PI / 2); // 90°回転
}


/**
	描画処理
	@param	点棒の情報
*/
void Tenbou::Draw() {
	m_tenbou->Draw(m_position, m_rotation, m_scale);
}
