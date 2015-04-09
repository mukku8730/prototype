#include "Textures.h"
#include "Graphics.h"
#include <cassert>
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

Textures* Textures::m_instance = 0;
LPDIRECT3DTEXTURE9*	Textures::m_pMeshTextures = NULL;
DWORD const Textures::m_textureIdx = 41;

/**
	コンストラクタ（封印）
*/
Textures::Textures()
{
}

/**
	デストラクタ（封印）
*/
Textures::~Textures()
{
}


/**
	テクスチャ情報の読み込み
*/
HRESULT Textures::LoadTextures() {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_textureIdx];
	assert(m_pMeshTextures != NULL);
	for (DWORD i = 0; i < (DWORD)m_textureIdx; ++i) m_pMeshTextures[i] = NULL;

	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man1-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[0]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man2-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[1]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man3-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[2]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man4-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[3]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man5-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[4]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man6-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[5]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man7-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[6]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man8-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[7]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/man9-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[8]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin1-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[9]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin2-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[10]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin3-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[11]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin4-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[12]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin5-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[13]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin6-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[14]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin7-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[15]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin8-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[16]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/pin9-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[17]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou1-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[18]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou2-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[19]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou3-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[20]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou4-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[21]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou5-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[22]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou6-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[23]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou7-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[24]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou8-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[25]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/sou9-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[26]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji1-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[27]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji2-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[28]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji3-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[29]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji4-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[30]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji5-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[31]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji6-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[32]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/ji7-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[33]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/aka1-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[34]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/aka2-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[35]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/aka3-66-90-l.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[36]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/tennbou-000.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[37]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/tennbou-001.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[38]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/tennbou-002.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[39]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/tennbou-003.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[40]))) throw E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, TEXT("Material/yellow.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[41]))) throw E_FAIL;


	return S_OK;
}


/**
	インスタンス取得
	@return インスタンス
*/
Textures* Textures::GetInstance() {
	return m_instance;
}


/**
	テクスチャ情報を破棄
*/
void Textures::DestroyTextures() {
	for (int i = 0; i < m_textureIdx; ++i) {
		SAFE_RELEASE(m_pMeshTextures[i]);
	}
	SAFE_DELETE(m_pMeshTextures);
}


/**
	指定されたIDのテクスチャを取得
	@param id	指定されたID
	@return		指定されたIDのテクスチャ
*/
LPDIRECT3DTEXTURE9 Textures::GetTexture(DWORD TX_id) {
	return m_pMeshTextures[TX_id - 1]; // 配列の添字にアクセスするため(-1)
}
