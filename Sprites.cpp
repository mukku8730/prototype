#include "Sprites.h"
#include "Graphics.h"
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }



/**
	�R���X�g���N�^
	@param filename	�摜�t�@�C����
	@param add		���Z�������ۂ�
*/
Sprites::Sprites(LPCTSTR filename, bool add) :
m_pTexture(NULL),
m_pSprite(NULL),
m_additive(false)
{
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	D3DXCreateSprite(pDevice, &m_pSprite);
	if (D3DXCreateTextureFromFileEx(pDevice, filename, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL, &m_pTexture) != D3D_OK) // �F�����Ȃ�
		throw TEXT("�e�N�X�`���̍쐬�Ɏ��s���܂���");
}


/**
	�f�X�g���N�^
*/
Sprites::~Sprites() {
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}


/**
	�u�����h�̐ݒ�
*/
void Sprites::SetRenderState() {
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();
	DWORD src, dest;
	if (m_additive) {
		src = D3DBLEND_ONE;
		dest = D3DBLEND_ONE;
	}
	else {
		src = D3DBLEND_SRCALPHA;
		dest = D3DBLEND_INVSRCALPHA;
	}
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, src);
	pDevice->SetRenderState(D3DRS_DESTBLEND, dest);
}


/**
	�`�揈��
	@param trimRect �g���~���O�̈� (�摜����)
	@param center	�g���~���O�̈撆�S (�g���~���O��`�̍���)
	@param position	�g���~���O�̈撆�S�̈ʒu (�X�N���[������)
*/
void Sprites::Draw(RECT trimRect, D3DXVECTOR3 center, D3DXVECTOR3 position) {
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetRenderState();
	m_pSprite->Draw(m_pTexture, &trimRect, &center, &position, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	m_pSprite->End();
}

