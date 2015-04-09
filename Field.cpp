#include "Field.h"
#include "Graphics.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Field::Field() :
m_field(new FileMesh(TEXT("Material/batokin_island5.x"))),
m_position(0.0, -30.0, 0.0),
m_rotation() {
	assert(m_field != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	デストラクタ
*/
Field::~Field()
{
	SAFE_DELETE(m_field);
}

/**
	描画処理
*/
void Field::Draw() {
	m_field->Draw(m_position, m_rotation);
}
