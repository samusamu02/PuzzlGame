#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "../Scene/SceneMag.h"
#include "../common/Dec.h"
#include "../common/SoundPross.h"
TitleScene::TitleScene()
{
	// 初期化処理呼び出し
	Init();

	// タイトルシーン用の
	lpSooundPross.Init(Scene::Title);

	// タイトルシーンのBGM再生
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::TitleSceneBGM, lpSooundPross.GetVolume(), true);

	// バグ対策として描画処理を先に呼ぶ
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
	// サウドのリリース
	lpSooundPross.Release(SOUNDNAME_BGM::TitleSceneBGM);
}

bool TitleScene::Init(void)
{
	// タイトルの背景
	titleBackPic_ = LoadGraph("Resource/img/nightbackgroundwithmoon.png");

	// タイトルのロゴ
	titlePic_ = LoadGraph("Resource/img/TitlePic.png");

	// キー入力待機
	playKeyPic_ = LoadGraph("Resource/img/press th space key.png");

	// タイトルロゴの拡大倍率
	titleExrate = 0.0;

	// タイトルロゴの座標
	titlePicPos_ = { 0,0 };

	// タイトルロゴのサイズ
	titlePicSize_ = { 640,320 };

	// キー入力の画像の座標
	playKeyPicPos_ = { 0,0 };

	// キー入力待機の画像のサイズ
	playKeyPicSize_ = { 640,320 };

	// 点滅用のカウンター変数
	count = 0;

	return true;
}

uniqueScene TitleScene::Updata(double delta, uniqueScene ownScene)
{
	// キーの情報取得
	key_.GetKey();	

	// スペースキーを押したらゲームシーンへ移行する
	if (key_.input[KEY_INPUT_SPACE] == 1)
	{
		lpSooundPross.PlayBackSound(SOUNDNAME_SE::Button, lpSooundPross.GetVolume(), false);
		return std::make_unique<GameScene>();
	}

	DrawOwnScreen(delta);
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// 背景の描画
	DrawGraph(0, 0, titleBackPic_, true);

	// タイトルロゴの描画
	DrawRotaGraph((titlePicPos_.x_ + (titlePicSize_.x_ / 2)) + 250, titlePicPos_.y_ + (titlePicSize_.y_ / 2) + 150, titleExrate, 0.0, titlePic_, true);

	// 徐々に大きくする
	if (titleExrate < 1.0)
	{
		titleExrate += 0.01;
	}
	// タイトルロゴの大きさが1になったら
	if (titleExrate >= 1.0)
	{
		// 点滅表示
		if ((count / 50) % 2 == 0)
		{
			DrawGraph(playKeyPicPos_.x_ + (playKeyPicSize_.x_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSize_.y_ / 2) + 350, playKeyPic_, true);
		}
		count++;
	}
}