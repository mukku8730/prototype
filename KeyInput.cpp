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
	コンストラクタ(封印)
*/
KeyInput::KeyInput() {}


/**
	デストラクタ(封印)
*/
KeyInput::~KeyInput() {}


/**
	インスタンス取得
*/
KeyInput* KeyInput::GetInstance() {
	return m_instance;
}


/**
	キー入力初期化処理
	@param hWnd	ウインドウハンドル
*/
HRESULT KeyInput::InitKeyInput(HWND hWnd) {
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pInput, NULL))) return E_FAIL;
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, NULL))) return E_FAIL;
	// 入力データ形式のセット
	if (FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard))) return E_FAIL;
	// 排他制御
	if (FAILED(m_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) return E_FAIL;
	// 入力開始を宣言
	m_pKeyDevice->Acquire();
	for (int i = 0; i < DIKS_ARRAY_SIZE; ++i) keys.push_back(new Key());

	return S_OK;
}


/**
	キー入力情報を解放
*/
void KeyInput::DestroyKeyInput() {
	for (unsigned int i = 0; i < keys.size(); ++i) SAFE_DELETE(keys[i]);
	SAFE_RELEASE(m_pInput);
	SAFE_RELEASE(m_pKeyDevice);
}


/**
	キー入力配列の取得
	@return キー入力配列
	@note	要素数256のキー入力配列を取得する。
			キー入力配列の要素は対応するキーが押されていればtrue、
			押されていなければfalse
			DIK_RETURN	リターン
			DIK_UP		↑
			DIK_DOWN	↓
			DIK_RIGHT	→
			DIK_LEFT	←
*/
std::vector<Key*> KeyInput::GetKeys() {
	return keys;
}


/**
	キー入力配列を更新
*/
void KeyInput::Update() {
	BYTE keyState[DIKS_ARRAY_SIZE] = {0};
	HRESULT hr = m_pKeyDevice->Acquire();
	if (hr == DI_OK || hr == S_FALSE){
		// 入力データを取得
		m_pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		for (int i = 0; i < sizeof(keyState); ++i) {
			keys[i]->Pushed((keyState[i] & 0x80) != 0);
		}
	}
	else throw TEXT("キー入力の取得に失敗しました");
}
