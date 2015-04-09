#pragma once
#include <d3dx9.h>


typedef LPDIRECT3D9 GraphicsObject;
typedef LPDIRECT3DDEVICE9 GraphicsDevice;

/// グラフィック制御クラス
class Graphics
{
private:
	Graphics();
	~Graphics();
	Graphics(const Graphics& directX);
	Graphics& operator=(const Graphics& directX);
	static GraphicsObject m_pGraphicsObject;
	static GraphicsDevice m_pGraphicsDevice; // Direct3Dデバイスオブジェクト
	static Graphics* m_instance;
	static FLOAT m_fogStart;					// フォグのスタート
	static FLOAT m_fogEnd;					// フォグのエンド
	static void SetFogConfiguration();		// フォグの設定

public:
	// インスタンス取得
	static Graphics* GetInstance();

	// グラフィックの初期化処理
	static HRESULT InitGraphics(HWND hWnd);

	// グラフィックオブジェクトの取得
	GraphicsObject GetGraphicsObject();

	// グラフィックデバイスの取得
	GraphicsDevice GetGraphicsDevice();

	// グラフィックオブジェクトの解放
	static void DestroyGraphicsObject();

	// グラフィックデバイスの解放
	static void DestroyGraphicsDevice();

	/// シーン開始
	static void BeginScene();

	/// シーン終了
	static void EndScene();
};

