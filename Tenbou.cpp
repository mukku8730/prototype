#include "Tenbou.h"
#include "FileMesh.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


/**
	�R���X�g���N�^
*/
Tenbou::Tenbou() :
m_tenbou(new FileMesh(TEXT("Material/tenbou.x"))),
m_position(0.0f, 0.0f, 0.0f),
m_rotation(),
m_scale(0.1f, 0.1f, 0.1f) {
	assert(m_tenbou != NULL);
	D3DXMatrixIdentity(&m_rotation);
}


/**
	�f�X�g���N�^
*/
Tenbou::~Tenbou()
{
	SAFE_DELETE(m_tenbou);
}


/**
	�e�N�X�`����ݒ�
	@param janpaiID	�w�肵��ID
*/
HRESULT Tenbou::SetTexture(int janpaiID) {
	if (FAILED(m_tenbou->SetTexture(janpaiID))) return E_FAIL;
	return S_OK;
}


/**
	���W�ݒ�
	@param position	���W
*/
void Tenbou::SetPosition(const Vector3& position) {
	m_position = position;
}


/**
	�X�V����
*/
void Tenbou::Update() {
	D3DXMatrixRotationY(&m_rotation, D3DX_PI / 2); // 90����]
}


/**
	�`�揈��
	@param	�_�_�̏��
*/
void Tenbou::Draw() {
	m_tenbou->Draw(m_position, m_rotation, m_scale);
}
