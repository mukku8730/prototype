#include "Sound.h"
#include <mmsystem.h>
#include <iostream>
#include <tchar.h>
#pragma comment (lib, "dsound.lib")

#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/**
	�R���X�g���N�^
	@param filename wav�t�@�C����
	@param hWnd �E�B���h�E�n���h��
*/
Sound::Sound(LPCTSTR filename, HWND hWnd) {
	HMMIO hMmio = NULL;				// Windows�}���`���f�B�AAPI�̃n���h��
	WAVEFORMATEX* pwfex;			// WAV�̃t�H�[�}�b�g�i������`�����l�����̏�񓙁j
	MMCKINFO ckInfo;				// �`�����N���
	MMCKINFO riffckInfo;			// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
	PCMWAVEFORMAT pcmWaveFormat;
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL))) throw TEXT("�T�E���h�J�[�h������܂���"); // �T�E���h�I�u�W�F�N�g�𐶐�
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE))) throw TEXT("�������x���ݒ莸�s"); // �������x���̐ݒ�
	hMmio = mmioOpen((LPTSTR)filename, NULL, MMIO_ALLOCBUF | MMIO_READ); // WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &riffckInfo, NULL, 0)) throw TEXT("�ŏ��̃`�����N�ɐi�����s"); // �t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	if ((riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E'))) throw TEXT("�����WAV�t�@�C���ł͂���܂���"); // WAV�t�@�C�����ǂ����m�F
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK)) throw TEXT("fmt �`�����N��������܂���"); // �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g
	if (mmioRead(hMmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat)) throw TEXT("WAV�t�H�[�}�b�g�̓ǂݍ��ݎ��s"); // �t�H�[�}�b�g��ǂݍ���
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) { // ���j�APCM�ŁA���A�}���`�`�����l��WAV�͑z��O
		pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		if (!pwfex) throw TEXT("pwfex is null");
		memcpy(pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat));
		pwfex->cbSize = 0;
	}
	else throw TEXT("�{�T���v���͕W���̃��j�APCM�t�H�[�}�b�g��z�肵�Ă��܂�");
	if (MMSYSERR_NOERROR != mmioAscend(hMmio, &ckInfo, 0)) {
		SAFE_DELETE(pwfex);
		throw TEXT("MMSYSERR_NOERROR != mmioAscend( hMmio, &ckInfo, 0)");
	}
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK)) throw TEXT("data�`�����N��������܂���"); // WAV�t�@�C�����̉��f�[�^�̓ǂݍ���
	DWORD dwWavSize = ckInfo.cksize;
	CreateSecondaryBuffer(pwfex, dwWavSize);
	WriteSoundDataToBuffer(dwWavSize, ckInfo, filename, riffckInfo);
}

/**
	�f�X�g���N�^
*/
Sound::~Sound() {
	SAFE_RELEASE(m_pSoundBuffer);
	SAFE_RELEASE(m_pSound);
}

/**
	�T�E���h�p�̃������쐬
	@param pwfex		WAV�̃t�H�[�}�b�g�\����
	@param dwWavSize	�T�C�Y
*/
void Sound::CreateSecondaryBuffer(WAVEFORMATEX* pwfex, DWORD dwWavSize) {
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = dwWavSize;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = pwfex;
	if (FAILED(m_pSound->CreateSoundBuffer(&dsbd, &m_pSoundBuffer, NULL))) throw TEXT("�Z�J���_���o�b�t�@�[�쐬���s");
	SAFE_DELETE(pwfex);
}

/**
	�o�b�t�@�[�ɉ��f�[�^����������
	@param dwWavSize	�T�C�Y
	@param ckInfo		�`�����N���
	@param filename		�t�@�C����
	@param riffckInfo	�ŏ㕔�`�����N���
*/
void Sound::WriteSoundDataToBuffer(DWORD dwWavSize, MMCKINFO ckInfo, LPCTSTR filename, MMCKINFO riffckInfo) {
	VOID* pBuffer = NULL;
	DWORD dwBufferSize = 0;
	if (FAILED(m_pSoundBuffer->Lock(0, dwWavSize, &pBuffer, &dwBufferSize, NULL, NULL, 0))) throw TEXT("�Z�J���_���[�o�b�t�@�[ ���b�N���s"); 	//�g�`�f�[�^���������ޏ����Ƃ��āA�Z�J���_���[�o�b�t�@�[�����b�N����
	DWORD dwSize = dwBufferSize;
	if (dwSize > ckInfo.cksize) dwSize = ckInfo.cksize;									//���b�N�����o�b�t�@�[�T�C�Y�����ۂ̔g�`�f�[�^���傫���ꍇ�B�N���b�V���h�~�B
	FILE* fp;
	_tfopen_s(&fp, filename, TEXT("rb"));
	fseek(fp, riffckInfo.dwDataOffset + sizeof(FOURCC), SEEK_SET);
	BYTE* pWavData = new BYTE[dwSize];
	fread(pWavData, 1, dwSize, fp);														//�܂��́A�ꎞ�I�ȏꏊ(pWavData)�ɔg�`�f�[�^��ǂݍ���
	for (DWORD i = 0; i < dwSize; i++)	*((BYTE*)pBuffer + i) = *((BYTE*)pWavData + i);	//�ꎞ�I�ȏꏊ�̔g�`�f�[�^���Z�J���_���o�b�t�@�[�ɃR�s�[����
	fclose(fp);
	SAFE_DELETE(pWavData);																//�ꎞ�I�Ȕg�`�f�[�^���J������
	m_pSoundBuffer->Unlock(pBuffer, dwBufferSize, NULL, 0);
}

/**
	�t�@�C���̍ŏ�����Đ��B�t�@�C���̍Ō�ɂ����ƒ�~
*/
void Sound::Play() {
	m_pSoundBuffer->SetCurrentPosition(0);
	m_pSoundBuffer->Play(NULL, 0, NULL);
}


/**
	��~
*/
void Sound::Stop() {
	m_pSoundBuffer->Stop();
}


/**
	�{�����[����ݒ�
	@param volume �{�����[�� �B�ݒ�l��-10000�`0�B�P�ʂ�1/100dB�B
	@note	�{�����[���̓}�C�i�X�i�����j�̂݁B�v���X�i�����j�͂ł��Ȃ��B
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
	���g����ݒ�
	@param resettingSamplingRate �Đݒ�T���v�����O���[�g
	@note	�Ⴆ�΃T���v�����O���[�g44100kHz�̉��Ɏ��g��22050��ݒ肷���1/2�̑��x�ɂȂ�
*/
void Sound::SetFrequency(int resettingSamplingRate) {
	m_pSoundBuffer->SetFrequency((DWORD)resettingSamplingRate);
}


/**
	�Đ������ۂ�
	@return �Đ������ۂ�
*/
bool Sound::InPlay() {
	DWORD dwStatus;
	m_pSoundBuffer->GetStatus(&dwStatus);
	if ((dwStatus & DSBSTATUS_PLAYING) != 0) return true;
	else return false;
}
