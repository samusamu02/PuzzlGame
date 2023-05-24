#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "../Scene/SceneMag.h"
#include "../common/Dec.h"
#include "../common/SoundPross.h"
TitleScene::TitleScene()
{
	// �����������Ăяo��
	Init();

	// �^�C�g���V�[���p��
	lpSooundPross.Init(Scene::Title);

	// �^�C�g���V�[����BGM�Đ�
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::TitleSceneBGM, lpSooundPross.GetVolume(), true);

	// �o�O�΍�Ƃ��ĕ`�揈�����ɌĂ�
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
	// �T�E�h�̃����[�X
	lpSooundPross.Release(SOUNDNAME_BGM::TitleSceneBGM);
}

bool TitleScene::Init(void)
{
	// �^�C�g���̔w�i
	titleBackPic_ = LoadGraph("Resource/img/nightbackgroundwithmoon.png");

	// �^�C�g���̃��S
	titlePic_ = LoadGraph("Resource/img/TitlePic.png");

	// �L�[���͑ҋ@
	playKeyPic_ = LoadGraph("Resource/img/press th space key.png");

	// �^�C�g�����S�̊g��{��
	titleExrate = 0.0;

	// �^�C�g�����S�̍��W
	titlePicPos_ = { 0,0 };

	// �^�C�g�����S�̃T�C�Y
	titlePicSize_ = { 640,320 };

	// �L�[���͂̉摜�̍��W
	playKeyPicPos_ = { 0,0 };

	// �L�[���͑ҋ@�̉摜�̃T�C�Y
	playKeyPicSize_ = { 640,320 };

	// �_�ŗp�̃J�E���^�[�ϐ�
	count = 0;

	return true;
}

uniqueScene TitleScene::Updata(double delta, uniqueScene ownScene)
{
	// �L�[�̏��擾
	key_.GetKey();	

	// �X�y�[�X�L�[����������Q�[���V�[���ֈڍs����
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
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// �w�i�̕`��
	DrawGraph(0, 0, titleBackPic_, true);

	// �^�C�g�����S�̕`��
	DrawRotaGraph((titlePicPos_.x_ + (titlePicSize_.x_ / 2)) + 250, titlePicPos_.y_ + (titlePicSize_.y_ / 2) + 150, titleExrate, 0.0, titlePic_, true);

	// ���X�ɑ傫������
	if (titleExrate < 1.0)
	{
		titleExrate += 0.01;
	}
	// �^�C�g�����S�̑傫����1�ɂȂ�����
	if (titleExrate >= 1.0)
	{
		// �_�ŕ\��
		if ((count / 50) % 2 == 0)
		{
			DrawGraph(playKeyPicPos_.x_ + (playKeyPicSize_.x_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSize_.y_ / 2) + 350, playKeyPic_, true);
		}
		count++;
	}
}