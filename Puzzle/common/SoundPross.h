	#pragma once
#include <DxLib.h>
#include <array>
#include "../Scene/Scene.h"

#define lpSooundPross SoundProcess::GetInstance()

// SE�̎��
enum class SOUNDNAME_SE
{
	ControlBlock,
	Select,
	Delete,
	Finish,
	Button,
	Max
};

// BGM�̎��
enum class SOUNDNAME_BGM
{
	TitleSceneBGM,
	GameSceneBGM,
	Max
};

// SE�̐�
constexpr int seNum = static_cast<int>(SOUNDNAME_SE::Max) + 1;		

// BGM�̐�
constexpr int bgmNum = static_cast<int>(SOUNDNAME_BGM::Max) + 1;			

class SoundProcess
{
public:

	static SoundProcess& GetInstance(void)
	{
		static SoundProcess s_Instance;
		return s_Instance;
	}

	// ������
	void Init(Scene nowScene);

	// ���[�h
	void Load(int loadFile, SOUNDNAME_SE name);		// SE�̃��[�h
	void Load(int loadFile, SOUNDNAME_BGM name);	// BGM�̃��[�h

	/// <summary>
	/// SE�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="volume">����</param>
	/// <param name="loopflag">���[�v�t���O</param>
	void PlayBackSound(SOUNDNAME_SE name, float volume, bool loopflag);

	/// <summary>
	/// BGM�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="volume">����</param>
	/// <param name="loopflag">���[�v�t���O</param>
	void PlayBackSound(SOUNDNAME_BGM name, float volume, bool loopflag);

	/// <summary>
	/// SE���~�߂�
	/// </summary>
	/// <param name="name">���O</param>
	void SoundStop(SOUNDNAME_SE name);

	/// <summary>
	/// BGM���~�߂�
	/// </summary>
	/// <param name="name">���O</param>
	void SoundStop(SOUNDNAME_BGM name);

	/// �~�߂Ă���SE���Đ�����
	/// <name> ��������SE���w��
	/// <loopflag> ���[�v�����邩���w��
	/// <loopTime> �Ȃ�����ĉ��b���������̎w��
	void SoundPlay(SOUNDNAME_SE name, bool loopflag, float loopTime);

	/// �~�߂Ă���BGM���Đ�����
	/// <name> ��������BGM���w��
	/// <loopflag> ���[�v�����邩���w��
	/// <loopTime> �Ȃ�����ĉ��b���������̎w��
	void SoundPlay(SOUNDNAME_BGM name, bool loopflag, float loopTime);

	// ���
	void Release();
	void Release(SOUNDNAME_SE name);
	void Release(SOUNDNAME_BGM name);

	// SE�̃��[�U�[���ʒ�����ݒ�
	void SetSEVolumeEntire(float UserSetVolume);

	// SE�̃��[�U�[���ʒ�����n��
	float GetSEVolumeEntire();

	// BGM�̃��[�U�[���ʒ�����ݒ�
	void SetBGMVolumeEntire(float UserSetVolume);

	// BGM�̃��[�U�[���ʒ�����n��
	float GetBGMVolumeEntire();

	// �W���̉��ʂ��Z�b�g����
	void SetDefaultVolume(float defaultVol);

	// �W���̉��ʂ��擾����
	float GetDefaultVolume();

	// �{�����[�����Z�b�g����
	void SetVolume(float volume);

	// �{�����[�����擾����
	float GetVolume();

private:
	SoundProcess();
	~SoundProcess();

	// �{�����[���֌W
	float volume_ = 255.0f;				// �{�����[��
	float defaultSEVol_ = 200.5f;		// �f�t�H���g��SE�̃{�����[��
	float defaultBGMVol_ = 150.5f;		// �f�t�H���g��BGM�̃{�����[��

	// SE�̕ϐ�
	std::array<int, seNum> se_sound;				// se�𐔂����ۑ�
	std::array<int, seNum> se_volumeSetMaxVolume;	// SE�̎w��ő剹��
	std::array<bool, seNum> se_loadFlag;			// ���[�h�̃`�F�b�N
	std::array<bool, seNum> se_playFlag;			// �Đ��`�F�b�N
	float se_volumeAdjustment = 1.0f;				// SE�̃��[�U�[���ʒ���

	// BGM�̕ϐ�
	std::array<int, bgmNum> bgm_sound;				// BGM�𐔂����ۑ�����
	std::array<int, bgmNum> bgm_volumeSetMaxVolume;	// SE�̎w��ő剹��
	std::array<bool, seNum> bgm_loadFlag;			// ���[�h�̃`�F�b�N
	std::array<bool, seNum> bgm_playFlag;			// �Đ��`�F�b�N
	float bgm_volumeAdjustment = 1.0f;				// BGM�̃��[�U�[���ʒ���
};