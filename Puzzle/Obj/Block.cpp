#include <DxLib.h>
#include <time.h>

#include "Block.h"
#include "../common/SoundPross.h"

Block::Block()
{
	Init();
}

Block::~Block()
{

}

void Block::Init(void)
{
	// �摜�������_���ɕ\��
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// �u���b�N�������_���ɕ\��
			nowBlock_.blockType[x][y] = GetRand(9);

			// �l�̏�����
			nowBlock_.blockDelete_[x][y] = 0;
			nowBlock_.bolockDrop_[x][y] = 0;
		}
	}

	// �w�i
	backImage_ = LoadGraph("Resource/img/Summer2.jpg");

	// �u���b�N�̉摜�̓ǂݍ���
	LoadBlockPic();

	// �����N�̉摜�̓ǂݍ���
	LoadRankPic();

	// �I�����̃����N�̉摜�̓ǂݍ���
	LoadFinishRankPic();

	// �g�g�݂̉摜�̃��[�h
	LoadFramePic();

	// �t�H���g���ߍ���
	timePic_ = LoadGraph("Resource/img/Time.png");
	conditionPic_ = LoadGraph("Resource/img/ClearString.png");
	scorePic_ = LoadGraph("Resource/img/ScorePic.png");

	// �t�H���g�̐ݒ�
	fontHandle_a_ = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 65, NULL, DX_FONTTYPE_ANTIALIASING);
	fontHandle_b_ = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 70, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHandle_ = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 30, NULL, DX_FONTTYPE_ANTIALIASING);
}

void Block::LoadBlockPic(void)
{
	// �摜�̓ǂݍ���
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

void Block::LoadRankPic(void)
{
	// �����N�̉摜�̓ǂݍ���
	rankPic_[0] = LoadGraph("Resource/img/S.png");
	rankPic_[1] = LoadGraph("Resource/img/A.png");
	rankPic_[2] = LoadGraph("Resource/img/B.png");
	rankPic_[3] = LoadGraph("Resource/img/C.png");
	rankPic_[4] = LoadGraph("Resource/img/D.png");
}

void Block::LoadFinishRankPic(void)
{
	// �I�����̃����N�̉摜�̓ǂݍ���
	finishPic_[0] = LoadGraph("Resource/img/stopPic_S.png");
	finishPic_[1] = LoadGraph("Resource/img/stopPic_A.png");
	finishPic_[2] = LoadGraph("Resource/img/stopPic_B.png");
	finishPic_[3] = LoadGraph("Resource/img/stopPic_C.png");
	finishPic_[4] = LoadGraph("Resource/img/stopPic_D.png");
}

void Block::LoadFramePic(void)
{
	// �g�g�݂̉摜�̓ǂݍ���
	blueFrameBlock_ = LoadGraph("Resource/img/blueBlockFrame.png");
	blueFrameMove_ = LoadGraph("Resource/img/blueFrameMove.png");
	blueFrameCong_ = LoadGraph("Resource/img/blueConditionFrame.png");
	blueFrameTimeAndUntilscore_ = LoadGraph("Resource/img/blueFrameTimeAndUntilscore.png");
}

void Block::Update(void)
{
	// �J�n�̉��o
	if (blockMult_ < 6.0)
	{
		blockMult_ += 0.05;
	}

	// �u���b�N�̈ړ�����
	ControlBlock();

	// �u���b�N�̍X�V����
	UpdateBlock();

	// �u���b�N�̗�������
	DownBlock();
}

void Block::ControlBlock(void)
{
	// �L�[���̎擾
	key_.GetKey();	

	// �������Ԃ̊ԃL�[������o����悤�ɂ���
	if (static_cast<int>(limitTime) > 0)
	{
		// �ړ��Ɣ͈͎w��
		if (blockMult_ > 6)
		{
			// �ړ�
			if (key_.input[KEY_INPUT_RIGHT] == 1)
			{
				// 1�u���b�N���i�߂�
				boxPos_.x_ = boxPos_.x_ + blockSize_.x_;
				// �͈�
				if (boxPos_.x_ > (blockSize_.x_ * 5))
				{
					boxPos_.x_ = blockSize_.x_ * 5;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock,lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_LEFT] == 1)
			{
				boxPos_.x_ = boxPos_.x_ - blockSize_.x_;
				if (boxPos_.x_ < 0)
				{
					boxPos_.x_ = 0;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_UP] == 1)
			{
				boxPos_.y_ = boxPos_.y_ - blockSize_.y_;
				if (boxPos_.y_ < 0)
				{
					boxPos_.y_ = 0;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_DOWN] == 1)
			{
				boxPos_.y_ = boxPos_.y_ + blockSize_.y_;
				if (boxPos_.y_ > (blockSize_.y_ * 5))
				{
					boxPos_.y_ = (blockSize_.y_ * 5);
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}

			if (key_.input[KEY_INPUT_Z] == 1)
			{
				boxSelPos_ = boxPos_;
				zkeyCount_++;

				// �T�E�h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::Select, lpSooundPross.GetVolume(), false);
			}
		}
	}
}

void Block::UpdateBlock(void)
{
	if (zkeyCount_ == 1)
	{
		// �ꎞ�ϐ��œ���ւ�����
		int change_block;
		change_block = nowBlock_.blockType[boxPos_.x_ / blockSize_.x_][boxPos_.y_ / blockSize_.y_];
		nowBlock_.blockType[boxPos_.x_ / blockSize_.x_][boxPos_.y_ / blockSize_.y_] = nowBlock_.blockType[boxSelPos_.x_ / blockSize_.x_][boxSelPos_.y_ / blockSize_.y_];
		nowBlock_.blockType[boxSelPos_.x_ / blockSize_.x_][boxSelPos_.y_ / blockSize_.y_] = change_block;

		boxSelPos_.x_ = boxPos_.x_;
		boxSelPos_.y_ = boxPos_.y_;
	}
	else if (zkeyCount_ == 2 || setTime_ < 0)
	{
		// �u���b�N���폜
		DeleBlock();

		zkeyCount_ = 0;

		for (int y = 0; y < blockNum_.y_; y++)
		{
			for (int x = 0; x < blockNum_.x_; x++)
			{
				// �u���b�N����������
				if (nowBlock_.blockType[x][y] == -1)
				{
					// �Ĕz�u
					nowBlock_.blockType[x][y] = GetRand(5);
					nowBlock_.blockDelete_[x][y] = 0;
					nowBlock_.bolockDrop_[x][y] = 0;
				}
			}
		}
	}
}

void Block::DeleBlock(void)
{
	// X�����̏����鏈��
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_ - 2; x++)
		{
			// 3�u���b�N�ȏオ��v���Ă��邩���m�F����
			if (nowBlock_.blockType[x + 0][y] == nowBlock_.blockType[x + 1][y] &&
				nowBlock_.blockType[x + 1][y] == nowBlock_.blockType[x + 2][y] &&
				nowBlock_.blockType[x + 2][y] == nowBlock_.blockType[x + 0][y] &&
				nowBlock_.blockType[x + 0][y] != -1 &&
				nowBlock_.blockType[x + 1][y] != -1 &&
				nowBlock_.blockType[x + 2][y] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					// ������v������u���b�N������
					nowBlock_.blockDelete_[x + i][y] = 1;	
				}
			}
		}
	}
	// Y�����̏����鏈��
	for (int y = 0; y < blockNum_.y_ - 2; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// 3�u���b�N���ȏオ��v���Ă��邩���m�F����
			if (nowBlock_.blockType[x][y + 0] == nowBlock_.blockType[x][y + 1] &&
				nowBlock_.blockType[x][y + 1] == nowBlock_.blockType[x][y + 2] &&
				nowBlock_.blockType[x][y + 2] == nowBlock_.blockType[x][y + 0] &&
				nowBlock_.blockType[x][y + 0] != -1 &&
				nowBlock_.blockType[x][y + 1] != -1 &&
				nowBlock_.blockType[x][y + 2] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					// ������v������u���b�N������
					nowBlock_.blockDelete_[x][y + i] = 1;	
				}
			}
		}
	}
	// �����������̂Ŏ��ۂɏ����鏈��
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// �u���b�N����������
			if (nowBlock_.blockDelete_[x][y] == 1)
			{
				// �Đ�����
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::Delete, lpSooundPross.GetVolume(), false);

				// �l��߂�
				nowBlock_.blockDelete_[x][y] = 0;	
				nowBlock_.blockType[x][y] = -1;
				score_ = score_ + 100;
			}
		}
	}

}

void Block::DownBlock(void)
{
	// �u���b�N����������u���b�N�𗎂Ƃ�
	// �u���b�N���������炠��ꍇ
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			if (nowBlock_.blockType[x][y] != -1)
			{
				for (int ye = y + 1; ye < 6; ye = ye + 1)
				{
					if (nowBlock_.blockType[x][ye] == -1)
					{
						nowBlock_.bolockDrop_[x][y] = nowBlock_.bolockDrop_[x][y] + 1;
					}
				}
			}

			// �����鏈�������ۂɓ�����
			for (int y = 6 - 1; y > -1; y = y - 1)
			{
				for (int x = 0; x < 6; x = x + 1)
				{
					if (nowBlock_.bolockDrop_[x][y] != 0)
					{
						nowBlock_.blockType[x][y + nowBlock_.bolockDrop_[x][y]] = nowBlock_.blockType[x][y];
						nowBlock_.blockType[x][y] = -1;
						nowBlock_.bolockDrop_[x][y + nowBlock_.bolockDrop_[x][y]] = 0;
						nowBlock_.bolockDrop_[x][y] = 0;
					}
				}
			}
		}
	}
}

void Block::Draw(void)
{
	// �u���b�N�̔w�i
	DrawGraph(0, 0, backImage_, true);

	// �����摜�̕`��
	DrawGraph(0,-30, timePic_, true);
	DrawGraph(0, 0, conditionPic_, true);
	DrawGraph(0, 0, scorePic_, true);

	// �X�R�A�ɉ����ă����N��ύX
	if (score_ < 3000)
	{
		DrawGraph(0, 0, rankPic_[4], true);
	}
	else if (score_ >= 3000 && score_ < 6000)
	{
		DrawGraph(0, 0, rankPic_[3], true);
	}
	else if (score_ >= 6000 && score_ < 10000)
	{
		DrawGraph(0, 0, rankPic_[2], true);
	}
	else if (score_ >= 10000 && score_ < 20000)
	{
		DrawGraph(0, 0, rankPic_[1], true);
	}
	else if (score_ >= 20000)
	{
		DrawGraph(0, 0, rankPic_[0], true);
	}

	// �g�g�݂̕\��
	DrawGraph(30, -35, blueFrameBlock_, true);
	DrawGraph(0, -30, blueFrameTime_, true);
	DrawGraph(0, -30, blueFrameTimeAndUntilscore_, true);
	DrawGraph(0, -30, blueFrameMove_, true);
	DrawGraph(0, -32, blueFrameCong_, true);

	// �t�H���g
	DrawFormatStringToHandle(800, 350, 0xffa500, fontHandle_a_, "%d", static_cast<int>(limitTime));
	DrawFormatStringToHandle(800, 230, 0xffa500, fontHandle_a_, "%u", score_);

	// �摜�̕`��
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			if (nowBlock_.blockType[x][y] != -1)
			{
				// �u���b�N�摜��`�悷��
				DrawRotaGraph(
					x * blockSize_.x_ + blockValSize_.x_ + 30,
					y * blockSize_.y_ + blockValSize_.y_, 
					blockMult_, 
					0,
					blockPic_[nowBlock_.blockType[x][y]], 
					true
				);
			}


			if (blockMult_ >= 6)
			{
				// �I��p�̃u���b�N
				if ((static_cast<int>(limitTime) >= 0))
				{
					if (x == boxPos_.x_ / blockSize_.x_ &&
						y == boxPos_.y_ / blockSize_.y_)
					{
						// Z�L�[�̏�Ԃɂ��{�b�N�X�̐F�𔃂���
						switch (zkeyCount_)
						{
						case 0:
							setTime_ = 5;
							DrawBox(boxPos_.x_ + boxSize_.x_ + 30, boxPos_.y_ + boxSize_.y_, boxPos_.x_ + blockSize_.x_ + boxSize_.x_ + 30, boxPos_.y_ + blockSize_.y_ + boxSize_.y_, 0x00ffff, false);
							break;
						case 1:
							DrawBox(boxSelPos_.x_ + boxSize_.x_ + 30, boxSelPos_.y_ + boxSize_.y_, boxSelPos_.x_ + blockSize_.x_ + boxSize_.x_ + 30, boxSelPos_.y_ + blockSize_.y_ + boxSize_.y_, 0xff00ff, false);

							// �u���b�N�������鎞�Ԃ��v��
							if (setTime_ >= 0)
							{
								setTime_ -= deltaTime;
							}
							else if (setTime_ <= 0)
							{
								zkeyCount_ = 0;
							}
							DrawFormatString(boxSelPos_.x_ + boxSize_.x_ + 30, boxSelPos_.y_ + boxSize_.y_, 0x0000ff, "%d", static_cast<int>(setTime_));

							break;
						}
					}
				}
			}
		}
	}

	if ((static_cast<int>(limitTime <= 0)))
	{
		for (int y = 0; y < blockNum_.y_; y++)
		{
			for (int x = 0; x < blockNum_.x_; x++)
			{
				// �u���b�N�Ƀt�B���^�[���|����
				GraphFilter(blockPic_[nowBlock_.blockType[x][y]], DX_GRAPH_FILTER_MONO, -1, 45);

				// �����N������
				if (score_ < 3000)
				{
					// �����ND
					DrawGraph(0, 0, finishPic_[4], true);
				}
				else if (score_ >= 3000 && score_ < 6000)
				{
					// �����NC
					DrawGraph(0, 0, finishPic_[3], true);
				}
				else if (score_ >= 6000 && score_ < 10000)
				{
					// �����NB
					DrawGraph(0, 0, finishPic_[2], true);
				}
				else if (score_ >= 10000 && score_ < 20000)
				{
					// �����NA
					DrawGraph(0, 0, finishPic_[1], true);
				}
				else if (score_ >= 20000)
				{
					// �����NS
					DrawGraph(0, 0, finishPic_[0], true);
				}
			}
		}
	}

	// �ŏ��̃u���b�N���ł�܂ł̎��Ԃ��v������
	if (startTime >= 0)
	{
		startTime -= deltaTime;
	}

	// �ŏ��̃u���b�N�����ׂĕ\�����ꂽ�琧�����Ԃ����炷
	if (startTime <= 0)
	{
		if (limitTime >= 0)
		{
			// �������Ԃ����炷
			limitTime -= deltaTime;
		}
	}
	
	// �������ԂɂȂ�����I���p��SE���Đ�����
	if (loopcount_ == 0)
	{
		if (limitTime <= 0.0)
		{
			loopcount_++;
			lpSooundPross.PlayBackSound(SOUNDNAME_SE::Finish, lpSooundPross.GetVolume(), false);
		}
	}
}

int Block::GetScore()
{
   	return score_;
}

float Block::GetLimitTime(void)
{
	return limitTime;
}

