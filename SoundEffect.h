#pragma once
#include <vector>
#include <dsound.h>

class Sound;

/// 効果音（シングルトン）
class SoundEffect {
private:
	SoundEffect();
	~SoundEffect();
	SoundEffect(const SoundEffect& se);
	SoundEffect& operator=(const SoundEffect& se);
	static const int SE_NUM;
	static std::vector<Sound*> m_sounds;
	static std::vector<bool> m_playables;
	static std::vector<int> m_playtimes;
	static SoundEffect* m_instance;

public:
	// インスタンス取得
	static SoundEffect* GetInstance();

	// サウンド情報の読み込み
	static void LoadSound(HWND hWnd);

	// サウンド情報の破棄
	static void DestorySound();

	// 効果音を再生
	static void Play(int SE_id);

	// 効果音が再生中か否か
	static bool InPlay(int SE_id);

	// 実行
	static void Play();
};
