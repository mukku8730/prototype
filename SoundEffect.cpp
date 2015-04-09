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
	�R���X�g���N�^�i������j
*/
SoundEffect::SoundEffect() {}


/**
	�f�X�g���N�^�i������j
*/
SoundEffect::~SoundEffect() {}


/**
	�C���X�^���X�擾
*/
SoundEffect* SoundEffect::GetInstance() {
	return m_instance;
}


/**
	�T�E���h���̓ǂݍ���
	@param hWnd	�E�C���h�E�n���h��
*/
void SoundEffect::LoadSound(HWND hWnd) {
/*
	LPCTSTR filename[SE_NUM] = {
		SE�}��
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
	�T�E���h���̔j��
*/
void SoundEffect::DestorySound() {
	for (int i = 0; i < SE_NUM; ++i) {
		SAFE_DELETE(m_sounds[i]);
	}
}


/**
	ID�Ŏw�肵�����ʉ����Đ��B��x�Đ�����ƁA�Đ��֎~���Ԃ̊ԁA�Đ��ł��Ȃ�
	@param SE_id ���ʉ�ID
*/
void SoundEffect::Play(int SE_id) {
	if (m_playables[SE_id]) {
		m_sounds[SE_id]->Play();
		m_playables[SE_id] = false;
	}
}


/**
	ID�Ŏw�肵�����ʉ����Đ������ۂ�
	@param SE_id ���ʉ�ID
*/
bool SoundEffect::InPlay(int SE_id) {
	return m_sounds[SE_id]->InPlay();
}


void SoundEffect::Play() {
	const int freeztime[SE_NUM] = { 60 };	// �Đ��֎~����
	for (int i = 0; i < SE_NUM; ++i) {
		if (!m_playables[i]) {
			if (++m_playtimes[i] > freeztime[i]) {
				m_playables[i] = true;
				m_playtimes[i] = 0;
			}
		}
	}
}
