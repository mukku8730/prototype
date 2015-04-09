#pragma once
#include "BillboardChar.h"
#include <vector>


/// ビルボード文字列クラス
class BillboardString {
protected:
	struct FloatPos {
		float x;
		float y;
	};

protected:
	// 位置関係更新
	void UpdatePositions();

	// 更新
	void Update();

public:
	BillboardString();
	~BillboardString();

	// 文字列登録
	void RegistString(const TCHAR* str);

	// フォント指定
	bool SetFont(const TCHAR *FaceName);

	// フォント文字サイズ指定
	bool SetMaxPixelSize(unsigned int size);

	// フォントスケール指定
	void SetScale(float xs, float ys);

	// 位置指定
	void SetPosition(float x, float y);

	// アルファ値指定
	void SetAlpha(int alpha);

	// 文字のベースカラー指定
	void SetColor(DWORD color);

	// 描画
	bool Draw();

protected:
	FloatPos m_basePos;
	DWORD m_color;
	int m_alpha;
	TCHAR m_faceName[LF_FACESIZE];
	float m_scale_X, m_scale_Y;
	unsigned int m_pixelSize;
	bool m_isBlurBG;
	int m_blurSize;
	DWORD m_bgColor;

private:
	unsigned int m_curLen;
	std::vector< BillboardChar* > m_strAry;
	bool m_isUpdatePosition;
	bool m_isUpdate;
};
