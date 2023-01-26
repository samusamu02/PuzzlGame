#pragma once
#include <DxLib.h>
#include <array>
class Image
{
public:
	std::array<int,10> blockPic_;
	void LoadImg(void)
	{
		blockPic_[0] = LoadGraph("Resource/img/cookies_001.png");
		blockPic_[1] = LoadGraph("Resource/img/cookies_002.png");
		blockPic_[2] = LoadGraph("Resource/img/cookies_003.png");
		blockPic_[3] = LoadGraph("Resource/img/cookies_004.png");
		blockPic_[4] = LoadGraph("Resource/img/cookies_011.png");
		blockPic_[5] = LoadGraph("Resource/img/cookies_010.png");
		blockPic_[6] = LoadGraph("Resource/img/cookies_009.png");
		blockPic_[7] = LoadGraph("Resource/img/cookies_013.png");
		blockPic_[8] = LoadGraph("Resource/img/cookies_020.png");
		blockPic_[9] = LoadGraph("Resource/img/cookies_019.png");
	}
	
	int explode[16];
	void LoadExplode(void)
	{
		LoadDivGraph("Resource/img/Exprosion.png", 16, 4, 4, 64, 64, explode, true);
	}

	int cntPic_[5];
	int cntPushPic_[5];
	void LoadCntImg(void)
	{

		cntPic_[0] = LoadGraph("Resource/img/Keyboard_Up.png");
		cntPic_[1] = LoadGraph("Resource/img/Keyboard_Down.png");
		cntPic_[2] = LoadGraph("Resource/img/Keyboard_Left.png");
		cntPic_[3] = LoadGraph("Resource/img/Keyboard_Right.png");
		cntPic_[4] = LoadGraph("Resource/img/Keyboard_Z.png");

		cntPushPic_[0] = LoadGraph("Resource/img/Keyboard_pushUp.png");
		cntPushPic_[1] = LoadGraph("Resource/img/Keyboard_pushDown.png");
		cntPushPic_[2] = LoadGraph("Resource/img/Keyboard_pushLeft.png");
		cntPushPic_[3] = LoadGraph("Resource/img/Keyboard_pushRight.png");
		cntPushPic_[4] = LoadGraph("Resource/img/Keyboard_pushZ.png");
	}

	int number[10];
	void NumBerImg(void)
	{
		LoadDivGraph("Resource/img/nunber.png", 10, 10, 1, 45, 320, number, true);
	}
};