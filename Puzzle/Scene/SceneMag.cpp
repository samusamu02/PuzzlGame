#include <DxLib.h>
#include <memory>
#include <chrono>
#include "SceneMag.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../common/Dec.h"

// スクリーンサイズ
constexpr int ScreenSizeX = 1024;
constexpr int ScreenSizeY = 768;

// キー情報
Key key;

// メインループ
void SceneMag::Run(void)
{
	// 初期化フラグ
	if (!initFlag_)
	{
		if (!SysInit())
		{
			return;
		}
	}

	// 初期シーンのインスタンス
	// TitleSceneの実態を生成
	scene_ = std::make_unique<TitleScene>();

	std::chrono::system_clock::time_point nowTime, oldTime;
	nowTime = std::chrono::system_clock::now();
	while (ProcessMessage() == 0 && key.GetKey() == 0 && key.input[KEY_INPUT_ESCAPE] == 0)
	{
		// デルタタイムの計算
		oldTime = nowTime;
		nowTime = std::chrono::system_clock::now();
		auto elTime = nowTime - oldTime;
		auto msec = std::chrono::duration_cast<std::chrono::microseconds>(elTime).count();
		auto delta = msec / 1000000.0;

		// Updataを呼ぶ
		scene_ = scene_->Updata(delta, std::move(scene_));

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		scene_->Draw(delta);
		ScreenFlip();
	}
}

void SceneMag::Update(void)
{

}

void SceneMag::Draw(void)
{

}

bool SceneMag::SysInit(void)
{
	// Dxlibの初期化
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);
	SetWindowIconID(001);
	ChangeWindowMode(true);
	SetWindowText("クッキーパズル");
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}

SceneMag::SceneMag()
{
	// 初期化成功フラグの取得
	initFlag_ = SysInit();
}

SceneMag::~SceneMag()
{
	
}

