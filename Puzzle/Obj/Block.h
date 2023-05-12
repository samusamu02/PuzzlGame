#pragma once
#include <array>
#include "../common/Vector2.h"
#include "../common/Dec.h"

constexpr int blockNumX = 6;	// �u���b�N�̐��i������)
constexpr int blockNumY = 6;	// �u���b�N�̐��i�c�����j

// ���݂̃u���b�N�̏��
struct NowBlock
{
	int blockType[blockNumX][blockNumY];
	int  bolockDrop_[blockNumX][blockNumY];
	bool blockDelete_[blockNumX][blockNumY];
};

class Block
{
public:

	Block();
	~Block();

	//�@�X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// get�֐�
	int GetScore();				// �X�R�A�̎擾
	float GetLimitTime(void);	// �������Ԃ̎擾

private:
	// ����������
	void Init(void);

	// �u���b�N�̉摜�̃��[�h
	void LoadBlockPic(void);

	// �����N�̉摜�̃��[�h
	void LoadRankPic(void);

	// �I�����̃����N�̉摜�̃��[�h
	void LoadFinishRankPic(void);

	// �g�g�݂̉摜�̃��[�h
	void LoadFramePic(void);

	// �u���b�N�̈ړ�����
	void ControlBlock(void);

	// �u���b�N�̍X�V����
	void UpdateBlock(void);

	// �u���b�N�̍폜����
	void DeleBlock(void);

	// �u���b�N�̗�������
	void DownBlock(void);

	// �L�[����
	Key key_;

	// ���݂̃u���b�N
	NowBlock nowBlock_;	

	// �u���b�N�̍��W
	Vector2 blockPos_;

	// �u���b�N�̃T�C�Y
	Vector2 blockSize_ = { 96,96 };

	// �{�b�N�X�̍��W
	Vector2 boxPos_;

	// �I�����̃{�b�N�X�̍��W
	Vector2 boxSelPos_;							

	// �X�R�A�̃t�H���g�摜�̍��W
	Vector2 scorePicPos_;

	// �^�C���̃t�H���g�摜�̍��W
	Vector2 timePicPos_;

	// �t�H���g�摜�̃T�C�Y
	Vector2 stringPicSize_ = { 10,320 };

	// �u���b�N�̔z�u
	Vector2 blockNum_ = { 6,6 };

	// �u���b�N�̊Ԋu
	Vector2 blockValSize_ = { 80,200 };

	// �{�b�N�X�̃T�C�Y
	Vector2 boxSize_ = { 35,155 };

	// �w�i�̉摜�̃T�C�Y
	Vector2 backPicSize_ = { 1024,768 };

	// �u���b�N�̑傫��
	double blockMult_ = 0.0;

	// �t�H���g�摜�̔{����傫��
	double stringExRate_ = 1.0;

	// �^�C�}�[�n
	float setTime_ = 5.0f;
	float startTime = 4.0f;
	float limitTime = 60.0f;
	float deltaTime = 0.018f;

	// �u���b�N�摜
	std::array<int, 10> blockPic_;

	// �����N�摜
	std::array<int, 5> rankPic_;

	// �t�B�j�b�V�����̃����N�摜
	std::array<int, 5> finishPic_;

	// �w�i�摜
	int backImage_;

	// �X�R�A
	unsigned int score_ = 0;				

	// Z�L�[�J�E���^�[
	unsigned int zkeyCount_ = 0;

	// �t�H���g�n���h��
	int fontHandle_a_;
	int fontHandle_b_;
	int blockMoveCountFontHandle_;

	// �t�H���g�摜
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	// �g�g��
	int blueFrame_;
	int blueFrameBlock_;
	int blueFrameScore_;
	int blueFrameTime_;
	int blueFrameMove_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// ���[�v���ŏ��������̂ݍs���p�̃J�E���g�ϐ�
	int loopcount_ = 0;

	// �_�ŃJ�E���g
	int stringCount_ = 0;
};

