#include<DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "../common/SoundPross.h"

GameScene::GameScene()
{
	Init();

	// ゲームシーンのサウドの初期化
	lpSooundPross.Init(Scene::Game);

	// BGMの再生
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::GameSceneBGM, lpSooundPross.GetVolume(), true);

	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
	// サウンドのリリース
	lpSooundPross.Release(SOUNDNAME_BGM::GameSceneBGM);
	lpSooundPross.Release(SOUNDNAME_SE::Delete);
	lpSooundPross.Release(SOUNDNAME_SE::Finish);
	lpSooundPross.Release(SOUNDNAME_SE::Select);
}

bool GameScene::Init(void)
{
	// ブロッククラスのインスタンス
	block_ = std::make_unique<Block>();


	return true;
}

uniqueScene GameScene::Updata(double delta, uniqueScene ownScene)
{
	key_.GetKey();	// キーの情報取得
	block_->Update();

	// シーン分岐（ゲームクリア、ゲームオーバー）
	if (block_->GetLimitTime() < 0.0f)
	{
		if (key_.input[KEY_INPUT_SPACE] == 1)
		{
			lpSooundPross.PlayBackSound(SOUNDNAME_SE::Button, lpSooundPross.GetVolume(), false);
			return std::make_unique<TitleScene>();
		}
	}
	DrawOwnScreen(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(double delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	block_->Draw();
}