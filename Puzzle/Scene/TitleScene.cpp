#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "../Scene/SceneMag.h"
#include "../common/Dec.h"
#include "../common/SoundPross.h"
TitleScene::TitleScene()
{
	// �C�j�V�����C�Y���Ăяo���Y��h�~
	Init();

	// �^�C�g���V�[���p��
	lpSooundPross.Init(Scene::Title);

	// �^�C�g���V�[����BGM�Đ�
	lpSooundPross.PlayBackSound(SOUNDNAME_BGM::TitleSceneBGM, lpSooundPross.GetVolume(), true);

	// ������ʂ��o��̂Ń_�~�[�ň�x�`�揈��������
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
	// �T�E�h�̃����[�X
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
	// �L�[�̏��擾
	key_.GetKey();	

	// �X�y�[�X�L�[����������Q�[���V�[���ֈڍs����
	if (key_.input[KEY_INPUT_SPACE] == 1)
	{
		lpSooundPross.PlayBackSound(SOUNDNAME_SE::Button, lpSooundPross.GetVolume(), false);
		return std::make_unique<GameScene>();
	}

	DrawOwnScreen(delta);		// �����̃X�N���[���΂��ĕ`�����^����
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, TitleBackGPic_, true);
	DrawRotaGraph((titlePos_.x_ + (titlePicSizeX_ / 2)) + 250, titlePos_.y_ + (titlePicSizeY_ / 2) + 150, titleExrate, 0.0, TitlePic_, true);
	// ���X�ɏ���������
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
			DrawGraph(playKeyPicPos_.x_ + (titlePicSizeX_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSizeY_ / 2) + 350, PlayKeyPic_, true);
		}
		count++;
	}
}