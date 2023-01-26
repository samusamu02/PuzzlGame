#include<DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "../common/SoundPross.h"

GameScene::GameScene()
{
	Init();

	// �Q�[���V�[���̃T�E�h�̏�����
	lpSooundPross.Init(Scene::Game);

	// BGM�̍Đ�
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::GameSceneBGM, lpSooundPross.GetVolume(), true);

	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
	// �T�E���h�̃����[�X
	lpSooundPross.Release(SOUNDNAME_BGM::GameSceneBGM);
	lpSooundPross.Release(SOUNDNAME_SE::Delete);
	lpSooundPross.Release(SOUNDNAME_SE::Finish);
	lpSooundPross.Release(SOUNDNAME_SE::Select);
}

bool GameScene::Init(void)
{
	// �u���b�N�N���X�̃C���X�^���X
	block_ = std::make_unique<Block>();


	return true;
}

uniqueScene GameScene::Updata(double delta, uniqueScene ownScene)
{
	key_.GetKey();	// �L�[�̏��擾
	block_->Update();

	// �V�[������i�Q�[���N���A�A�Q�[���I�[�o�[�j
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
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	block_->Draw();
}