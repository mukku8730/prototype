#include "KeyInput.h"
#include "Key.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

KeyInput* KeyInput::m_instance = 0;
const int KeyInput::DIKS_ARRAY_SIZE = 256;
LPDIRECTINPUT8 KeyInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 KeyInput::m_pKeyDevice = NULL;
std::vector<Key*> KeyInput::keys;


/**
	�R���X�g���N�^(����)
*/
KeyInput::KeyInput() {}


/**
	�f�X�g���N�^(����)
*/
KeyInput::~KeyInput() {}


/**
	�C���X�^���X�擾
*/
KeyInput* KeyInput::GetInstance() {
	return m_instance;
}


/**
	�L�[���͏���������
	@param hWnd	�E�C���h�E�n���h��
*/
HRESULT KeyInput::InitKeyInput(HWND hWnd) {
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pInput, NULL))) return E_FAIL;
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, NULL))) return E_FAIL;
	// ���̓f�[�^�`���̃Z�b�g
	if (FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard))) return E_FAIL;
	// �r������
	if (FAILED(m_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) return E_FAIL;
	// ���͊J�n��錾
	m_pKeyDevice->Acquire();
	for (int i = 0; i < DIKS_ARRAY_SIZE; ++i) keys.push_back(new Key());

	return S_OK;
}


/**
	�L�[���͏������
*/
void KeyInput::DestroyKeyInput() {
	for (unsigned int i = 0; i < keys.size(); ++i) SAFE_DELETE(keys[i]);
	SAFE_RELEASE(m_pInput);
	SAFE_RELEASE(m_pKeyDevice);
}


/**
	�L�[���͔z��̎擾
	@return �L�[���͔z��
	@note	�v�f��256�̃L�[���͔z����擾����B
			�L�[���͔z��̗v�f�͑Ή�����L�[��������Ă����true�A
			������Ă��Ȃ����false
			DIK_RETURN	���^�[��
			DIK_UP		��
			DIK_DOWN	��
			DIK_RIGHT	��
			DIK_LEFT	��
*/
std::vector<Key*> KeyInput::GetKeys() {
	return keys;
}


/**
	�L�[���͔z����X�V
*/
void KeyInput::Update() {
	BYTE keyState[DIKS_ARRAY_SIZE] = {0};
	HRESULT hr = m_pKeyDevice->Acquire();
	if (hr == DI_OK || hr == S_FALSE){
		// ���̓f�[�^���擾
		m_pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		for (int i = 0; i < sizeof(keyState); ++i) {
			keys[i]->Pushed((keyState[i] & 0x80) != 0);
		}
	}
	else throw TEXT("�L�[���͂̎擾�Ɏ��s���܂���");
}
