#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define FVF_2DBILLBOARDVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // 座標変換済み頂点


/// ビルボード文字クラス
class BillboardChar {
public:
	enum Regist {
		Regist_OK,			//! OK
		Regist_SameChar,	//! 同じ文字だった
		Regist_Error,		//! エラー
	};

protected:
	struct BillboardVertex {
		float x, y, z; // 頂点座標 
		float rhw; // 除算数
		DWORD dwColor; // 頂点の色
		float u, v; //　テクスチャ座標 
	};

public:
	enum BILLBOARDCHAR_RESOLUTION {
		BILLBOARDCHAR_RESOLUTION_LOW = 0,
		BILLBOARDCHAR_RESOLUTION_MIDDLE = 1,
		BILLBOARDCHAR_RESOLUTION_HIGH = 2
	};

private:
	// 文字コード変換
	unsigned int TransCharCode(const TCHAR *c);

protected:
	// ビルボードテクスチャ作成
	bool CreateTexture(unsigned int width, unsigned int height);

	// フォントハンドル生成
	bool BillboardChar::CreateFontHandle();

	// フォントビットマップを生成
	DWORD CreateFontBMP(TEXTMETRIC &TM, GLYPHMETRICS &GM, BYTE **outBMP);

	// BMPをテクスチャに適用
	bool ApplyBMPToTex(BYTE* bmp, TEXTMETRIC &TM, GLYPHMETRICS &GM);

	// 文字をテクスチャに刻印
	bool PlotCharToTex();

	// 描画位置更新
	bool UpdateSizeAndPosition(float x, float y);

	// レンダリング準備
	void SetRenderState();

public:
	// コンストラクタ・デストラクタ
	BillboardChar();
	virtual ~BillboardChar();

	// アップデート
	bool Update();

	// 文字登録
	BillboardChar::Regist RegistChar(const TCHAR *c);

	// 基本情報をコピー
	void CopyBaseInfoFrom(BillboardChar* src);

	// 解像度設定
	void SetResolution(BILLBOARDCHAR_RESOLUTION resolution);

	// フォント文字サイズ指定
	bool SetMaxPixelSize(unsigned int size);

	// フォントスケール指定
	void SetScale(float xs, float ys);

	// 回転角度指定
	void SetAngle(float angle);

	// 位置指定
	void SetPosition(float x, float y);

	// フォント指定
	bool SetFont(const TCHAR *FaceName);

	// センター位置指定
	void SetCenterPos(float x, float y);

	// アルファ値指定
	void SetAlpha(int alpha);

	// 文字のベースカラー指定
	void SetColor(DWORD color);

	// フォントテクスチャ取得
	IDirect3DTexture9* GetFontTexture();

	// 表示文字幅取得
	float GetDispWidth();

	// 表示文字右位置取得
	float GetRightPos();

	// 描画
	bool Draw();

private:
	// クラス変数
	static const BillboardVertex m_vertex[4];	// ビルボード頂点

private:
	IDirect3DTexture9* m_pTex;				// 文字テクスチャ
	IDirect3DVertexBuffer9* m_pVertexBuf;	// 頂点バッファ
	TCHAR m_char[2];						// 描画文字
	TCHAR m_lfFaceName[LF_FACESIZE];		// フォント名
	HFONT m_hFont;							// フォントハンドル
	int m_iBmp_W;
	int m_iBmp_H;
	int m_iBmpOfs_x;
	int m_iBmpOfs_y;
	bool m_iSFontHandleRecreate;
	bool m_isUpdate;						// アップデート指示
	int m_texSize;
	unsigned int m_maxPixel;				// フォントサイズ
	DWORD m_color;							// フォントカラー
	float m_xScale;
	float m_yScale;
	float m_angle;
	float m_pos_X, m_pos_Y;
	float m_center_X;
	float m_center_Y;
	int m_R_margin;
	int m_B_margin;
	BYTE m_alpha;
	BILLBOARDCHAR_RESOLUTION m_resolution;
};
