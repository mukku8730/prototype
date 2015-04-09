#include "BillboardString.h"
#include <crtdbg.h>
#include <string.h>
#include <tchar.h>


/**
	�R���X�g���N�^
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
	SetFont(_T("�l�r �S�V�b�N"));
}


/**
	�f�X�g���N�^
*/
BillboardString::~BillboardString() {
	size_t sz = m_strAry.size(), i;
	for (i = 0; i < sz; i++) {
		delete m_strAry[i];
	}
}


/**
	������o�^
	@param str	������
*/
void BillboardString::RegistString(const TCHAR* str) {
	// �������`�F�b�N����BillboardChar�I�u�W�F�N�g�z�����z
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
	// �}���`�����̏ꍇ�͕�����͂��K�v�ł�
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

	// �����̕ύX���������ꍇ�͍X�V������
	if (updateCounter > 0) {
		m_isUpdate = true;
		m_isUpdatePosition = true;
	}
}


/**
	�ʒu�֌W�X�V
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
	�t�H���g�����T�C�Y�w��
	@param size	�t�H���g�����T�C�Y
*/
bool BillboardString::SetMaxPixelSize(unsigned int size) {
	if (m_pixelSize == size) return true;	// �����T�C�Y�Ȃ̂ōX�V���Ȃ�
	m_pixelSize = size;
	m_isUpdatePosition = true;
	m_isUpdate = true;
	return false;
}


/**
	�t�H���g�X�P�[���w��
	@param xs	�t�H���g�X�P�[��x
	@param ys	�t�H���g�X�P�[��y
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
	�ʒu�w��
	@param x	x���W
	@param y	y���W
*/
void BillboardString::SetPosition(float x, float y) {
	if (m_basePos.x != x || m_basePos.y != y) {
		m_basePos.x = x;
		m_basePos.y = y;
		m_isUpdatePosition = true;
	}
}


/**
	�t�H���g�w��
	@param faceName	�t�H���g
*/
bool BillboardString::SetFont(const TCHAR* faceName) {
	//	�����t�H���g�����w�肳��Ă���̂ōX�V���Ȃ�
	if (_tcscmp(m_faceName, faceName) == 0) return true;
	_tcsncpy(m_faceName, faceName, LF_FACESIZE - 1);
	m_isUpdatePosition = true;
	m_isUpdate = true;
	return true;
}


/**
	�A���t�@�l�w��
	@param alpha	�A���t�@�l
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
	�����̃x�[�X�J���[�w��
	@param color	�����J���[
*/
void BillboardString::SetColor(DWORD color) {
	if (m_color == color) return;
	m_color = color & 0x00ffffff;
	m_isUpdate = true;
}


/**
	�X�V
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
	�`��
*/
bool BillboardString::Draw() {
	// �X�V���K�v�ȏꍇ�͑S�������X�V����
	if (m_isUpdate) {
		Update();
		m_isUpdate = false;
	}

	// �ʒu�X�V���K�v�ȏꍇ�ɍX�V����
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
