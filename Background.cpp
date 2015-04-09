#include "Background.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Background::Background() :
m_table(new FileMesh(TEXT("Material/dome324.X"))),
m_position(0.0, 0.0, 0.0),
m_rotation() {
	assert(m_table != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	デストラクタ
*/
Background::~Background() {
	SAFE_DELETE(m_table);
}


/**
	描画処理
*/
void Background::Draw() {
	m_table->Draw(m_position, m_rotation);
}
