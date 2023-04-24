#pragma once
#include <list>
#include <memory>
#include "image.h"
#include "../common/Vector2.h"
#include "../common/Dec.h"

constexpr int blockNumX = 6;	// �u���b�N�̐��i������)
constexpr int blockNumY = 6;	// �u���b�N�̐��i�c�����j

// ���݂̃u���b�N�̏��
struct NowBlock
{
	int Type[blockNumX][blockNumY];
	int  Drop[blockNumX][blockNumY];
	bool Del[blockNumX][blockNumY];
};

class Block
{
public:
	Block();
	~Block();

	void Update(void);
	void Draw(void);

	// get�֐�
	int GetScore();							// �X�R�A�̎擾
	float GetLimitTime(void);				// �������Ԃ̎擾

private:
	void Init(void);

	void Move(void);
	void DeleBlock(void);
	void DownBlock(void);

	unsigned int score_ = 0;				// �X�R�A

	// �L�[����
	Key key_;

	int keyCount_ = 0;
	// �u���b�N�̑傫��
	double blockMult_ = 0.0;

	// �u���b�N��Val�l
	int BlockValX = 80;
	int BlockValY = 200;

	// �{�b�N�X��Val�l
	int boxValX = 35;
	int boxValY = 155;

	// �u���b�N�̔z�u
	int block_hight_ = 6;
	int block_witdh_ = 6;

	// �摜�̑傫���ƍ��W
	Vector2 blockpos_;
	Vector2 blockSize_ = { 96,96 };

	unsigned int ZkeyCount_ = 0;				// Z�L�[�J�E���^�[

	Vector2 boxpos_;
	Vector2 boxSelpos_;							// �I��p�̉摜�̍��W

	// �^�C�}�[�n
	float setTime = 5.0f;
	float startTime = 4.0f;
	float limitTime = 60.0f;
	float deltaTime = 0.018f;

	// �t�H���g�摜�̔{����傫��
	double stringExRate_ = 1.0;
	int StringPicSizeX_ = 10;
	int StringPicSizeY_ = 320;

	// �t�H���g�n���h��
	int FontHundle;
	int FontHundle2;
	int blockMoveCountFontHundle;

	// �t�H���g�摜�̍��W
	Vector2 scorePicPos;
	Vector2 clearScorePicPos;
	Vector2 timePicPos;
	Vector2  blockMoveCountPicPos;
	Vector2 rankFontPic;

	NowBlock nowBlock_;		// ���݂̃u���b�N�̍폜
	Image image_;

	// �Z���N�^�[
	int selectImage_;
	int selectPicSizeX = 1019;
	int selectPicSizeY = 767;

	int selSelectorImage_;
	int selSelectorPicSizeX_ = 1019;
	int selSelectorPicSizeY_ = 767;

	// �w�i�摜
	int backImage_;
	int backPicSizeX = 1024;
	int backPicSizeY = 768;

	// �t�H���g�摜
	int ClearScorePic_;
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	// �����N�摜
	int rankS_;
	int rankA_;
	int rankB_;
	int rankC_;
	int rankD_;

	// �t�B�j�b�V�����̃����N�摜
	int StopPicS_;
	int StopPicA_;
	int StopPicB_;
	int StopPicC_;
	int StopPicD_;

	// �g�g��
	int blueFrame_;
	int blueFrameBlock_;
	int blueFrameScore_;
	int blueFrameTime_;
	int blueFrameMove_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// ���[�v���ŏ��������̂ݍs���p�̃J�E���g�ϐ�
	int count_ = 0;

	// �_�ŃJ�E���g
	int stringCount_ = 0;
};

