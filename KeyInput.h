#pragma once
#include <dinput.h>
#include <vector>

class Key;


/// キーボード入力クラス（シングルトン）
class KeyInput
{
private:
	KeyInput();
	~KeyInput();
	KeyInput(const KeyInput& input);
	KeyInput& operator=(const KeyInput& input);
	static KeyInput* m_instance;
	static const int DIKS_ARRAY_SIZE;			// キー入力配列サイズ
	static LPDIRECTINPUT8 m_pInput;				// インプット
	static LPDIRECTINPUTDEVICE8 m_pKeyDevice;	// インプットデバイス
	static std::vector<Key*> keys;				// キー入力配列

public:
	// インスタンス取得
	static KeyInput* GetInstance();

	// キー入力初期化処理
	static HRESULT InitKeyInput(HWND hWnd);

	// キー入力情報を解放
	static void DestroyKeyInput();

	// キー入力配列の取得
	std::vector<Key*> GetKeys();

	// キー入力配列を更新
	static void Update();
};

