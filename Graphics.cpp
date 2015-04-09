#include "Graphics.h"
#include <cassert>
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }


Graphics* Graphics::m_instance = 0;
GraphicsObject Graphics::m_pGraphicsObject = NULL;
GraphicsDevice Graphics::m_pGraphicsDevice = NULL;
FLOAT Graphics::m_fogStart = 150;
FLOAT Graphics::m_fogEnd = 1000;
/**
	コンストラクタ(封印)
*/
Graphics::Graphics() {}

/**
	デストラクタ(封印)
*/
Graphics::~Graphics() {}

/**
	インスタンス取得
	@param インスタンス
*/
Graphics* Graphics::GetInstance() {
	return m_instance;
}

/**
	グラフィックの初期化処理
	@param hWnd	ウインドウハンドル
*/
HRESULT Graphics::InitGraphics(HWND hWnd) {
	if (m_pGraphicsObject != NULL) return E_FAIL;
	// Create the D3D object.
	if (NULL == (m_pGraphicsObject = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	if (m_pGraphicsDevice != NULL) return E_FAIL;
	// Create the D3DDevice
	if (FAILED(m_pGraphicsObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pGraphicsDevice)))
	{
		return E_FAIL;
	}

	// Turn on the zbuffer
	m_pGraphicsDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//SetFogConfiguration();

	return S_OK;
}

/**
	グラフィックオブジェクトの取得
	@return	グラフィックオブジェクト
*/
GraphicsObject Graphics::GetGraphicsObject() {
	if (m_pGraphicsObject != NULL) return m_pGraphicsObject;
	else return NULL;
}

/**
	グラフィックデバイスの取得
	@return	グラフィックデバイス
*/
GraphicsDevice Graphics::GetGraphicsDevice() {
	if (m_pGraphicsDevice != NULL) return m_pGraphicsDevice;
	else return NULL;
}

/**
	グラフィックオブジェクトの解放
*/
void Graphics::DestroyGraphicsObject() {
	SAFE_RELEASE(m_pGraphicsObject);
}

/**
	グラフィックデバイスの解放
*/
void Graphics::DestroyGraphicsDevice() {
	SAFE_RELEASE(m_pGraphicsDevice);
}

/**
	画面を背景色でクリアし、シーンを開始する。描画関数はシーン中に呼び出す
*/
void Graphics::BeginScene() {
	m_pGraphicsDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	if (!SUCCEEDED(m_pGraphicsDevice->BeginScene())) throw TEXT("BeginSceneに失敗しました");
}

/**
	シーンを終了する
*/
void Graphics::EndScene() {
	m_pGraphicsDevice->EndScene();
	m_pGraphicsDevice->Present(NULL, NULL, NULL, NULL);
}


/**
	フォグの設定
*/
void Graphics::SetFogConfiguration() {
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	m_pGraphicsDevice->GetDeviceCaps(&caps);
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE) == 0) {
		if (MessageBox(0, TEXT("ピクセルフォグが使えない可能性があります。続行しますか?"), TEXT("質問"), MB_ABORTRETRYIGNORE) == IDABORT) throw TEXT("フォグ設定に失敗しました");
	}
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(150, 255, 255, 255));
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fogStart));
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fogEnd));
}
