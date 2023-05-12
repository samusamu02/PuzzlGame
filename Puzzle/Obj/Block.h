#pragma once
#include <array>
#include "../common/Vector2.h"
#include "../common/Dec.h"

constexpr int blockNumX = 6;	// ブロックの数（横方向)
constexpr int blockNumY = 6;	// ブロックの数（縦方向）

// 現在のブロックの状態
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

	//　更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// get関数
	int GetScore();				// スコアの取得
	float GetLimitTime(void);	// 制限時間の取得

private:
	// 初期化処理
	void Init(void);

	// ブロックの画像のロード
	void LoadBlockPic(void);

	// ランクの画像のロード
	void LoadRankPic(void);

	// 終了時のランクの画像のロード
	void LoadFinishRankPic(void);

	// 枠組みの画像のロード
	void LoadFramePic(void);

	// ブロックの移動処理
	void ControlBlock(void);

	// ブロックの更新処理
	void UpdateBlock(void);

	// ブロックの削除処理
	void DeleBlock(void);

	// ブロックの落下処理
	void DownBlock(void);

	// キー入力
	Key key_;

	// 現在のブロック
	NowBlock nowBlock_;	

	// ブロックの座標
	Vector2 blockPos_;

	// ブロックのサイズ
	Vector2 blockSize_ = { 96,96 };

	// ボックスの座標
	Vector2 boxPos_;

	// 選択時のボックスの座標
	Vector2 boxSelPos_;							

	// スコアのフォント画像の座標
	Vector2 scorePicPos_;

	// タイムのフォント画像の座標
	Vector2 timePicPos_;

	// フォント画像のサイズ
	Vector2 stringPicSize_ = { 10,320 };

	// ブロックの配置
	Vector2 blockNum_ = { 6,6 };

	// ブロックの間隔
	Vector2 blockValSize_ = { 80,200 };

	// ボックスのサイズ
	Vector2 boxSize_ = { 35,155 };

	// 背景の画像のサイズ
	Vector2 backPicSize_ = { 1024,768 };

	// ブロックの大きさ
	double blockMult_ = 0.0;

	// フォント画像の倍率を大きさ
	double stringExRate_ = 1.0;

	// タイマー系
	float setTime_ = 5.0f;
	float startTime = 4.0f;
	float limitTime = 60.0f;
	float deltaTime = 0.018f;

	// ブロック画像
	std::array<int, 10> blockPic_;

	// ランク画像
	std::array<int, 5> rankPic_;

	// フィニッシュ時のランク画像
	std::array<int, 5> finishPic_;

	// 背景画像
	int backImage_;

	// スコア
	unsigned int score_ = 0;				

	// Zキーカウンター
	unsigned int zkeyCount_ = 0;

	// フォントハンドル
	int fontHandle_a_;
	int fontHandle_b_;
	int blockMoveCountFontHandle_;

	// フォント画像
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	// 枠組み
	int blueFrame_;
	int blueFrameBlock_;
	int blueFrameScore_;
	int blueFrameTime_;
	int blueFrameMove_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// ループ内で処理を一回のみ行う用のカウント変数
	int loopcount_ = 0;

	// 点滅カウント
	int stringCount_ = 0;
};

