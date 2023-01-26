#include "SoundPross.h"

void SoundProcess::Load(int loadFile, SOUNDNAME_SE name)
{
	// loadFile�Ɋi�[		
	se_sound[static_cast<int>(name)] = loadFile;	// ��ޕʂɃT�E���h�𕪂���
	se_loadFlag[static_cast<int>(name)] = true;		// �t���O��true�ɂ���
}

void SoundProcess::Load(int loadFile, SOUNDNAME_BGM name)
{
	// loadFile�Ɋi�[
	bgm_sound[static_cast<int>(name)] = loadFile;	// ��ޕʂɃT�E���h�𕪂���
	bgm_loadFlag[static_cast<int>(name)] = true;	// �t���O��true�ɂ���
}

void SoundProcess::Init(Scene nowScene)
{
	// �^�C�g���V�[���̃T�E���h������
	if (nowScene == Scene::Title)
	{
		// BGM�̃��[�h
		Load(LoadSoundMem("Resource/Sound/BGM/TitleSceneBGM.mp3"), SOUNDNAME_BGM::TitleSceneBGM);

		// SE�̃��[�h
		Load(LoadSoundMem("Resource/Sound/SE/button.mp3"),SOUNDNAME_SE::Button);
	}

	// �Q�[���V�[���̃T�E���h������
	if (nowScene == Scene::Game)
	{
		// BGM�̃��[�h
		Load(LoadSoundMem("Resource/Sound/BGM/GameSceneBGM.mp3"), SOUNDNAME_BGM::GameSceneBGM);

		// SE�̃��[�h
		Load(LoadSoundMem("Resource/Sound/SE/select07.mp3"), SOUNDNAME_SE::Move);
		Load(LoadSoundMem("Resource/Sound/SE/Zselect.mp3"), SOUNDNAME_SE::Select);
		Load(LoadSoundMem("Resource/Sound/SE/delte.mp3"), SOUNDNAME_SE::Delete);
		Load(LoadSoundMem("Resource/Sound/SE/finish.mp3"), SOUNDNAME_SE::Finish);
		Load(LoadSoundMem("Resource/Sound/SE/button.mp3"), SOUNDNAME_SE::Button);
	}
}

// SE�̍Đ�
void SoundProcess::PlayBackSound(SOUNDNAME_SE name, float volume, bool loopflag)
{
	volume_ = volume;

	// �Z�b�g���ꂽvolume���i�[����
	volume_ = se_volumeAdjustment * defaultSEVol_;

	// ����SE�̍ő剹�ʂ����߂�
	se_volumeSetMaxVolume[static_cast<int>(name)] = static_cast<int>(volume_);

	// SE�̃t���O��true�ɂ���
	se_playFlag[static_cast<int>(name)] = true;

	// ���[�v�t���O
	if (!loopflag)
	{
		// SE�̍Đ��t���O��true�ɂȂ��Ă����特�ʂ�^����
		if (se_playFlag[static_cast<int>(name)])
		{
			// ���ʂ������čĐ����Ȃ���
			ChangeVolumeSoundMem(static_cast<int>(volume_), se_sound[static_cast<int>(name)]);
			PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (se_playFlag[static_cast<int>(name)])
		{
			// ���ʂ������čĐ����Ȃ���
			StopSoundMem(se_sound[static_cast<int>(name)]);
			PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(static_cast<int>(volume_), se_sound[static_cast<int>(name)]);
		}
	}
}

// BGM�̍Đ�
void SoundProcess::PlayBackSound(SOUNDNAME_BGM name, float volume, bool loopflag)
{
	volume_ = volume;

	// �Z�b�g���ꂽvolume���i�[����
	volume_ = bgm_volumeAdjustment * defaultBGMVol_;

	// ����BGM�̍ő剹�ʂ����߂�
	bgm_volumeSetMaxVolume[static_cast<int>(name)] = static_cast<int>(volume_);

	// BGM�̃t���O��true�ɂ���
	bgm_playFlag[static_cast<int>(name)] = true;

	// loop�t���O
	if (!loopflag)
	{
		// BGM�̍Đ��t���O��true�ɂȂ��Ă����特�ʂ�^����
		if (bgm_playFlag[static_cast<int>(name)])
		{
			// ���ʂ������čĐ����Ȃ���
			ChangeVolumeSoundMem(static_cast<int>(volume_), bgm_sound[static_cast<int>(name)]);
			PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		// BGM�̍Đ��t���O��true�ɂȂ��Ă����特�ʂ�^����
		if (bgm_playFlag[static_cast<int>(name)])
		{
			// ���ʂ������čĐ����Ȃ���
			StopSoundMem(bgm_sound[static_cast<int>(name)]);
			PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(static_cast<int>(volume_), bgm_sound[static_cast<int>(name)]);
		}
	}
}

void SoundProcess::SoundStop(SOUNDNAME_SE name)
{
	// SE���~�߂�
	StopSoundMem(se_sound[static_cast<int>(name)]);
}

void SoundProcess::SoundStop(SOUNDNAME_BGM name)
{
	// BGM���~�߂�
	StopSoundMem(bgm_sound[static_cast<int>(name)]);
}
void SoundProcess::SoundPlay(SOUNDNAME_SE name, bool loopflag, float loopTime)
{
	SetLoopPosSoundMem(static_cast<int>(loopTime * 100), se_sound[static_cast<int>(name)]);
	if (!loopflag)
	{
		PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK, false);
	}
	else if (loopflag)
	{
		PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP, false);
	}
	ChangeVolumeSoundMem(static_cast<int>(se_volumeAdjustment * 255), se_sound[static_cast<int>(name)]);
}
void SoundProcess::SoundPlay(SOUNDNAME_BGM name, bool loopflag, float loopTime)
{
	SetLoopPosSoundMem(static_cast<int>(loopTime * 100), bgm_sound[static_cast<int>(name)]);
	if (!loopflag)
	{
		PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK, false);
	}
	else if (loopflag)
	{
		PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP, false);
	}
	ChangeVolumeSoundMem(static_cast<int>(bgm_volumeAdjustment * 255), bgm_sound[static_cast<int>(name)]);
}
void SoundProcess::Release()
{
	// SE������
	for (int i = 0; i != seNum; ++i)
	{
		if (!se_loadFlag[i])
		{
			continue;
		}
		DeleteSoundMem(se_sound[i]);
		se_sound[i] = -1;
	}

	// BGM������
	for (int i = 0; i != bgmNum; ++i)
	{
		if (!bgm_loadFlag[i])
		{
			continue;
		}
		StopSoundMem(bgm_sound[i]);
		DeleteSoundMem(bgm_sound[i]);
		bgm_sound[i] = -1;
	}
}

void SoundProcess::Release(SOUNDNAME_SE name)
{
	DeleteSoundMem(se_sound[static_cast<int>(name)]);
}

void SoundProcess::Release(SOUNDNAME_BGM name)
{
	DeleteSoundMem(bgm_sound[static_cast<int>(name)]);
}

void SoundProcess::SetSEVolumeEntire(float volumeEntire)
{
	se_volumeAdjustment = volumeEntire;
}

float SoundProcess::GetSEVolumeEntire()
{
	return se_volumeAdjustment;
}

void SoundProcess::SetBGMVolumeEntire(float volumeEntire)
{
	bgm_volumeAdjustment = volumeEntire;
}

float SoundProcess::GetBGMVolumeEntire()
{
	return bgm_volumeAdjustment;
}

void SoundProcess::SetDefaultVolume(float defaultVol)
{
	defaultSEVol_ = defaultVol;
}

float SoundProcess::GetDefaultVolume()
{
	return defaultSEVol_;
}

void SoundProcess::SetVolume(float volume)
{
	volume_ = volume;
}

float SoundProcess::GetVolume()
{
	return volume_;
}


SoundProcess::SoundProcess()
{
}

SoundProcess::~SoundProcess()
{
}
