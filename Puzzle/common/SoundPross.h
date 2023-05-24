	#pragma once
#include <DxLib.h>
#include <array>
#include "../Scene/Scene.h"

#define lpSooundPross SoundProcess::GetInstance()

// SEの種類
enum class SOUNDNAME_SE
{
	ControlBlock,
	Select,
	Delete,
	Finish,
	Button,
	Max
};

// BGMの種類
enum class SOUNDNAME_BGM
{
	TitleSceneBGM,
	GameSceneBGM,
	Max
};

// SEの数
constexpr int seNum = static_cast<int>(SOUNDNAME_SE::Max) + 1;		

// BGMの数
constexpr int bgmNum = static_cast<int>(SOUNDNAME_BGM::Max) + 1;			

class SoundProcess
{
public:

	static SoundProcess& GetInstance(void)
	{
		static SoundProcess s_Instance;
		return s_Instance;
	}

	// 初期化
	void Init(Scene nowScene);

	// ロード
	void Load(int loadFile, SOUNDNAME_SE name);		// SEのロード
	void Load(int loadFile, SOUNDNAME_BGM name);	// BGMのロード

	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="volume">音量</param>
	/// <param name="loopflag">ループフラグ</param>
	void PlayBackSound(SOUNDNAME_SE name, float volume, bool loopflag);

	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="volume">音量</param>
	/// <param name="loopflag">ループフラグ</param>
	void PlayBackSound(SOUNDNAME_BGM name, float volume, bool loopflag);

	/// <summary>
	/// SEを止める
	/// </summary>
	/// <param name="name">名前</param>
	void SoundStop(SOUNDNAME_SE name);

	/// <summary>
	/// BGMを止める
	/// </summary>
	/// <param name="name">名前</param>
	void SoundStop(SOUNDNAME_BGM name);

	/// 止めていたSEを再生する
	/// <name> 流したいSEを指定
	/// <loopflag> ループをするかを指定
	/// <loopTime> 曲が流れて何秒立ったかの指定
	void SoundPlay(SOUNDNAME_SE name, bool loopflag, float loopTime);

	/// 止めていたBGMを再生する
	/// <name> 流したいBGMを指定
	/// <loopflag> ループをするかを指定
	/// <loopTime> 曲が流れて何秒立ったかの指定
	void SoundPlay(SOUNDNAME_BGM name, bool loopflag, float loopTime);

	// 解放
	void Release();
	void Release(SOUNDNAME_SE name);
	void Release(SOUNDNAME_BGM name);

	// SEのユーザー音量調整を設定
	void SetSEVolumeEntire(float UserSetVolume);

	// SEのユーザー音量調整を渡す
	float GetSEVolumeEntire();

	// BGMのユーザー音量調整を設定
	void SetBGMVolumeEntire(float UserSetVolume);

	// BGMのユーザー音量調整を渡す
	float GetBGMVolumeEntire();

	// 標準の音量をセットする
	void SetDefaultVolume(float defaultVol);

	// 標準の音量を取得する
	float GetDefaultVolume();

	// ボリュームをセットする
	void SetVolume(float volume);

	// ボリュームを取得する
	float GetVolume();

private:
	SoundProcess();
	~SoundProcess();

	// ボリューム関係
	float volume_ = 255.0f;				// ボリューム
	float defaultSEVol_ = 200.5f;		// デフォルトのSEのボリューム
	float defaultBGMVol_ = 150.5f;		// デフォルトのBGMのボリューム

	// SEの変数
	std::array<int, seNum> se_sound;				// seを数だけ保存
	std::array<int, seNum> se_volumeSetMaxVolume;	// SEの指定最大音量
	std::array<bool, seNum> se_loadFlag;			// ロードのチェック
	std::array<bool, seNum> se_playFlag;			// 再生チェック
	float se_volumeAdjustment = 1.0f;				// SEのユーザー音量調整

	// BGMの変数
	std::array<int, bgmNum> bgm_sound;				// BGMを数だけ保存する
	std::array<int, bgmNum> bgm_volumeSetMaxVolume;	// SEの指定最大音量
	std::array<bool, seNum> bgm_loadFlag;			// ロードのチェック
	std::array<bool, seNum> bgm_playFlag;			// 再生チェック
	float bgm_volumeAdjustment = 1.0f;				// BGMのユーザー音量調整
};