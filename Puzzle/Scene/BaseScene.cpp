#include <DxLib.h>
#include "BaseScene.h"
#include "../common/SoundPross.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);										// �����I�Ƀo�b�N�o�b�t�@���w��
	GetDrawScreenSize(&screenSize_.x_, &screenSize_.y_);				// �`���̃T�C�Y���擾����(�o�b�t�@�j
	screenID_ = MakeScreen(screenSize_.x_, screenSize_.y_, true);		// �X�N���[���̃T�C�Y
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(double delta)
{
	// screenID�ɑ΂��ĕ`��
	DrawGraph(0, 0, screenID_, true);
}