#include "BillboardString.h"
#include <crtdbg.h>
#include <string.h>
#include <tchar.h>


/**
	コンストラクタ
*/
BillboardString::BillboardString() :
m_curLen(0),
m_isUpdatePosition(true),
m_isUpdate(true),
m_color(0x00ffffff),
m_alpha(0xff),
m_scale_X(1.0f),
m_scale_Y(1.0f),
m_pixelSize(32)
{
	m_basePos.x = 0;
	m_basePos.y = 0;

	memset(m_faceName, 0, LF_FACESIZE);
	SetFont(_T("ＭＳ ゴシック"));
}


/**
	デストラクタ
*/
BillboardString::~BillboardString() {
	size_t sz = m_strAry.size(), i;
	for (i = 0; i < sz; i++) {
		delete m_strAry[i];
	}
}


/**
	文字列登録
	@param str	文字列
*/
void BillboardString::RegistString(const TCHAR* str) {
	// 文字数チェックからBillboardCharオブジェクト配列を手配
	unsigned int len, i;
	unsigned int updateCounter = 0;
#if _UNICODE
	len = (unsigned int)wcslen(str), i;
	if (m_curLen < len) {
		for (i = m_curLen; i < len; i++) m_strAry.push_back(new BillboardChar);
	}
	m_curLen = len;

	for (i = 0; i < m_curLen; i++) {
		if (m_strAry[i]->RegistChar(str + i) != BillboardChar::Regist_SameChar) {
			++updateCounter;
		}
	}
#else
	// マルチ文字の場合は文字解析が必要です
	unsigned int counter = 0;
	len = (unsigned int)strlen(str);
	for (i = 0; i < len; i++)
	{
		BillboardChar* bc;
		if (counter < m_CurLen) {
			bc = m_strAry[counter];
		}
		else {
			bc = new BillboardChar();
			m_strAry.push_back(bc);
		}

		if (p->RegistChar(str + i) != BillboardChar::Regist_SameChar) {
			++updateCounter;
		}

		if (IsDBCSLeadByte(str[i])) {
			++i;
		}
		++counter;
	}
	m_curLen = counter;
#endif

	// 文字の変更があった場合は更新し直す
	if (updateCounter > 0) {
		m_isUpdate = true;
		m_isUpdatePosition = true;
	}
}


/**
	位置関係更新
*/
void BillboardString::UpdatePositions() {
	if (m_curLen == 0) return;
	m_strAry[0]->SetPosition(m_basePos.x, m_basePos.y);
	size_t i;
	for (i = 1; i < m_curLen; i++) {
		const float x = m_strAry[i - 1]->GetRightPos();
		const float y = m_basePos.y;
		m_strAry[i]->SetPosition(x, y);
	}
}

/**
	フォント文字サイズ指定
	@param size	フォント文字サイズ
*/
bool BillboardString::SetMaxPixelSize(unsigned int size) {
	if (m_pixelSize == size) return true;	// 同じサイズなので更新しない
	m_pixelSize = size;
	m_isUpdatePosition = true;
	m_isUpdate = true;
	return false;
}


/**
	フォントスケール指定
	@param xs	フォントスケールx
	@param ys	フォントスケールy
*/
void BillboardString::SetScale(float xs, float ys) {
	if (m_scale_X != xs || m_scale_Y != ys) {
		m_scale_X = xs;
		m_scale_Y = ys;
		m_isUpdatePosition = true;
		m_isUpdate = true;
	}
}


/**
	位置指定
	@param x	x座標
	@param y	y座標
*/
void BillboardString::SetPosition(float x, float y) {
	if (m_basePos.x != x || m_basePos.y != y) {
		m_basePos.x = x;
		m_basePos.y = y;
		m_isUpdatePosition = true;
	}
}


/**
	フォント指定
	@param faceName	フォント
*/
bool BillboardString::SetFont(const TCHAR* faceName) {
	//	同じフォント名が指定されているので更新しない
	if (_tcscmp(m_faceName, faceName) == 0) return true;
	_tcsncpy(m_faceName, faceName, LF_FACESIZE - 1);
	m_isUpdatePosition = true;
	m_isUpdate = true;
	return true;
}


/**
	アルファ値指定
	@param alpha	アルファ値
*/
void BillboardString::SetAlpha(int alpha) {
	if (alpha >= 256)
		alpha = 255;
	if (alpha <= 0)
		alpha = 0;
	if (m_alpha != alpha) {
		m_alpha = alpha;
		m_isUpdate = true;
	}
}


/**
	文字のベースカラー指定
	@param color	文字カラー
*/
void BillboardString::SetColor(DWORD color) {
	if (m_color == color) return;
	m_color = color & 0x00ffffff;
	m_isUpdate = true;
}


/**
	更新
*/
void BillboardString::Update() {
	size_t i;
	for (i = 0; i < m_curLen; i++) {
		m_strAry[i]->SetColor(m_color);
		m_strAry[i]->SetAlpha(m_alpha);
		m_strAry[i]->SetFont(m_faceName);
		m_strAry[i]->SetScale(m_scale_X, m_scale_Y);
		m_strAry[i]->SetMaxPixelSize(m_pixelSize);
		m_strAry[i]->Update();
	}
}


/**
	描画
*/
bool BillboardString::Draw() {
	// 更新が必要な場合は全文字を更新する
	if (m_isUpdate) {
		Update();
		m_isUpdate = false;
	}

	// 位置更新が必要な場合に更新する
	if (m_isUpdatePosition) {
		UpdatePositions();
		m_isUpdatePosition = false;
	}

	size_t i;
	for (i = 0; i < m_curLen; i++) {
		m_strAry[i]->Draw();
	}
	return true;
}
