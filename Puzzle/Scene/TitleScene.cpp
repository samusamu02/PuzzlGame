#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "../Scene/SceneMag.h"
#include "../common/Dec.h"
#include "../common/SoundPross.h"
TitleScene::TitleScene()
{
	// イニシャライズを呼び出し忘れ防止
	Init();

	// タイトルシーン用の
	lpSooundPross.Init(Scene::Title);

	// タイトルシーンのBGM再生
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::TitleSceneBGM, lpSooundPross.GetVolume(), true);

	// 黒い画面が出るのでダミーで一度描画処理をする
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
	// サウドのリリース
	lpSooundPross.Release(SOUNDNAME_BGM::TitleSceneBGM);
}

bool TitleScene::Init(void)
{
	TitlePic_ = LoadGraph("Resource/img/TitlePic.png");
	PlayKeyPic_ = LoadGraph("Resource/img/press th space key.png");
	TitleBackGPic_ = LoadGraph("Resource/img/nightbackgroundwithmoon.png");
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

	DrawOwnScreen(delta);		// 自分のスクリーン対して描画情報を与える
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, TitleBackGPic_, true);
	DrawRotaGraph((titlePos_.x_ + (titlePicSizeX_ / 2)) + 250, titlePos_.y_ + (titlePicSizeY_ / 2) + 150, titleExrate, 0.0, TitlePic_, true);
	// 徐々に小さくする
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
			DrawGraph(playKeyPicPos_.x_ + (titlePicSizeX_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSizeY_ / 2) + 350, PlayKeyPic_, true);
		}
		count++;
	}
}