#pragma warning ( disable : 4996 )
#include "BillboardString.h"
#include "Graphics.h"
#include <crtdbg.h>
#include <tchar.h>
#include <stdio.h>
#include <cassert>


const BillboardChar::BillboardVertex BillboardChar::m_vertex[4] = {
		{ 0.5f, -0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
		{ -0.5f, -0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
		{ -0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f }
};


// 解像度ハッシュ
unsigned int resolutionHash_g[] = {
	GGO_GRAY2_BITMAP,
	GGO_GRAY4_BITMAP,
	GGO_GRAY8_BITMAP
};

// 分解能ハッシュ
unsigned int gLevel[] = { 5, 17, 65 };

// べき乗飽和値算出
unsigned int PowerSaturation(unsigned int val) {
	val -= 1;
	BYTE S1 = (val >> 16) != 0;
	val >>= 16 * S1;
	BYTE S2 = (val >> 8) != 0;
	val >>= 8 * S2;
	BYTE S3 = (val >> 4) != 0;
	val >>= 4 * S3;
	BYTE S4 = (val >> 2) != 0;
	val >>= 2 * S4;
	BYTE S5 = (val >> 1) != 0;
	val >>= S5;
	BYTE S6 = val;
	return 1 << (16 * S1 + 8 * S2 + 4 * S3 + 2 * S4 + S5 + S6);
}

BillboardChar::BillboardChar() :
m_pTex(0),
m_pVertexBuf(0),
m_maxPixel(32),
m_isUpdate(true),
m_hFont(0),
m_xScale(1.0f),
m_yScale(1.0f),
m_iSFontHandleRecreate(true),
m_texSize(0),
m_angle(0),
m_pos_X(0),
m_pos_Y(0),
m_color(0x00ffffff),
m_alpha(0xff),
m_center_X(-0.5f),
m_center_Y(-0.5f),
m_iBmpOfs_x(0),
m_iBmpOfs_y(0),
m_iBmp_W(0),
m_iBmp_H(0),
m_R_margin(0),
m_B_margin(0),
m_resolution(BILLBOARDCHAR_RESOLUTION_MIDDLE)
{
	m_char[0] = 0;
	m_char[1] = 0;

	// 頂点バッファの生成
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->CreateVertexBuffer(sizeof(BillboardVertex) * 4, D3DUSAGE_WRITEONLY, FVF_2DBILLBOARDVERTEX, D3DPOOL_MANAGED, &m_pVertexBuf, NULL);
	assert(m_pVertexBuf);
	void *pData;
	if (SUCCEEDED(m_pVertexBuf->Lock(0, sizeof(BillboardVertex) * 4, (void**)&pData, 0))) {
		memcpy(pData, m_vertex, sizeof(BillboardVertex) * 4);
		m_pVertexBuf->Unlock();
	}

	memset(m_lfFaceName, 0, LF_FACESIZE);
	SetFont(_T("ＭＳ 明朝"));
	SetMaxPixelSize(m_maxPixel);
}

BillboardChar::~BillboardChar() {
	if (m_pVertexBuf) m_pVertexBuf->Release();
	if (m_hFont) DeleteObject(m_hFont);
	if (m_pTex) m_pTex->Release();
}

// 文字登録
BillboardChar::Regist BillboardChar::RegistChar(const TCHAR *c) {
	_ASSERT(c);
	if (!c)
		return Regist_Error;
#if _UNICODE
	// unicodeの場合単純代入
	if (m_char[0] == c[0])
		return Regist_SameChar;

	m_char[0] = c[0];
#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if (IsDBCSLeadByte(*c)) {

		if (m_char[0] == c[0] && m_char[1] == c[1])
			return Regist_SameChar;	// 同じ文字なので更新しない

		m_char[0] = c[0];
		m_char[1] = c[1];
	}
	else {
		if (m_char[0] == c[0])
			return Regist_SameChar;
		m_char[0] = c[0];
	}
#endif

	// アップデート
	m_isUpdate = true;
	return Regist_OK;
}

// 基本情報をコピー
void BillboardChar::CopyBaseInfoFrom(BillboardChar* src) {
	// 表記文字以外の情報を引数からコピー
	SetAlpha(src->m_alpha);
	SetAngle(src->m_angle);
	SetCenterPos(src->m_center_X, src->m_center_Y);
	SetColor(src->m_color);
	SetFont(src->m_lfFaceName);
	SetMaxPixelSize(src->m_maxPixel);
	SetPosition(src->m_pos_X, src->m_pos_Y);
	SetScale(src->m_xScale, src->m_yScale);
	SetResolution(src->m_resolution);
}

// 解像度設定
void BillboardChar::SetResolution(BILLBOARDCHAR_RESOLUTION resolution) {
	m_resolution = resolution;
}

// 文字サイズ指定
bool BillboardChar::SetMaxPixelSize(unsigned int size) {
	if (size == 0)
		return false;
	if (m_maxPixel != size) {
		// 文字サイズ変更
		m_maxPixel = size;
		m_isUpdate = true;
		m_iSFontHandleRecreate = true;
	}
	return true;
}

// フォントスケール指定
void BillboardChar::SetScale(float xs, float ys) {
	m_xScale = xs;
	m_yScale = ys;
}

// 回転角度指定
void BillboardChar::SetAngle(float angle) {
	m_angle = angle;
}

// 位置指定
void BillboardChar::SetPosition(float x, float y) {
	m_pos_X = x;
	m_pos_Y = y;
}

// フォント変更
bool BillboardChar::SetFont(const TCHAR *faceName) {
	if (_tcscmp(m_lfFaceName, faceName) == 0)
		return true;		//	同じフォント名が指定されているので更新しない
	_tcsncpy(m_lfFaceName, faceName, LF_FACESIZE - 1);
	m_isUpdate = true;
	m_iSFontHandleRecreate = true;
	return true;
}

// センター位置指定
void BillboardChar::SetCenterPos(float x, float y) {
	m_center_X = x;
	m_center_Y = y;
}

// アルファ値指定
void BillboardChar::SetAlpha(int alpha) {
	if (alpha >= 256)
		alpha = 255;
	if (alpha <= 0)
		alpha = 0;
	m_alpha = alpha;
}

// 文字のベースカラー指定
void BillboardChar::SetColor(DWORD color) {
	m_color = color;
}

// フォントテクスチャ取得
IDirect3DTexture9* BillboardChar::GetFontTexture() {
	if (m_pTex) m_pTex->AddRef();
	return m_pTex;
}

// ビルボードテクスチャ作成
bool BillboardChar::CreateTexture(unsigned int width, unsigned int height) {
	// テクスチャ作成
	IDirect3DTexture9 *tmpTex = 0;
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	if (FAILED(pDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tmpTex, NULL))){
		if (FAILED(pDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tmpTex, NULL))){
			// テクスチャ作成失敗
			assert(0);
			return false;
		}
	}

	if (m_pTex) m_pTex->Release();
	m_pTex = tmpTex;

	return true;
}

// フォントハンドル生成
bool BillboardChar::CreateFontHandle() {
	LOGFONT lf = { m_maxPixel, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SCRIPT };
	_tcscpy(lf.lfFaceName, m_lfFaceName);
	lf.lfWeight = 500;
	HFONT tmpFont = CreateFontIndirect(&lf);
	if (!tmpFont) {
		_ASSERT(0);
		return false;
	}
	DeleteObject(m_hFont);
	m_hFont = tmpFont;
	return true;
}

// 文字コード変換
unsigned int BillboardChar::TransCharCode(const TCHAR *c) {
#if _UNICODE
	// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
	return (UINT)m_char[0];
#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if (IsDBCSLeadByte(m_char[0]))
		return (BYTE)m_char[0] << 8 | (BYTE)m_char[1];
	return m_char[0];
#endif
}

// フォントビットマップを生成
DWORD BillboardChar::CreateFontBMP(TEXTMETRIC &TM, GLYPHMETRICS &GM, BYTE **outBMP)
{
	// デバイスコンテキスト取得
	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont);

	// 文字コード取得
	UINT code = TransCharCode(m_char);

	GetTextMetrics(hdc, &TM);
	CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
	DWORD size = GetGlyphOutline(hdc, code, resolutionHash_g[m_resolution], &GM, 0, NULL, &Mat);

	if (size != 0)
		*outBMP = new BYTE[size];

	GetGlyphOutline(hdc, code, resolutionHash_g[m_resolution], &GM, size, *outBMP, &Mat);

	// 幅と高さ、オフセット値、マージンを算出
	m_iBmpOfs_x = GM.gmptGlyphOrigin.x;
	m_iBmp_W = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	m_R_margin = GM.gmCellIncX - GM.gmptGlyphOrigin.x - GM.gmBlackBoxX;
	m_iBmpOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	m_iBmp_H = GM.gmBlackBoxY;
	m_B_margin = TM.tmHeight - GM.gmptGlyphOrigin.y - GM.gmBlackBoxY;

	// サイズ0の文字（空白）の場合は
	// 上で取得したビットマップの幅と高さぶんだけ
	// メモリを与える
	if (!size) {
		*outBMP = new BYTE[m_iBmp_W * m_iBmp_H];
		memset(*outBMP, 0x00, m_iBmp_W * m_iBmp_H);
	}

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);

	return size;
}

// BMPをテクスチャに適用
bool BillboardChar::ApplyBMPToTex(BYTE* bmp, TEXTMETRIC &TM, GLYPHMETRICS &GM) {
	_ASSERT(bmp);
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD))){
		if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, 0))){
			// ロック失敗
			assert(0);
			return false;
		}
	}

	// テクスチャ初期化
	memset(LockedRect.pBits, 0, LockedRect.Pitch * m_iBmp_H);	// テクスチャを真透明に

	// iBmpOfs_x, iBmpOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階
	int Level = gLevel[m_resolution];
	int x, y;
	DWORD Alpha, Color;
	for (y = 0; y < m_iBmp_H; y++) {
		for (x = 0; x < m_iBmp_W; x++) {
			Alpha = (255 * bmp[x + m_iBmp_W * y]) / (Level - 1);
#if _DEBUG
			Color = 0x00ffffff | (Alpha << 24) | 0x33000000;
#else
			Color = 0x00ffffff | (Alpha << 24);
#endif
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
		}
	}
	m_pTex->UnlockRect(0);
	return true;
}

// 文字をテクスチャに刻印
bool BillboardChar::PlotCharToTex() {
	// フォントハンドル生成
	if (m_iSFontHandleRecreate)
		if (!CreateFontHandle())
			return false;

	// フォントビットマップ生成
	TEXTMETRIC TM;
	GLYPHMETRICS GM;
	BYTE *bmp = 0;
	CreateFontBMP(TM, GM, &bmp);

	// テクスチャ作成
	CreateTexture(m_iBmp_W, m_iBmp_H);

	// テクスチャにフォントビットマップ書き込み
	ApplyBMPToTex(bmp, TM, GM);

	delete[] bmp;

	return true;
}

// アップデート
bool BillboardChar::Update() {
	if (m_char && m_isUpdate == true)
		PlotCharToTex();

	m_isUpdate = false;
	m_iSFontHandleRecreate = false;

	return true;
}

// 描画位置更新
bool BillboardChar::UpdateSizeAndPosition(float x, float y) {
	int i;
	BillboardVertex *pData;
	if (FAILED(m_pVertexBuf->Lock(0, sizeof(BillboardVertex) * 4, (void**)&pData, 0)))
		return false;

	float px, py, scx, scy;
	for (i = 0; i < 4; i++) {
		// 頂点変形
		scx = m_xScale * m_iBmp_W;
		scy = m_xScale * m_iBmp_H;
		px = m_vertex[i].x * scx;
		py = m_vertex[i].y * scy;

		// 中心点回転
		float tmp = px;
		px = cos(m_angle) * px - sin(m_angle) * py;
		py = sin(m_angle) * tmp + cos(m_angle) * py;

		// 位置変更
		pData[i].x = px + x + m_xScale * m_iBmpOfs_x - scx * m_center_X;
		pData[i].y = py + y + m_yScale * m_iBmpOfs_y - scy * m_center_Y;
		pData[i].z = 0.0f;
		pData[i].rhw = 1.0f;

		// テクスチャUVを文字の最大サイズ/テクスチャサイズに合わせる
		pData[i].dwColor = m_color | (m_alpha << 24);
	}

	// UVの最大値を1/ピクセルサイズ分だけ拡張
	pData[0].u = 1.0f + 1.0f / m_iBmp_W;
	pData[1].u = 1.0f + 1.0f / m_iBmp_W;
	pData[1].v = 1.0f + 1.0f / m_iBmp_H;
	pData[3].v = 1.0f + 1.0f / m_iBmp_H;

	m_pVertexBuf->Unlock();
	return true;
}

// 描画
bool BillboardChar::Draw() {

	// アップデートが必要かチェック
	if (m_isUpdate) {
		if (!Update())
			return false;
	}

	// 描画サイズと位置の更新
	UpdateSizeAndPosition(m_pos_X, m_pos_Y);

	// 描画（BeginSceneが呼ばれている前提）
	SetRenderState();
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(BillboardVertex));
	pDevice->SetFVF(FVF_2DBILLBOARDVERTEX);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	return true;
}

void BillboardChar::SetRenderState()
{
	// テクスチャセット
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->SetTexture(0, m_pTex);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // 板ポリのα値を利用

	pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x00000000);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

	// レンダリングステート
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// 表示文字幅取得
float BillboardChar::GetDispWidth() {
	return (m_iBmpOfs_x + m_iBmp_W) * m_xScale;
}

// 表示文字右位置取得
float BillboardChar::GetRightPos() {
	return (m_iBmpOfs_x + m_iBmp_W + m_R_margin) * m_xScale + m_pos_X;
}
