#include "TenbouManager.h"
#include "Tenbou.h"
#include <cassert>
#define Tenbo_100	(38)
#define Tenbo_1000	(39)
#define Tenbo_5000	(40)
#define Tenbo_10000	(41)
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	コンストラクタ
*/
TenbouManager::TenbouManager() : m_tenbou(NULL) {
	m_tenbou = new Tenbou();
	assert(m_tenbou != NULL);
}


/**
	デストラクタ
*/
TenbouManager::~TenbouManager() {
	SAFE_DELETE(m_tenbou);
}


/**
	更新処理
*/
void TenbouManager::Update() {
	m_tenbou->Update();
}


/**
	描画処理
	@param	点棒の情報
*/
void TenbouManager::Draw() {
	m_tenbou->SetPosition(Vector3(0.0f, 0.0f, -25.0f));
	m_tenbou->SetTexture(Tenbo_1000);
	m_tenbou->Draw();
	m_tenbou->SetPosition(Vector3(0.0f, 0.0f, -23.0f));
	m_tenbou->SetTexture(Tenbo_1000);
	m_tenbou->Draw();
}
