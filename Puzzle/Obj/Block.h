#pragma once
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "../common/Dec.h"

constexpr int blockNumX = 6;	// �u���b�N�̐��i������)
constexpr int blockNumY = 6;	// �u���b�N�̐��i�c�����j

// ���݂̃u���b�N�̏��
struct NowBlock
{
	std::vector<std::vector<int>> blockType;
	std::vector<std::vector<int>> blockDrop_;
	std::vector<std::vector<bool>> blockDelete_;
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
	void LoadBackPic(void);

	// �t�H���g�̃��[�h
	void LoadFontPic(void);

	// �u���b�N�̈ړ�����
	void ControlBlock(void);

	// �u���b�N�̍X�V����
	void UpdateBlock(void);

	// �u���b�N�̍폜����
	void DeleBlock(void);

	// �u���b�N�̗�������
	void DownBlock(void);

	void DrawBG(void);

	// �u���b�N�̕`�揈��
	void DrawBlock(void);

	void DrawSelector(void);

	void DrawFont(void);

	void DrawRank(void);

	void DrawFinishRank(void);

	// �L�[����
	Key key_;

	// ���݂̃u���b�N
	NowBlock nowBlock_;

	// �u���b�N�̃T�C�Y
	Vector2 blockSize_;

	// �u���b�N�̔z�u
	Vector2 blockNum_;

	// �u���b�N�̊Ԋu
	Vector2 blockValSize_;

	// �{�b�N�X�̍��W
	Vector2 selectorPos_;

	// �I�����̃{�b�N�X�̍��W
	Vector2 selectorSelPos_;

	// �{�b�N�X�̃T�C�Y
	Vector2 selectorSize_;

	// �u���b�N�̑傫��
	double blockMult_;

	// �ŏ��̃u���b�N���o��܂ł̎���
	float startTime_;

	// �������鎞��
	float moveTime_;

	// ��������
	float limitTime_;

	// �f���^�^�C��
	float deltaTime_;

	// �u���b�N�摜
	std::array<int, 10> blockPic_;

	// �����N�摜
	std::array<int, 5> rankPic_;

	// �t�B�j�b�V�����̃����N�摜
	std::array<int, 5> finishPic_;

	// �w�i�摜
	int backImage_;

	// �X�R�A
	int score_;

	// Z�L�[�J�E���^�[
	int zkeyCount_;

	// �t�H���g�n���h��
	int fontHandle_;

	// �t�H���g�摜
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	// �g�g��
	int blueFrameBlock_;
	int blueFrameRank_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// ���[�v���ŏ��������̂ݍs���p�̃J�E���g�ϐ�
	int loopCount_;
};

