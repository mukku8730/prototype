#include "Character.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Character::Character() :
m_chara(new FileMesh(TEXT("Material/TryCursor.x"))),
m_position(-15.0f, 4.0f, -28.0f),
m_rotation(),
m_scale(0.075f, 0.075f, 0.075f) {
	assert(m_chara != NULL);
	D3DXMatrixIdentity(&m_rotation);
//	m_chara->SetTexture(42);
}


/**
	デストラクタ
*/
Character::~Character()
{
	SAFE_DELETE(m_chara);
}

/**
	更新処理
*/
void Character::Update() {
	// 放物運動の計算
	static int t;	//時間
	++t;
	const float vy0 = 0.03f;  // 速度
	const float ay = -0.001f; // 加速度
	static float vy = vy0;
	m_position.y += vy;
	if (m_position.y <= 4.0f) vy = vy0;
	else vy += ay;
	m_position = Vector3(m_position.x, m_position.y, m_position.z);
	D3DXMatrixRotationY(&m_rotation, (FLOAT)t / 2.0f);
}


/**
	描画処理
*/
void Character::Draw() {
	m_chara->Draw(m_position, m_rotation, m_scale);
}


/**
	座標を取得
*/
Vector3 Character::GetPosition() const {
	return m_position;
}


/**
	座標を設定
*/
void Character::SetPosition(const Vector3& position) {
	m_position = position;
}
