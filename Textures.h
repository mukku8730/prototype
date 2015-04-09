#pragma once
#include <d3dx9.h>


/// テクスチャ管理クラス（シングルトン）
class Textures
{
private:
	Textures();
	~Textures();
	Textures(const Textures& texture);
	Textures& operator=(const Textures& texture);
	static Textures* m_instance;
	static LPDIRECT3DTEXTURE9*	m_pMeshTextures; // テクスチャ配列
	static const DWORD m_textureIdx;

public:
	// インスタンス取得
	static Textures* GetInstance();

	// テクスチャ情報の読み込み
	static HRESULT LoadTextures();

	// テクスチャ情報を破棄
	static void DestroyTextures();

	// 指定されたIDのテクスチャを取得
	LPDIRECT3DTEXTURE9 GetTexture(DWORD TX_id);
};

