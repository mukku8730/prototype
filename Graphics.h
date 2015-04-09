#pragma once
#include <d3dx9.h>


typedef LPDIRECT3D9 GraphicsObject;
typedef LPDIRECT3DDEVICE9 GraphicsDevice;

/// �O���t�B�b�N����N���X
class Graphics
{
private:
	Graphics();
	~Graphics();
	Graphics(const Graphics& directX);
	Graphics& operator=(const Graphics& directX);
	static GraphicsObject m_pGraphicsObject;
	static GraphicsDevice m_pGraphicsDevice; // Direct3D�f�o�C�X�I�u�W�F�N�g
	static Graphics* m_instance;
	static FLOAT m_fogStart;					// �t�H�O�̃X�^�[�g
	static FLOAT m_fogEnd;					// �t�H�O�̃G���h
	static void SetFogConfiguration();		// �t�H�O�̐ݒ�

public:
	// �C���X�^���X�擾
	static Graphics* GetInstance();

	// �O���t�B�b�N�̏���������
	static HRESULT InitGraphics(HWND hWnd);

	// �O���t�B�b�N�I�u�W�F�N�g�̎擾
	GraphicsObject GetGraphicsObject();

	// �O���t�B�b�N�f�o�C�X�̎擾
	GraphicsDevice GetGraphicsDevice();

	// �O���t�B�b�N�I�u�W�F�N�g�̉��
	static void DestroyGraphicsObject();

	// �O���t�B�b�N�f�o�C�X�̉��
	static void DestroyGraphicsDevice();

	/// �V�[���J�n
	static void BeginScene();

	/// �V�[���I��
	static void EndScene();
};

