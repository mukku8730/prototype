#include "Sprites.h"
#include "Graphics.h"
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }



/**
	コンストラクタ
	@param filename	画像ファイル名
	@param add		加算合成か否か
*/
Sprites::Sprites(LPCTSTR filename, bool add) :
m_pTexture(NULL),
m_pSprite(NULL),
m_additive(false)
{
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	D3DXCreateSprite(pDevice, &m_pSprite);
	if (D3DXCreateTextureFromFileEx(pDevice, filename, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL, &m_pTexture) != D3D_OK) // 色抜きなし
		throw TEXT("テクスチャの作成に失敗しました");
}


/**
	デストラクタ
*/
Sprites::~Sprites() {
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}


/**
	ブレンドの設定
*/
void Sprites::SetRenderState() {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	DWORD src, dest;
	if (m_additive) {
		src = D3DBLEND_ONE;
		dest = D3DBLEND_ONE;
	}
	else {
		src = D3DBLEND_SRCALPHA;
		dest = D3DBLEND_INVSRCALPHA;
	}
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, src);
	pDevice->SetRenderState(D3DRS_DESTBLEND, dest);
}


/**
	描画処理
	@param trimRect トリミング領域 (画像左上基準)
	@param center	トリミング領域中心 (トリミング矩形の左上基準)
	@param position	トリミング領域中心の位置 (スクリーン左上基準)
*/
void Sprites::Draw(RECT trimRect, D3DXVECTOR3 center, D3DXVECTOR3 position) {
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetRenderState();
	m_pSprite->Draw(m_pTexture, &trimRect, &center, &position, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	m_pSprite->End();
}

