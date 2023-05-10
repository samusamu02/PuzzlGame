#include <DxLib.h>
#include <time.h>
#include <math.h>
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
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// �u���b�N�������_���ɕ\��
			nowBlock_.blockType[x][y] = GetRand(9);

			// �l�̏�����
			nowBlock_.blockDelete_[x][y] = 0;
			nowBlock_.bolockDrop_[x][y] = 0;
		}
	}

	// �摜�̓ǂݍ���
	image_.LoadImg();

	// �w�i
	backImage_ = LoadGraph("Resource/img/Summer2.jpg");

	// �t�H���g���ߍ���
	timePic_ = LoadGraph("Resource/img/Time.png");
	blockMoveCountPic_ = LoadGraph("Resource/img/Move.png");
	conditionPic_ = LoadGraph("Resource/img/ClearString.png");
	scorePic_ = LoadGraph("Resource/img/ScorePic.png");
	rankS_ = LoadGraph("Resource/img/S.png");
	rankA_ = LoadGraph("Resource/img/A.png");
	rankB_ = LoadGraph("Resource/img/B.png");
	rankC_ = LoadGraph("Resource/img/C.png");
	rankD_ = LoadGraph("Resource/img/D.png");
	StopPicS_ = LoadGraph("Resource/img/stopPic_S.png");
	StopPicA_ = LoadGraph("Resource/img/stopPic_A.png");
	StopPicB_ = LoadGraph("Resource/img/stopPic_B.png");
	StopPicC_ = LoadGraph("Resource/img/stopPic_C.png");
	StopPicD_ = LoadGraph("Resource/img/stopPic_D.png");

	// �g�g��
	blueFrameBlock_ = LoadGraph("Resource/img/blueBlockFrame.png");
	blueFrameMove_ = LoadGraph("Resource/img/blueFrameMove.png");
	blueFrameCong_ = LoadGraph("Resource/img/blueConditionFrame.png");
	blueFrameTimeAndUntilscore_ = LoadGraph("Resource/img/blueFrameTimeAndUntilscore.png");

	// �t�H���g�̐ݒ�
	FontHundle = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 65, NULL, DX_FONTTYPE_ANTIALIASING);
	FontHundle2 = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 70, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHundle = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 30, NULL, DX_FONTTYPE_ANTIALIASING);
}

void Block::Update(void)
{
	// �J�n�̉��o
	if (blockMult_ < 6.0)
	{
		blockMult_ += 0.05;
	}

	// �u���b�N�̈ړ�����
	MoveBlock();

	// �u���b�N�̍X�V����
	UpdateBlock();

	// �u���b�N�̗�������
	DownBlock();
}

void Block::MoveBlock(void)
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
				boxpos_.x_ = boxpos_.x_ + blockSize_.x_;
				// �͈�
				if (boxpos_.x_ > (blockSize_.x_ * 5))
				{
					boxpos_.x_ = blockSize_.x_ * 5;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::MoveBlock,lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_LEFT] == 1)
			{
				boxpos_.x_ = boxpos_.x_ - blockSize_.x_;
				if (boxpos_.x_ < 0)
				{
					boxpos_.x_ = 0;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::MoveBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_UP] == 1)
			{
				boxpos_.y_ = boxpos_.y_ - blockSize_.y_;
				if (boxpos_.y_ < 0)
				{
					boxpos_.y_ = 0;
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::MoveBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_DOWN] == 1)
			{
				boxpos_.y_ = boxpos_.y_ + blockSize_.y_;
				if (boxpos_.y_ > (blockSize_.y_ * 5))
				{
					boxpos_.y_ = (blockSize_.y_ * 5);
				}

				// �T�E���h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::MoveBlock, lpSooundPross.GetVolume(), false);
			}

			if (key_.input[KEY_INPUT_Z] == 1)
			{
				boxSelpos_ = boxpos_;
				ZkeyCount_++;

				// �T�E�h�̍Đ�
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::Select, lpSooundPross.GetVolume(), false);
			}
		}
	}
}

void Block::UpdateBlock(void)
{
	if (ZkeyCount_ == 1)
	{
		// �ꎞ�ϐ��œ���ւ�����
		int change_block;
		change_block = nowBlock_.blockType[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_];
		nowBlock_.blockType[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_] = nowBlock_.blockType[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_];
		nowBlock_.blockType[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_] = change_block;

		boxSelpos_.x_ = boxpos_.x_;
		boxSelpos_.y_ = boxpos_.y_;
	}
	else if (ZkeyCount_ == 2 || setTime < 0)
	{
		// �u���b�N���폜
		DeleBlock();

		ZkeyCount_ = 0;

		for (int y = 0; y < block_hight_; y++)
		{
			for (int x = 0; x < block_witdh_; x++)
			{
				// �u���b�N����������
				if (nowBlock_.blockType[x][y] == -1)
				{
					nowBlock_.blockType[x][y] = GetRand(5);	// �Ĕz�u
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
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_ - 2; x++)
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
					nowBlock_.blockDelete_[x + i][y] = 1;	// ������v������u���b�N������
				}
			}
		}
	}
	// Y�����̏����鏈��
	for (int y = 0; y < block_hight_ - 2; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
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
					nowBlock_.blockDelete_[x][y + i] = 1;	// ������v������u���b�N������
				}
			}
		}
	}
	// �����������̂Ŏ��ۂɏ����鏈��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
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
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
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
	DrawGraph(720, 400, blockMoveCountPic_, true);
	DrawGraph(0, 0, conditionPic_, true);
	DrawGraph(0, 0, scorePic_, true);

	// �X�R�A�ɉ����ă����N��ύX
	if (score_ < 3000)
	{
		DrawGraph(0, 0, rankD_, true);
	}
	else if (score_ >= 3000 && score_ < 6000)
	{
		DrawGraph(0, 0, rankC_, true);
	}
	else if (score_ >= 6000 && score_ < 10000)
	{
		DrawGraph(0, 0, rankB_, true);
	}
	else if (score_ >= 10000 && score_ < 20000)
	{
		DrawGraph(0, 0, rankA_, true);
	}
	else if (score_ >= 20000)
	{
		DrawGraph(0, 0, rankS_, true);
	}

	// �g�g�݂̕\��
	DrawGraph(30, -35, blueFrameBlock_, true);
	DrawGraph(0, -30, blueFrameTime_, true);
	DrawGraph(0, -30, blueFrameTimeAndUntilscore_, true);
	DrawGraph(0, -30, blueFrameMove_, true);
	DrawGraph(0, -32, blueFrameCong_, true);

	// �t�H���g
	DrawFormatStringToHandle(800, 350, 0xffa500, FontHundle, "%d", static_cast<int>(limitTime));
	DrawFormatStringToHandle(800, 230, 0xffa500, FontHundle, "%u", score_);

	// �摜�̕`��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			if (nowBlock_.blockType[x][y] != -1)
			{
				// �u���b�N�摜��`�悷��
				DrawRotaGraph(x * blockSize_.x_ + BlockValX + 30, y * blockSize_.y_ + BlockValY, blockMult_, 0, image_.blockPic_[nowBlock_.blockType[x][y]], true);
			}


			if (blockMult_ >= 6)
			{
				// �I��p�̃u���b�N
				if ((static_cast<int>(limitTime) >= 0))
				{
					if (x == boxpos_.x_ / blockSize_.x_ &&
						y == boxpos_.y_ / blockSize_.y_)
					{
						// Z�L�[�̏�Ԃɂ��{�b�N�X�̐F�𔃂���
						switch (ZkeyCount_)
						{
						case 0:
							setTime = 5;
							DrawBox(boxpos_.x_ + boxValX + 30, boxpos_.y_ + boxValY, boxpos_.x_ + blockSize_.x_ + boxValX + 30, boxpos_.y_ + blockSize_.y_ + boxValY, 0x00ffff, false);
							break;
						case 1:
							DrawBox(boxSelpos_.x_ + boxValX + 30, boxSelpos_.y_ + boxValY, boxSelpos_.x_ + blockSize_.x_ + boxValX + 30, boxSelpos_.y_ + blockSize_.y_ + boxValY, 0xff00ff, false);

							// �u���b�N�������鎞�Ԃ��v��
							if (setTime >= 0)
							{
								setTime -= deltaTime;
							}
							else if (setTime <= 0)
							{
								ZkeyCount_ = 0;
							}
							DrawFormatString(boxSelpos_.x_ + boxValX + 30, boxSelpos_.y_ + boxValY, 0x0000ff, "%d", static_cast<int>(setTime));

							break;
						}
					}
				}
			}
		}
	}

	if ((static_cast<int>(limitTime <= 0)))
	{
		for (int y = 0; y < block_hight_; y++)
		{
			for (int x = 0; x < block_witdh_; x++)
			{
				// �u���b�N�Ƀt�B���^�[���|����
				GraphFilter(image_.blockPic_[nowBlock_.blockType[x][y]], DX_GRAPH_FILTER_MONO, -1, 45);

				// �����N������
				if (score_ < 3000)
				{
					// �����ND
					DrawGraph(0, 0, StopPicD_, true);
				}
				else if (score_ >= 3000 && score_ < 6000)
				{
					// �����NC
					DrawGraph(0, 0, StopPicC_, true);
				}
				else if (score_ >= 6000 && score_ < 10000)
				{
					// �����NB
					DrawGraph(0, 0, StopPicB_, true);
				}
				else if (score_ >= 10000 && score_ < 20000)
				{
					// �����NA
					DrawGraph(0, 0, StopPicA_, true);
				}
				else if (score_ >= 20000)
				{
					// �����NS
					DrawGraph(0, 0, StopPicS_, true);
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
	if (count_ == 0)
	{
		if (limitTime <= 0.0)
		{
			count_++;
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

