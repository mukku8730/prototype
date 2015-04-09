#include "SoundEffect.h"
#include "Sound.h"
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

const int SoundEffect::SE_NUM = 1;
std::vector<Sound*> SoundEffect::m_sounds;
std::vector<bool> SoundEffect::m_playables;
std::vector<int> SoundEffect::m_playtimes;
SoundEffect* SoundEffect::m_instance = NULL;

/**
	コンストラクタ（空実装）
*/
SoundEffect::SoundEffect() {}


/**
	デストラクタ（空実装）
*/
SoundEffect::~SoundEffect() {}


/**
	インスタンス取得
*/
SoundEffect* SoundEffect::GetInstance() {
	return m_instance;
}


/**
	サウンド情報の読み込み
	@param hWnd	ウインドウハンドル
*/
void SoundEffect::LoadSound(HWND hWnd) {
/*
	LPCTSTR filename[SE_NUM] = {
		SE挿入
	};
	for (int i = 0; i < SE_NUM; ++i) {
		m_sounds[i] = new Sound(filename[i], hWnd));
		assert(m_sounds[i] != NULL);
		m_playables[i] = true;
		m_playtimes[i] = 0;
	}
	m_sounds[0]->SetVolume(-1000);
*/
}


/**
	サウンド情報の破棄
*/
void SoundEffect::DestorySound() {
	for (int i = 0; i < SE_NUM; ++i) {
		SAFE_DELETE(m_sounds[i]);
	}
}


/**
	IDで指定した効果音を再生。一度再生すると、再生禁止時間の間、再生できない
	@param SE_id 効果音ID
*/
void SoundEffect::Play(int SE_id) {
	if (m_playables[SE_id]) {
		m_sounds[SE_id]->Play();
		m_playables[SE_id] = false;
	}
}


/**
	IDで指定した効果音が再生中か否か
	@param SE_id 効果音ID
*/
bool SoundEffect::InPlay(int SE_id) {
	return m_sounds[SE_id]->InPlay();
}


void SoundEffect::Play() {
	const int freeztime[SE_NUM] = { 60 };	// 再生禁止時間
	for (int i = 0; i < SE_NUM; ++i) {
		if (!m_playables[i]) {
			if (++m_playtimes[i] > freeztime[i]) {
				m_playables[i] = true;
				m_playtimes[i] = 0;
			}
		}
	}
}
