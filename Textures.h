#pragma once
#include <d3dx9.h>


/// �e�N�X�`���Ǘ��N���X�i�V���O���g���j
class Textures
{
private:
	Textures();
	~Textures();
	Textures(const Textures& texture);
	Textures& operator=(const Textures& texture);
	static Textures* m_instance;
	static LPDIRECT3DTEXTURE9*	m_pMeshTextures; // �e�N�X�`���z��
	static const DWORD m_textureIdx;

public:
	// �C���X�^���X�擾
	static Textures* GetInstance();

	// �e�N�X�`�����̓ǂݍ���
	static HRESULT LoadTextures();

	// �e�N�X�`������j��
	static void DestroyTextures();

	// �w�肳�ꂽID�̃e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetTexture(DWORD TX_id);
};

