#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define FVF_2DBILLBOARDVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // ���W�ϊ��ςݒ��_


/// �r���{�[�h�����N���X
class BillboardChar {
public:
	enum Regist {
		Regist_OK,			//! OK
		Regist_SameChar,	//! ��������������
		Regist_Error,		//! �G���[
	};

protected:
	struct BillboardVertex {
		float x, y, z; // ���_���W 
		float rhw; // ���Z��
		DWORD dwColor; // ���_�̐F
		float u, v; //�@�e�N�X�`�����W 
	};

public:
	enum BILLBOARDCHAR_RESOLUTION {
		BILLBOARDCHAR_RESOLUTION_LOW = 0,
		BILLBOARDCHAR_RESOLUTION_MIDDLE = 1,
		BILLBOARDCHAR_RESOLUTION_HIGH = 2
	};

private:
	// �����R�[�h�ϊ�
	unsigned int TransCharCode(const TCHAR *c);

protected:
	// �r���{�[�h�e�N�X�`���쐬
	bool CreateTexture(unsigned int width, unsigned int height);

	// �t�H���g�n���h������
	bool BillboardChar::CreateFontHandle();

	// �t�H���g�r�b�g�}�b�v�𐶐�
	DWORD CreateFontBMP(TEXTMETRIC &TM, GLYPHMETRICS &GM, BYTE **outBMP);

	// BMP���e�N�X�`���ɓK�p
	bool ApplyBMPToTex(BYTE* bmp, TEXTMETRIC &TM, GLYPHMETRICS &GM);

	// �������e�N�X�`���ɍ���
	bool PlotCharToTex();

	// �`��ʒu�X�V
	bool UpdateSizeAndPosition(float x, float y);

	// �����_�����O����
	void SetRenderState();

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	BillboardChar();
	virtual ~BillboardChar();

	// �A�b�v�f�[�g
	bool Update();

	// �����o�^
	BillboardChar::Regist RegistChar(const TCHAR *c);

	// ��{�����R�s�[
	void CopyBaseInfoFrom(BillboardChar* src);

	// �𑜓x�ݒ�
	void SetResolution(BILLBOARDCHAR_RESOLUTION resolution);

	// �t�H���g�����T�C�Y�w��
	bool SetMaxPixelSize(unsigned int size);

	// �t�H���g�X�P�[���w��
	void SetScale(float xs, float ys);

	// ��]�p�x�w��
	void SetAngle(float angle);

	// �ʒu�w��
	void SetPosition(float x, float y);

	// �t�H���g�w��
	bool SetFont(const TCHAR *FaceName);

	// �Z���^�[�ʒu�w��
	void SetCenterPos(float x, float y);

	// �A���t�@�l�w��
	void SetAlpha(int alpha);

	// �����̃x�[�X�J���[�w��
	void SetColor(DWORD color);

	// �t�H���g�e�N�X�`���擾
	IDirect3DTexture9* GetFontTexture();

	// �\���������擾
	float GetDispWidth();

	// �\�������E�ʒu�擾
	float GetRightPos();

	// �`��
	bool Draw();

private:
	// �N���X�ϐ�
	static const BillboardVertex m_vertex[4];	// �r���{�[�h���_

private:
	IDirect3DTexture9* m_pTex;				// �����e�N�X�`��
	IDirect3DVertexBuffer9* m_pVertexBuf;	// ���_�o�b�t�@
	TCHAR m_char[2];						// �`�敶��
	TCHAR m_lfFaceName[LF_FACESIZE];		// �t�H���g��
	HFONT m_hFont;							// �t�H���g�n���h��
	int m_iBmp_W;
	int m_iBmp_H;
	int m_iBmpOfs_x;
	int m_iBmpOfs_y;
	bool m_iSFontHandleRecreate;
	bool m_isUpdate;						// �A�b�v�f�[�g�w��
	int m_texSize;
	unsigned int m_maxPixel;				// �t�H���g�T�C�Y
	DWORD m_color;							// �t�H���g�J���[
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
