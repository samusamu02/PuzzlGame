#pragma once
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "../common/Dec.h"

constexpr int blockNumX = 6;	// ブロックの数（横方向)
constexpr int blockNumY = 6;	// ブロックの数（縦方向）

// 現在のブロックの状態
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
	void LoadBackPic(void);

	// フォントのロード
	void LoadFontPic(void);

	// ブロックの移動処理
	void ControlBlock(void);

	// ブロックの更新処理
	void UpdateBlock(void);

	// ブロックの削除処理
	void DeleBlock(void);

	// ブロックの落下処理
	void DownBlock(void);

	void DrawBG(void);

	// ブロックの描画処理
	void DrawBlock(void);

	void DrawSelector(void);

	void DrawFont(void);

	void DrawRank(void);

	void DrawFinishRank(void);

	// キー入力
	Key key_;

	// 現在のブロック
	NowBlock nowBlock_;

	// ブロックのサイズ
	Vector2 blockSize_;

	// ブロックの配置
	Vector2 blockNum_;

	// ブロックの間隔
	Vector2 blockValSize_;

	// ボックスの座標
	Vector2 selectorPos_;

	// 選択時のボックスの座標
	Vector2 selectorSelPos_;

	// ボックスのサイズ
	Vector2 selectorSize_;

	// ブロックの大きさ
	double blockMult_;

	// 最初のブロックが出るまでの時間
	float startTime_;

	// 動かせる時間
	float moveTime_;

	// 制限時間
	float limitTime_;

	// デルタタイム
	float deltaTime_;

	// ブロック画像
	std::array<int, 10> blockPic_;

	// ランク画像
	std::array<int, 5> rankPic_;

	// フィニッシュ時のランク画像
	std::array<int, 5> finishPic_;

	// 背景画像
	int backImage_;

	// スコア
	int score_;

	// Zキーカウンター
	int zkeyCount_;

	// フォントハンドル
	int fontHandle_;

	// フォント画像
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	// 枠組み
	int blueFrameBlock_;
	int blueFrameRank_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// ループ内で処理を一回のみ行う用のカウント変数
	int loopCount_;
};

