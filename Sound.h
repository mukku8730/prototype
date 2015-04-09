#pragma once
#include <dsound.h>


/// サウンド
class Sound
{
private:
	LPDIRECTSOUND8 m_pSound;			// サウンドデバイス
	LPDIRECTSOUNDBUFFER m_pSoundBuffer;	// サウンド用のメモリ

	// サウンド用のメモリ作成
	void CreateSecondaryBuffer(WAVEFORMATEX* pwfex, DWORD dwWavSize);

	// バッファーに音データを書き込む
	void WriteSoundDataToBuffer(DWORD dwWavSize, MMCKINFO ckInfo, LPCTSTR filename, MMCKINFO riffckInfo);

public:
	Sound(LPCTSTR filename, HWND hWnd);
	~Sound();

	// 再生
	void Play();

	// 停止
	void Stop();

	// ボリュームを設定
	void SetVolume(int volume);

	// 周波数を設定
	void SetFrequency(int resettingSamplingRate);

	// 再生中か否か
	bool InPlay();
};

