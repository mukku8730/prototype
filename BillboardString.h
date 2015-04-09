#pragma once
#include "BillboardChar.h"
#include <vector>


/// �r���{�[�h������N���X
class BillboardString {
protected:
	struct FloatPos {
		float x;
		float y;
	};

protected:
	// �ʒu�֌W�X�V
	void UpdatePositions();

	// �X�V
	void Update();

public:
	BillboardString();
	~BillboardString();

	// ������o�^
	void RegistString(const TCHAR* str);

	// �t�H���g�w��
	bool SetFont(const TCHAR *FaceName);

	// �t�H���g�����T�C�Y�w��
	bool SetMaxPixelSize(unsigned int size);

	// �t�H���g�X�P�[���w��
	void SetScale(float xs, float ys);

	// �ʒu�w��
	void SetPosition(float x, float y);

	// �A���t�@�l�w��
	void SetAlpha(int alpha);

	// �����̃x�[�X�J���[�w��
	void SetColor(DWORD color);

	// �`��
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
