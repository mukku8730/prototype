#include "FileMesh.h"
#include "Graphics.h"
#include "Textures.h"
#include "DebugFont.h"
#include <cassert>
#include <string.h>
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

/**
	�R���X�g���N�^
	Load the mesh and build the material and texture arrays
	@param filename �摜�t�@�C����
*/
FileMesh::FileMesh(LPCTSTR filename) : m_textureIdx(0) {
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh))) throw TEXT("X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];
	assert(m_pMeshMaterials != NULL);
	assert(m_pMeshTextures != NULL);
	for (DWORD i = 0; i < m_dwNumMaterials; ++i) {
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		m_pMeshTextures[i] = NULL;

		// �e�N�X�`���t�@�C������Unicode�Ή�
		char dst[256] = { "Material/" };
		char str[256] = { 0 };

		if (d3dxMaterials[i].pTextureFilename) strcpy_s(str, d3dxMaterials[i].pTextureFilename);
		strcat_s(dst, str);
		DebugFont::GetInstance()->Print(160, 160, 0xffffffff, "%s", dst);
		TCHAR textureFilename[256] = { 0 };
#ifdef UNICODE
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, dst, strlen(dst), textureFilename, (sizeof textureFilename) / 2);
#else
		strcpy_s(textureFilename, dst);
#endif

		//TODO::
		if ((textureFilename != NULL) && (strcmp(dst, "Material/"))) {
			m_textureIdx = i;
			if (FAILED(D3DXCreateTextureFromFileEx(pDevice, textureFilename, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pMeshTextures[m_textureIdx]))) throw TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���");
		}
	}
	pD3DXMtrlBuffer->Release();
}

/**
	�f�X�g���N�^
*/
FileMesh::~FileMesh() {
	SAFE_RELEASE(m_pMesh);

	for (DWORD i = 0; i < m_dwNumMaterials; ++i) {
		SAFE_RELEASE(m_pMeshTextures[i]);
	}
	SAFE_DELETE(m_pMeshTextures);
	SAFE_DELETE(m_pMeshMaterials);
}


/**
	�e�N�X�`����ݒ�
	@param int janpaiId	�w�肵��ID
*/
HRESULT FileMesh::SetTexture(int janpaiID) {
	if (NULL == (m_pMeshTextures[m_textureIdx] = Textures::GetInstance()->GetTexture(janpaiID))) return E_FAIL;
	return S_OK;
}


/**
	�`�揈��
	@param position �ʒu
	@param attitude �p����\����]�s��
*/
void FileMesh::Draw(const Vector3& position, const Matrix16& attitude) {
	Matrix16 matWorld, matTrans;
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	matWorld = attitude * matTrans;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S����Diffuse�F�̓����x���e�N�X�`���ɔ��f������
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	for (DWORD i = 0; i < m_dwNumMaterials; ++i) {
		pDevice->SetMaterial(&m_pMeshMaterials[i]);
		pDevice->SetTexture(0, m_pMeshTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}


/**
	�`�揈��
	@param position �ʒu
	@param attitude �p����\����]�s��
	@param scale	�g��
*/
void FileMesh::Draw(const Vector3& position, const Matrix16& attitude, const Vector3& scale) {
	Matrix16 matWorld, matTrans, matScale, matMul;
	D3DXMatrixIdentity(&matWorld);
	LPDIRECT3DDEVICE9 pDevice = Graphics::GetInstance()->GetGraphicsDevice();

	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&matMul, &matScale, &attitude);
	D3DXMatrixMultiply(&matWorld, &matMul, &matTrans);
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S����Diffuse�F�̓����x���e�N�X�`���ɔ��f������
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	for (DWORD i = 0; i < m_dwNumMaterials; ++i) {
		pDevice->SetMaterial(&m_pMeshMaterials[i]);
		pDevice->SetTexture(0, m_pMeshTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}
