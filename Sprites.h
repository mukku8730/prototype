#pragma once
#include <d3dx9.h>

/// �X�v���C�g�N���X�B
/// �摜�t�@�C����Ǎ��݁A�V�[�����ɃX�v���C�g�Ƃ��ĕ`�悷��B
class Sprites {
public:
	Sprites(LPCTSTR filename, bool add);

	~Sprites(void);

	// �`�揈��
	void Draw(RECT trimRect, D3DXVECTOR3 center, D3DXVECTOR3 position);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	LPD3DXSPRITE m_pSprite;			// �X�v���C�g
	bool m_additive;				// ���Z�������ۂ�
	void SetRenderState();	// �u�����h�̐ݒ�
};