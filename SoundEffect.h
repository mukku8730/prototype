#pragma once
#include <vector>
#include <dsound.h>

class Sound;

/// ���ʉ��i�V���O���g���j
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
	// �C���X�^���X�擾
	static SoundEffect* GetInstance();

	// �T�E���h���̓ǂݍ���
	static void LoadSound(HWND hWnd);

	// �T�E���h���̔j��
	static void DestorySound();

	// ���ʉ����Đ�
	static void Play(int SE_id);

	// ���ʉ����Đ������ۂ�
	static bool InPlay(int SE_id);

	// ���s
	static void Play();
};
