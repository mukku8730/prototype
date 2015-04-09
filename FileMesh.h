#pragma once
#include "Vector3.h"

/// �t�@�C������Ǎ��񂾃��b�V��
class FileMesh {
private:
	LPD3DXMESH			m_pMesh;			// ���b�V��
	D3DMATERIAL9*		m_pMeshMaterials;	// �}�e���A���z��
	LPDIRECT3DTEXTURE9*	m_pMeshTextures;	// �e�N�X�`���z��
	DWORD				m_dwNumMaterials;	// �}�e���A���E�e�N�X�`���z��̑傫��
	DWORD				m_textureIdx;		// �e�N�X�`���t�@�C�����w�肳��Ă���Y��

public:
	FileMesh(LPCTSTR filename);
	~FileMesh();

	// �e�N�X�`����ݒ�
	HRESULT SetTexture(int janpaiID);

	// �`��i�g��Ȃ��j
	void Draw(const Vector3& position, const Matrix16& attitude);

	// �`��i�g�傠��j
	void Draw(const Vector3& position, const Matrix16& attitude, const Vector3& scale);
};
