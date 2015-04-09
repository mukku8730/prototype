#pragma once
#include "Vector3.h"

/// ファイルから読込んだメッシュ
class FileMesh {
private:
	LPD3DXMESH			m_pMesh;			// メッシュ
	D3DMATERIAL9*		m_pMeshMaterials;	// マテリアル配列
	LPDIRECT3DTEXTURE9*	m_pMeshTextures;	// テクスチャ配列
	DWORD				m_dwNumMaterials;	// マテリアル・テクスチャ配列の大きさ
	DWORD				m_textureIdx;		// テクスチャファイルが指定されている添字

public:
	FileMesh(LPCTSTR filename);
	~FileMesh();

	// テクスチャを設定
	HRESULT SetTexture(int janpaiID);

	// 描画（拡大なし）
	void Draw(const Vector3& position, const Matrix16& attitude);

	// 描画（拡大あり）
	void Draw(const Vector3& position, const Matrix16& attitude, const Vector3& scale);
};
