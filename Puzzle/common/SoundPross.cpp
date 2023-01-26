#include "SoundPross.h"

void SoundProcess::Load(int loadFile, SOUNDNAME_SE name)
{
	// loadFileに格納		
	se_sound[static_cast<int>(name)] = loadFile;	// 種類別にサウンドを分ける
	se_loadFlag[static_cast<int>(name)] = true;		// フラグをtrueにする
}

void SoundProcess::Load(int loadFile, SOUNDNAME_BGM name)
{
	// loadFileに格納
	bgm_sound[static_cast<int>(name)] = loadFile;	// 種類別にサウンドを分ける
	bgm_loadFlag[static_cast<int>(name)] = true;	// フラグをtrueにする
}

void SoundProcess::Init(Scene nowScene)
{
	// タイトルシーンのサウンド初期化
	if (nowScene == Scene::Title)
	{
		// BGMのロード
		Load(LoadSoundMem("Resource/Sound/BGM/TitleSceneBGM.mp3"), SOUNDNAME_BGM::TitleSceneBGM);

		// SEのロード
		Load(LoadSoundMem("Resource/Sound/SE/button.mp3"),SOUNDNAME_SE::Button);
	}

	// ゲームシーンのサウンド初期化
	if (nowScene == Scene::Game)
	{
		// BGMのロード
		Load(LoadSoundMem("Resource/Sound/BGM/GameSceneBGM.mp3"), SOUNDNAME_BGM::GameSceneBGM);

		// SEのロード
		Load(LoadSoundMem("Resource/Sound/SE/select07.mp3"), SOUNDNAME_SE::Move);
		Load(LoadSoundMem("Resource/Sound/SE/Zselect.mp3"), SOUNDNAME_SE::Select);
		Load(LoadSoundMem("Resource/Sound/SE/delte.mp3"), SOUNDNAME_SE::Delete);
		Load(LoadSoundMem("Resource/Sound/SE/finish.mp3"), SOUNDNAME_SE::Finish);
		Load(LoadSoundMem("Resource/Sound/SE/button.mp3"), SOUNDNAME_SE::Button);
	}
}

// SEの再生
void SoundProcess::PlayBackSound(SOUNDNAME_SE name, float volume, bool loopflag)
{
	volume_ = volume;

	// セットされたvolumeを格納する
	volume_ = se_volumeAdjustment * defaultSEVol_;

	// 流すSEの最大音量を決める
	se_volumeSetMaxVolume[static_cast<int>(name)] = static_cast<int>(volume_);

	// SEのフラグをtrueにする
	se_playFlag[static_cast<int>(name)] = true;

	// ループフラグ
	if (!loopflag)
	{
		// SEの再生フラグがtrueになっていたら音量を与える
		if (se_playFlag[static_cast<int>(name)])
		{
			// 音量を消して再生しなおす
			ChangeVolumeSoundMem(static_cast<int>(volume_), se_sound[static_cast<int>(name)]);
			PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (se_playFlag[static_cast<int>(name)])
		{
			// 音量を消して再生しなおす
			StopSoundMem(se_sound[static_cast<int>(name)]);
			PlaySoundMem(se_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(static_cast<int>(volume_), se_sound[static_cast<int>(name)]);
		}
	}
}

// BGMの再生
void SoundProcess::PlayBackSound(SOUNDNAME_BGM name, float volume, bool loopflag)
{
	volume_ = volume;

	// セットされたvolumeを格納する
	volume_ = bgm_volumeAdjustment * defaultBGMVol_;

	// 流すBGMの最大音量を決める
	bgm_volumeSetMaxVolume[static_cast<int>(name)] = static_cast<int>(volume_);

	// BGMのフラグをtrueにする
	bgm_playFlag[static_cast<int>(name)] = true;

	// loopフラグ
	if (!loopflag)
	{
		// BGMの再生フラグがtrueになっていたら音量を与える
		if (bgm_playFlag[static_cast<int>(name)])
		{
			// 音量を消して再生しなおす
			ChangeVolumeSoundMem(static_cast<int>(volume_), bgm_sound[static_cast<int>(name)]);
			PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		// BGMの再生フラグがtrueになっていたら音量を与える
		if (bgm_playFlag[static_cast<int>(name)])
		{
			// 音量を消して再生しなおす
			StopSoundMem(bgm_sound[static_cast<int>(name)]);
			PlaySoundMem(bgm_sound[static_cast<int>(name)], DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(static_cast<int>(volume_), bgm_sound[static_cast<int>(name)]);
		}
	}
}

void SoundProcess::SoundStop(SOUNDNAME_SE name)
{
	// SEを止める
	StopSoundMem(se_sound[static_cast<int>(name)]);
}

void SoundProcess::SoundStop(SOUNDNAME_BGM name)
{
	// BGMを止める
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
	// SEを消す
	for (int i = 0; i != seNum; ++i)
	{
		if (!se_loadFlag[i])
		{
			continue;
		}
		DeleteSoundMem(se_sound[i]);
		se_sound[i] = -1;
	}

	// BGMを消す
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
