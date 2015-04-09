#pragma once
#include <dinput.h>
#include <vector>

class Key;


/// �L�[�{�[�h���̓N���X�i�V���O���g���j
class KeyInput
{
private:
	KeyInput();
	~KeyInput();
	KeyInput(const KeyInput& input);
	KeyInput& operator=(const KeyInput& input);
	static KeyInput* m_instance;
	static const int DIKS_ARRAY_SIZE;			// �L�[���͔z��T�C�Y
	static LPDIRECTINPUT8 m_pInput;				// �C���v�b�g
	static LPDIRECTINPUTDEVICE8 m_pKeyDevice;	// �C���v�b�g�f�o�C�X
	static std::vector<Key*> keys;				// �L�[���͔z��

public:
	// �C���X�^���X�擾
	static KeyInput* GetInstance();

	// �L�[���͏���������
	static HRESULT InitKeyInput(HWND hWnd);

	// �L�[���͏������
	static void DestroyKeyInput();

	// �L�[���͔z��̎擾
	std::vector<Key*> GetKeys();

	// �L�[���͔z����X�V
	static void Update();
};

