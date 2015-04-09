#include "Table.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
Table::Table() :
m_table(new FileMesh(TEXT("Material/Table.x"))),
m_position(0.0f, 0.0f, 0.0f),
m_rotation(),
m_scale(0.1f, 0.1f, 0.1f) {
	assert(m_table != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	デストラクタ
*/
Table::~Table() {
	SAFE_DELETE(m_table);
}


/**
	描画処理
*/
void Table::Draw() {
	m_table->Draw(m_position, m_rotation, m_scale);
}

