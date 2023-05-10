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
};