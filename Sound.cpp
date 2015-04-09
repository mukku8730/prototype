#include "Sound.h"
#include <mmsystem.h>
#include <iostream>
#include <tchar.h>
#pragma comment (lib, "dsound.lib")

#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/**
	コンストラクタ
	@param filename wavファイル名
	@param hWnd ウィンドウハンドル
*/
Sound::Sound(LPCTSTR filename, HWND hWnd) {
	HMMIO hMmio = NULL;				// WindowsマルチメディアAPIのハンドル
	WAVEFORMATEX* pwfex;			// WAVのフォーマット（音質やチャンネル数の情報等）
	MMCKINFO ckInfo;				// チャンク情報
	MMCKINFO riffckInfo;			// 最上部チャンク（RIFFチャンク）保存用
	PCMWAVEFORMAT pcmWaveFormat;
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL))) throw TEXT("サウンドカードがありません"); // サウンドオブジェクトを生成
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE))) throw TEXT("協調レベル設定失敗"); // 協調レベルの設定
	hMmio = mmioOpen((LPTSTR)filename, NULL, MMIO_ALLOCBUF | MMIO_READ); // WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &riffckInfo, NULL, 0)) throw TEXT("最初のチャンクに進入失敗"); // ファイルポインタをRIFFチャンクの先頭にセットする
	if ((riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E'))) throw TEXT("これはWAVファイルではありません"); // WAVファイルかどうか確認
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK)) throw TEXT("fmt チャンクが見つかりません"); // ファイルポインタを'f' 'm' 't' ' ' チャンクにセット
	if (mmioRead(hMmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat)) throw TEXT("WAVフォーマットの読み込み失敗"); // フォーマットを読み込む
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) { // リニアPCMで、かつ、マルチチャンネルWAVは想定外
		pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		if (!pwfex) throw TEXT("pwfex is null");
		memcpy(pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat));
		pwfex->cbSize = 0;
	}
	else throw TEXT("本サンプルは標準のリニアPCMフォーマットを想定しています");
	if (MMSYSERR_NOERROR != mmioAscend(hMmio, &ckInfo, 0)) {
		SAFE_DELETE(pwfex);
		throw TEXT("MMSYSERR_NOERROR != mmioAscend( hMmio, &ckInfo, 0)");
	}
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK)) throw TEXT("dataチャンクが見つかりません"); // WAVファイル内の音データの読み込み
	DWORD dwWavSize = ckInfo.cksize;
	CreateSecondaryBuffer(pwfex, dwWavSize);
	WriteSoundDataToBuffer(dwWavSize, ckInfo, filename, riffckInfo);
}

/**
	デストラクタ
*/
Sound::~Sound() {
	SAFE_RELEASE(m_pSoundBuffer);
	SAFE_RELEASE(m_pSound);
}

/**
	サウンド用のメモリ作成
	@param pwfex		WAVのフォーマット構造体
	@param dwWavSize	サイズ
*/
void Sound::CreateSecondaryBuffer(WAVEFORMATEX* pwfex, DWORD dwWavSize) {
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = dwWavSize;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = pwfex;
	if (FAILED(m_pSound->CreateSoundBuffer(&dsbd, &m_pSoundBuffer, NULL))) throw TEXT("セカンダリバッファー作成失敗");
	SAFE_DELETE(pwfex);
}

/**
	バッファーに音データを書き込む
	@param dwWavSize	サイズ
	@param ckInfo		チャンク情報
	@param filename		ファイル名
	@param riffckInfo	最上部チャンク情報
*/
void Sound::WriteSoundDataToBuffer(DWORD dwWavSize, MMCKINFO ckInfo, LPCTSTR filename, MMCKINFO riffckInfo) {
	VOID* pBuffer = NULL;
	DWORD dwBufferSize = 0;
	if (FAILED(m_pSoundBuffer->Lock(0, dwWavSize, &pBuffer, &dwBufferSize, NULL, NULL, 0))) throw TEXT("セカンダリーバッファー ロック失敗"); 	//波形データを書き込む準備として、セカンダリーバッファーをロックする
	DWORD dwSize = dwBufferSize;
	if (dwSize > ckInfo.cksize) dwSize = ckInfo.cksize;									//ロックしたバッファーサイズが実際の波形データより大きい場合。クラッシュ防止。
	FILE* fp;
	_tfopen_s(&fp, filename, TEXT("rb"));
	fseek(fp, riffckInfo.dwDataOffset + sizeof(FOURCC), SEEK_SET);
	BYTE* pWavData = new BYTE[dwSize];
	fread(pWavData, 1, dwSize, fp);														//まずは、一時的な場所(pWavData)に波形データを読み込み
	for (DWORD i = 0; i < dwSize; i++)	*((BYTE*)pBuffer + i) = *((BYTE*)pWavData + i);	//一時的な場所の波形データをセカンダリバッファーにコピーする
	fclose(fp);
	SAFE_DELETE(pWavData);																//一時的な波形データを開放する
	m_pSoundBuffer->Unlock(pBuffer, dwBufferSize, NULL, 0);
}

/**
	ファイルの最初から再生。ファイルの最後にいくと停止
*/
void Sound::Play() {
	m_pSoundBuffer->SetCurrentPosition(0);
	m_pSoundBuffer->Play(NULL, 0, NULL);
}


/**
	停止
*/
void Sound::Stop() {
	m_pSoundBuffer->Stop();
}


/**
	ボリュームを設定
	@param volume ボリューム 。設定値は-10000～0。単位は1/100dB。
	@note	ボリュームはマイナス（減衰）のみ。プラス（増幅）はできない。
*/
void Sound::SetVolume(int volume) {
	if (volume < DSBVOLUME_MIN){
		volume = DSBVOLUME_MIN;
	}

	if (volume > DSBVOLUME_MAX) {
		volume = DSBVOLUME_MAX;
	}
	
	m_pSoundBuffer->SetVolume(volume);
}


/**
	周波数を設定
	@param resettingSamplingRate 再設定サンプリングレート
	@note	例えばサンプリングレート44100kHzの音に周波数22050を設定すると1/2の速度になる
*/
void Sound::SetFrequency(int resettingSamplingRate) {
	m_pSoundBuffer->SetFrequency((DWORD)resettingSamplingRate);
}


/**
	再生中か否か
	@return 再生中か否か
*/
bool Sound::InPlay() {
	DWORD dwStatus;
	m_pSoundBuffer->GetStatus(&dwStatus);
	if ((dwStatus & DSBSTATUS_PLAYING) != 0) return true;
	else return false;
}
