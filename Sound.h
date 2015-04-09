#pragma once
#include <dsound.h>


/// �T�E���h
class Sound
{
private:
	LPDIRECTSOUND8 m_pSound;			// �T�E���h�f�o�C�X
	LPDIRECTSOUNDBUFFER m_pSoundBuffer;	// �T�E���h�p�̃�����

	// �T�E���h�p�̃������쐬
	void CreateSecondaryBuffer(WAVEFORMATEX* pwfex, DWORD dwWavSize);

	// �o�b�t�@�[�ɉ��f�[�^����������
	void WriteSoundDataToBuffer(DWORD dwWavSize, MMCKINFO ckInfo, LPCTSTR filename, MMCKINFO riffckInfo);

public:
	Sound(LPCTSTR filename, HWND hWnd);
	~Sound();

	// �Đ�
	void Play();

	// ��~
	void Stop();

	// �{�����[����ݒ�
	void SetVolume(int volume);

	// ���g����ݒ�
	void SetFrequency(int resettingSamplingRate);

	// �Đ������ۂ�
	bool InPlay();
};

