#include "Graphics.h"
#include <cassert>
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }


Graphics* Graphics::m_instance = 0;
GraphicsObject Graphics::m_pGraphicsObject = NULL;
GraphicsDevice Graphics::m_pGraphicsDevice = NULL;
FLOAT Graphics::m_fogStart = 150;
FLOAT Graphics::m_fogEnd = 1000;
/**
	�R���X�g���N�^(����)
*/
Graphics::Graphics() {}

/**
	�f�X�g���N�^(����)
*/
Graphics::~Graphics() {}

/**
	�C���X�^���X�擾
	@param �C���X�^���X
*/
Graphics* Graphics::GetInstance() {
	return m_instance;
}

/**
	�O���t�B�b�N�̏���������
	@param hWnd	�E�C���h�E�n���h��
*/
HRESULT Graphics::InitGraphics(HWND hWnd) {
	if (m_pGraphicsObject != NULL) return E_FAIL;
	// Create the D3D object.
	if (NULL == (m_pGraphicsObject = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	if (m_pGraphicsDevice != NULL) return E_FAIL;
	// Create the D3DDevice
	if (FAILED(m_pGraphicsObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pGraphicsDevice)))
	{
		return E_FAIL;
	}

	// Turn on the zbuffer
	m_pGraphicsDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//SetFogConfiguration();

	return S_OK;
}

/**
	�O���t�B�b�N�I�u�W�F�N�g�̎擾
	@return	�O���t�B�b�N�I�u�W�F�N�g
*/
GraphicsObject Graphics::GetGraphicsObject() {
	if (m_pGraphicsObject != NULL) return m_pGraphicsObject;
	else return NULL;
}

/**
	�O���t�B�b�N�f�o�C�X�̎擾
	@return	�O���t�B�b�N�f�o�C�X
*/
GraphicsDevice Graphics::GetGraphicsDevice() {
	if (m_pGraphicsDevice != NULL) return m_pGraphicsDevice;
	else return NULL;
}

/**
	�O���t�B�b�N�I�u�W�F�N�g�̉��
*/
void Graphics::DestroyGraphicsObject() {
	SAFE_RELEASE(m_pGraphicsObject);
}

/**
	�O���t�B�b�N�f�o�C�X�̉��
*/
void Graphics::DestroyGraphicsDevice() {
	SAFE_RELEASE(m_pGraphicsDevice);
}

/**
	��ʂ�w�i�F�ŃN���A���A�V�[�����J�n����B�`��֐��̓V�[�����ɌĂяo��
*/
void Graphics::BeginScene() {
	m_pGraphicsDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	if (!SUCCEEDED(m_pGraphicsDevice->BeginScene())) throw TEXT("BeginScene�Ɏ��s���܂���");
}

/**
	�V�[�����I������
*/
void Graphics::EndScene() {
	m_pGraphicsDevice->EndScene();
	m_pGraphicsDevice->Present(NULL, NULL, NULL, NULL);
}


/**
	�t�H�O�̐ݒ�
*/
void Graphics::SetFogConfiguration() {
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	m_pGraphicsDevice->GetDeviceCaps(&caps);
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE) == 0) {
		if (MessageBox(0, TEXT("�s�N�Z���t�H�O���g���Ȃ��\��������܂��B���s���܂���?"), TEXT("����"), MB_ABORTRETRYIGNORE) == IDABORT) throw TEXT("�t�H�O�ݒ�Ɏ��s���܂���");
	}
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(150, 255, 255, 255));
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fogStart));
	m_pGraphicsDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fogEnd));
}
