#include "Janpai.h"
#include "FileMesh.h"
#include "Key.h"
#include "KeyInput.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Janpai::Janpai() :
m_janpai(new FileMesh(TEXT("Material/Janpai.x"))),
m_position(0.0, 0.0, 0.0),
m_rotation(),
m_scale(0.1f, 0.1f, 0.1f) {
	assert(m_janpai != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	デストラクタ
*/
Janpai::~Janpai() {
	SAFE_DELETE(m_janpai);
}

/**
	位置を設定
*/
void Janpai::SetPosition(const Vector3 position) {
	m_position = position;
}


/**
	姿勢を設定
*/
void Janpai::SetRotation(const Vector3 rotation) {
	Matrix16 matWorld, matRotation;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRotation);

	// 回転行列を作成する
	D3DXMatrixRotationX(&matRotation, D3DXToRadian(rotation.x));
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotation);

	D3DXMatrixRotationY(&matRotation, D3DXToRadian(rotation.y));
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotation);

	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(rotation.z));
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotation);

	m_rotation = matWorld;
}


/**
	テクスチャを設定
	@param janpaiID	指定したID

*/
HRESULT Janpai::SetTexture(int janpaiID) {
	if (FAILED(m_janpai->SetTexture(janpaiID))) return E_FAIL;
	return S_OK;
}


/**
	更新処理
*/
void Janpai::Update() {}


/**
	描画処理
*/
void Janpai::Draw() {
	m_janpai->Draw(m_position, m_rotation, m_scale);
}
