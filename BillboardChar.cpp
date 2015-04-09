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


// �𑜓x�n�b�V��
unsigned int resolutionHash_g[] = {
	GGO_GRAY2_BITMAP,
	GGO_GRAY4_BITMAP,
	GGO_GRAY8_BITMAP
};

// ����\�n�b�V��
unsigned int gLevel[] = { 5, 17, 65 };

// �ׂ���O�a�l�Z�o
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

	// ���_�o�b�t�@�̐���
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->CreateVertexBuffer(sizeof(BillboardVertex) * 4, D3DUSAGE_WRITEONLY, FVF_2DBILLBOARDVERTEX, D3DPOOL_MANAGED, &m_pVertexBuf, NULL);
	assert(m_pVertexBuf);
	void *pData;
	if (SUCCEEDED(m_pVertexBuf->Lock(0, sizeof(BillboardVertex) * 4, (void**)&pData, 0))) {
		memcpy(pData, m_vertex, sizeof(BillboardVertex) * 4);
		m_pVertexBuf->Unlock();
	}

	memset(m_lfFaceName, 0, LF_FACESIZE);
	SetFont(_T("�l�r ����"));
	SetMaxPixelSize(m_maxPixel);
}

BillboardChar::~BillboardChar() {
	if (m_pVertexBuf) m_pVertexBuf->Release();
	if (m_hFont) DeleteObject(m_hFont);
	if (m_pTex) m_pTex->Release();
}

// �����o�^
BillboardChar::Regist BillboardChar::RegistChar(const TCHAR *c) {
	_ASSERT(c);
	if (!c)
		return Regist_Error;
#if _UNICODE
	// unicode�̏ꍇ�P�����
	if (m_char[0] == c[0])
		return Regist_SameChar;

	m_char[0] = c[0];
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if (IsDBCSLeadByte(*c)) {

		if (m_char[0] == c[0] && m_char[1] == c[1])
			return Regist_SameChar;	// ���������Ȃ̂ōX�V���Ȃ�

		m_char[0] = c[0];
		m_char[1] = c[1];
	}
	else {
		if (m_char[0] == c[0])
			return Regist_SameChar;
		m_char[0] = c[0];
	}
#endif

	// �A�b�v�f�[�g
	m_isUpdate = true;
	return Regist_OK;
}

// ��{�����R�s�[
void BillboardChar::CopyBaseInfoFrom(BillboardChar* src) {
	// �\�L�����ȊO�̏�����������R�s�[
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

// �𑜓x�ݒ�
void BillboardChar::SetResolution(BILLBOARDCHAR_RESOLUTION resolution) {
	m_resolution = resolution;
}

// �����T�C�Y�w��
bool BillboardChar::SetMaxPixelSize(unsigned int size) {
	if (size == 0)
		return false;
	if (m_maxPixel != size) {
		// �����T�C�Y�ύX
		m_maxPixel = size;
		m_isUpdate = true;
		m_iSFontHandleRecreate = true;
	}
	return true;
}

// �t�H���g�X�P�[���w��
void BillboardChar::SetScale(float xs, float ys) {
	m_xScale = xs;
	m_yScale = ys;
}

// ��]�p�x�w��
void BillboardChar::SetAngle(float angle) {
	m_angle = angle;
}

// �ʒu�w��
void BillboardChar::SetPosition(float x, float y) {
	m_pos_X = x;
	m_pos_Y = y;
}

// �t�H���g�ύX
bool BillboardChar::SetFont(const TCHAR *faceName) {
	if (_tcscmp(m_lfFaceName, faceName) == 0)
		return true;		//	�����t�H���g�����w�肳��Ă���̂ōX�V���Ȃ�
	_tcsncpy(m_lfFaceName, faceName, LF_FACESIZE - 1);
	m_isUpdate = true;
	m_iSFontHandleRecreate = true;
	return true;
}

// �Z���^�[�ʒu�w��
void BillboardChar::SetCenterPos(float x, float y) {
	m_center_X = x;
	m_center_Y = y;
}

// �A���t�@�l�w��
void BillboardChar::SetAlpha(int alpha) {
	if (alpha >= 256)
		alpha = 255;
	if (alpha <= 0)
		alpha = 0;
	m_alpha = alpha;
}

// �����̃x�[�X�J���[�w��
void BillboardChar::SetColor(DWORD color) {
	m_color = color;
}

// �t�H���g�e�N�X�`���擾
IDirect3DTexture9* BillboardChar::GetFontTexture() {
	if (m_pTex) m_pTex->AddRef();
	return m_pTex;
}

// �r���{�[�h�e�N�X�`���쐬
bool BillboardChar::CreateTexture(unsigned int width, unsigned int height) {
	// �e�N�X�`���쐬
	IDirect3DTexture9 *tmpTex = 0;
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	if (FAILED(pDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tmpTex, NULL))){
		if (FAILED(pDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tmpTex, NULL))){
			// �e�N�X�`���쐬���s
			assert(0);
			return false;
		}
	}

	if (m_pTex) m_pTex->Release();
	m_pTex = tmpTex;

	return true;
}

// �t�H���g�n���h������
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

// �����R�[�h�ϊ�
unsigned int BillboardChar::TransCharCode(const TCHAR *c) {
#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
	return (UINT)m_char[0];
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if (IsDBCSLeadByte(m_char[0]))
		return (BYTE)m_char[0] << 8 | (BYTE)m_char[1];
	return m_char[0];
#endif
}

// �t�H���g�r�b�g�}�b�v�𐶐�
DWORD BillboardChar::CreateFontBMP(TEXTMETRIC &TM, GLYPHMETRICS &GM, BYTE **outBMP)
{
	// �f�o�C�X�R���e�L�X�g�擾
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont);

	// �����R�[�h�擾
	UINT code = TransCharCode(m_char);

	GetTextMetrics(hdc, &TM);
	CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
	DWORD size = GetGlyphOutline(hdc, code, resolutionHash_g[m_resolution], &GM, 0, NULL, &Mat);

	if (size != 0)
		*outBMP = new BYTE[size];

	GetGlyphOutline(hdc, code, resolutionHash_g[m_resolution], &GM, size, *outBMP, &Mat);

	// ���ƍ����A�I�t�Z�b�g�l�A�}�[�W�����Z�o
	m_iBmpOfs_x = GM.gmptGlyphOrigin.x;
	m_iBmp_W = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	m_R_margin = GM.gmCellIncX - GM.gmptGlyphOrigin.x - GM.gmBlackBoxX;
	m_iBmpOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	m_iBmp_H = GM.gmBlackBoxY;
	m_B_margin = TM.tmHeight - GM.gmptGlyphOrigin.y - GM.gmBlackBoxY;

	// �T�C�Y0�̕����i�󔒁j�̏ꍇ��
	// ��Ŏ擾�����r�b�g�}�b�v�̕��ƍ����Ԃ񂾂�
	// ��������^����
	if (!size) {
		*outBMP = new BYTE[m_iBmp_W * m_iBmp_H];
		memset(*outBMP, 0x00, m_iBmp_W * m_iBmp_H);
	}

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);

	return size;
}

// BMP���e�N�X�`���ɓK�p
bool BillboardChar::ApplyBMPToTex(BYTE* bmp, TEXTMETRIC &TM, GLYPHMETRICS &GM) {
	_ASSERT(bmp);
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD))){
		if (FAILED(m_pTex->LockRect(0, &LockedRect, NULL, 0))){
			// ���b�N���s
			assert(0);
			return false;
		}
	}

	// �e�N�X�`��������
	memset(LockedRect.pBits, 0, LockedRect.Pitch * m_iBmp_H);	// �e�N�X�`����^������

	// iBmpOfs_x, iBmpOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K
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

// �������e�N�X�`���ɍ���
bool BillboardChar::PlotCharToTex() {
	// �t�H���g�n���h������
	if (m_iSFontHandleRecreate)
		if (!CreateFontHandle())
			return false;

	// �t�H���g�r�b�g�}�b�v����
	TEXTMETRIC TM;
	GLYPHMETRICS GM;
	BYTE *bmp = 0;
	CreateFontBMP(TM, GM, &bmp);

	// �e�N�X�`���쐬
	CreateTexture(m_iBmp_W, m_iBmp_H);

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
	ApplyBMPToTex(bmp, TM, GM);

	delete[] bmp;

	return true;
}

// �A�b�v�f�[�g
bool BillboardChar::Update() {
	if (m_char && m_isUpdate == true)
		PlotCharToTex();

	m_isUpdate = false;
	m_iSFontHandleRecreate = false;

	return true;
}

// �`��ʒu�X�V
bool BillboardChar::UpdateSizeAndPosition(float x, float y) {
	int i;
	BillboardVertex *pData;
	if (FAILED(m_pVertexBuf->Lock(0, sizeof(BillboardVertex) * 4, (void**)&pData, 0)))
		return false;

	float px, py, scx, scy;
	for (i = 0; i < 4; i++) {
		// ���_�ό`
		scx = m_xScale * m_iBmp_W;
		scy = m_xScale * m_iBmp_H;
		px = m_vertex[i].x * scx;
		py = m_vertex[i].y * scy;

		// ���S�_��]
		float tmp = px;
		px = cos(m_angle) * px - sin(m_angle) * py;
		py = sin(m_angle) * tmp + cos(m_angle) * py;

		// �ʒu�ύX
		pData[i].x = px + x + m_xScale * m_iBmpOfs_x - scx * m_center_X;
		pData[i].y = py + y + m_yScale * m_iBmpOfs_y - scy * m_center_Y;
		pData[i].z = 0.0f;
		pData[i].rhw = 1.0f;

		// �e�N�X�`��UV�𕶎��̍ő�T�C�Y/�e�N�X�`���T�C�Y�ɍ��킹��
		pData[i].dwColor = m_color | (m_alpha << 24);
	}

	// UV�̍ő�l��1/�s�N�Z���T�C�Y�������g��
	pData[0].u = 1.0f + 1.0f / m_iBmp_W;
	pData[1].u = 1.0f + 1.0f / m_iBmp_W;
	pData[1].v = 1.0f + 1.0f / m_iBmp_H;
	pData[3].v = 1.0f + 1.0f / m_iBmp_H;

	m_pVertexBuf->Unlock();
	return true;
}

// �`��
bool BillboardChar::Draw() {

	// �A�b�v�f�[�g���K�v���`�F�b�N
	if (m_isUpdate) {
		if (!Update())
			return false;
	}

	// �`��T�C�Y�ƈʒu�̍X�V
	UpdateSizeAndPosition(m_pos_X, m_pos_Y);

	// �`��iBeginScene���Ă΂�Ă���O��j
	SetRenderState();
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(BillboardVertex));
	pDevice->SetFVF(FVF_2DBILLBOARDVERTEX);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	return true;
}

void BillboardChar::SetRenderState()
{
	// �e�N�X�`���Z�b�g
	GraphicsDevice pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	pDevice->SetTexture(0, m_pTex);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // �|���̃��l�𗘗p

	pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x00000000);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

	// �����_�����O�X�e�[�g
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// �\���������擾
float BillboardChar::GetDispWidth() {
	return (m_iBmpOfs_x + m_iBmp_W) * m_xScale;
}

// �\�������E�ʒu�擾
float BillboardChar::GetRightPos() {
	return (m_iBmpOfs_x + m_iBmp_W + m_R_margin) * m_xScale + m_pos_X;
}
