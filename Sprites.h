#pragma once
#include <d3dx9.h>

/// スプライトクラス。
/// 画像ファイルを読込み、シーン中にスプライトとして描画する。
class Sprites {
public:
	Sprites(LPCTSTR filename, bool add);

	~Sprites(void);

	// 描画処理
	void Draw(RECT trimRect, D3DXVECTOR3 center, D3DXVECTOR3 position);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	LPD3DXSPRITE m_pSprite;			// スプライト
	bool m_additive;				// 加算合成か否か
	void SetRenderState();	// ブレンドの設定
};