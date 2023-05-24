#include <time.h>
#include <DxLib.h>


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
	// ブロックの種類
	nowBlock_.blockType.resize(blockNumX, std::vector<int>(blockNumY));

	// どのブロックが落ちるか
	nowBlock_.blockDrop_.resize(blockNumX, std::vector<int>(blockNumY));

	// どのブロックが消えるか
	nowBlock_.blockDelete_.resize(blockNumX, std::vector<bool>(blockNumY));

	// ブロックのサイズ
	blockSize_ = { 96,96 };

	// ブロックの配置
	blockNum_ = { 6,6 };

	// ブロックの間隔
	blockValSize_ = { 80,200 };

	// ボックスの座標
	selectorPos_ = { 0,0 };

	// 選択時のボックスの座標
	selectorSelPos_ = { 0,0 };

	// ボックスのサイズ
	selectorSize_ = { 35,155 };

	// ブロックの大きさ
	blockMult_ = 0;

	// 最初のブロックが出るまでの時間
	startTime_ = 4.0f;

	// 動かせる時間
	moveTime_ = 5.0f;

	// 制限時間
	limitTime_ = 60.0f;

	// デルタタイム
	deltaTime_ = 0.018f;

	// スコア
	score_ = 0;

	// Zキーカウンター
	zkeyCount_ = 0;

	// ループ内で処理を一回のみ行う用のカウント変数
	loopCount_ = 0;

	// フォントの設定
	fontHandle_ = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 65, NULL, DX_FONTTYPE_ANTIALIASING);

	// ブロックの画像の読み込み
	LoadBlockPic();

	// ランクの画像の読み込み
	LoadRankPic();

	// 終了時のランクの画像の読み込み
	LoadFinishRankPic();

	// 枠組みの画像のロード
	LoadBackPic();

	// フォントのロード
	LoadFontPic();

	// 画像をランダムに表示
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// ブロックをランダムに表示
			nowBlock_.blockType[x][y] = GetRand(9);

			// 値の初期化
			nowBlock_.blockDelete_[x][y] = 0;
			nowBlock_.blockDrop_[x][y] = 0;
		}
	}
}

void Block::LoadBlockPic(void)
{
	// 画像の読み込み
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
	// ランクの画像の読み込み
	rankPic_[0] = LoadGraph("Resource/img/S.png");
	rankPic_[1] = LoadGraph("Resource/img/A.png");
	rankPic_[2] = LoadGraph("Resource/img/B.png");
	rankPic_[3] = LoadGraph("Resource/img/C.png");
	rankPic_[4] = LoadGraph("Resource/img/D.png");
}

void Block::LoadFinishRankPic(void)
{
	// 終了時のランクの画像の読み込み
	finishPic_[0] = LoadGraph("Resource/img/stopPic_S.png");
	finishPic_[1] = LoadGraph("Resource/img/stopPic_A.png");
	finishPic_[2] = LoadGraph("Resource/img/stopPic_B.png");
	finishPic_[3] = LoadGraph("Resource/img/stopPic_C.png");
	finishPic_[4] = LoadGraph("Resource/img/stopPic_D.png");
}

void Block::LoadBackPic(void)
{
	// 背景
	backImage_ = LoadGraph("Resource/img/Summer2.jpg");

	// 枠組みの画像の読み込み
	blueFrameBlock_ = LoadGraph("Resource/img/blueBlockFrame.png");
	blueFrameRank_ = LoadGraph("Resource/img/blueFrameMove.png");
	blueFrameCong_ = LoadGraph("Resource/img/blueConditionFrame.png");
	blueFrameTimeAndUntilscore_ = LoadGraph("Resource/img/blueFrameTimeAndUntilscore.png");
}

void Block::LoadFontPic(void)
{
	// フォント埋め込み
	timePic_ = LoadGraph("Resource/img/Time.png");
	conditionPic_ = LoadGraph("Resource/img/ClearString.png");
	scorePic_ = LoadGraph("Resource/img/ScorePic.png");
}

void Block::Update(void)
{
	// 開始の演出
	if (blockMult_ < 6.0)
	{
		blockMult_ += 0.05;
	}

	// 最初のブロックがでるまでの時間を計測する
	if (startTime_ >= 0)
	{
		startTime_ -= deltaTime_;
	}

	// 最初のブロックがすべて表示されたら制限時間を減らす
	if (startTime_ <= 0)
	{
		if (limitTime_ >= 0)
		{
			// 制限時間を減らす
			limitTime_ -= deltaTime_;
		}
	}

	// 制限時間になったら終了用のSEを再生する
	if (loopCount_ == 0)
	{
		if (limitTime_ <= 0.0)
		{
			loopCount_++;
			lpSooundPross.PlayBackSound(SOUNDNAME_SE::Finish, lpSooundPross.GetVolume(), false);
		}
	}

	// ブロックの移動処理
	ControlBlock();

	// ブロックの更新処理
	UpdateBlock();

	// ブロックの落下処理
	DownBlock();

}

void Block::ControlBlock(void)
{
	// キー情報の取得
	key_.GetKey();	

	// 制限時間の間キー操作を出来るようにする
	if (static_cast<int>(limitTime_) > 0)
	{
		// 移動と範囲指定
		if (blockMult_ > 6)
		{
			// 移動
			if (key_.input[KEY_INPUT_RIGHT] == 1)
			{
				// 1ブロック分進める
				selectorPos_.x_ = selectorPos_.x_ + blockSize_.x_;
				// 範囲
				if (selectorPos_.x_ > (blockSize_.x_ * 5))
				{
					selectorPos_.x_ = blockSize_.x_ * 5;
				}

				// サウンドの再生
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock,lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_LEFT] == 1)
			{
				selectorPos_.x_ = selectorPos_.x_ - blockSize_.x_;
				if (selectorPos_.x_ < 0)
				{
					selectorPos_.x_ = 0;
				}

				// サウンドの再生
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_UP] == 1)
			{
				selectorPos_.y_ = selectorPos_.y_ - blockSize_.y_;
				if (selectorPos_.y_ < 0)
				{
					selectorPos_.y_ = 0;
				}

				// サウンドの再生
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}
			if (key_.input[KEY_INPUT_DOWN] == 1)
			{
				selectorPos_.y_ = selectorPos_.y_ + blockSize_.y_;
				if (selectorPos_.y_ > (blockSize_.y_ * 5))
				{
					selectorPos_.y_ = (blockSize_.y_ * 5);
				}

				// サウンドの再生
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::ControlBlock, lpSooundPross.GetVolume(), false);
			}

			if (key_.input[KEY_INPUT_Z] == 1)
			{
				selectorSelPos_ = selectorPos_;
				zkeyCount_++;

				// サウドの再生
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::Select, lpSooundPross.GetVolume(), false);
			}
		}
	}
}

void Block::UpdateBlock(void)
{
	if (zkeyCount_ == 1)
	{
		// 一時変数で入れ替え処理
		int change_block;
		change_block = nowBlock_.blockType[selectorPos_.x_ / blockSize_.x_][selectorPos_.y_ / blockSize_.y_];
		nowBlock_.blockType[selectorPos_.x_ / blockSize_.x_][selectorPos_.y_ / blockSize_.y_] = nowBlock_.blockType[selectorSelPos_.x_ / blockSize_.x_][selectorSelPos_.y_ / blockSize_.y_];
		nowBlock_.blockType[selectorSelPos_.x_ / blockSize_.x_][selectorSelPos_.y_ / blockSize_.y_] = change_block;

		selectorSelPos_.x_ = selectorPos_.x_;
		selectorSelPos_.y_ = selectorPos_.y_;
	}
	else if (zkeyCount_ == 2 || moveTime_ < 0)
	{
		// ブロックを削除
		DeleBlock();

		zkeyCount_ = 0;

		for (int y = 0; y < blockNum_.y_; y++)
		{
			for (int x = 0; x < blockNum_.x_; x++)
			{
				// ブロックが消えたら
				if (nowBlock_.blockType[x][y] == -1)
				{
					// 再配置
					nowBlock_.blockType[x][y] = GetRand(5);
					nowBlock_.blockDelete_[x][y] = 0;
					nowBlock_.blockDrop_[x][y] = 0;
				}
			}
		}
	}
}

void Block::DeleBlock(void)
{
	// X方向のブロック一致チェック
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_ - 2; x++)
		{
			// 3ブロック以上が一致しているかを確認する
			if (nowBlock_.blockType[x + 0][y] == nowBlock_.blockType[x + 1][y] &&
				nowBlock_.blockType[x + 1][y] == nowBlock_.blockType[x + 2][y] &&
				nowBlock_.blockType[x + 2][y] == nowBlock_.blockType[x + 0][y] &&
				nowBlock_.blockType[x + 0][y] != -1 &&
				nowBlock_.blockType[x + 1][y] != -1 &&
				nowBlock_.blockType[x + 2][y] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					// もし一致したらブロックを消す
					nowBlock_.blockDelete_[x + i][y] = 1;	
				}
			}
		}
	}

	// Y方向のブロック一致チェック
	for (int y = 0; y < blockNum_.y_ - 2; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// 3ブロックが以上が一致しているかを確認する
			if (nowBlock_.blockType[x][y + 0] == nowBlock_.blockType[x][y + 1] &&
				nowBlock_.blockType[x][y + 1] == nowBlock_.blockType[x][y + 2] &&
				nowBlock_.blockType[x][y + 2] == nowBlock_.blockType[x][y + 0] &&
				nowBlock_.blockType[x][y + 0] != -1 &&
				nowBlock_.blockType[x][y + 1] != -1 &&
				nowBlock_.blockType[x][y + 2] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					nowBlock_.blockDelete_[x][y + i] = 1;	
				}
			}
		}
	}

	// 処理をしたので実際に消える処理
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			// ブロックが消えたら
			if (nowBlock_.blockDelete_[x][y] == 1)
			{
				// 再生する
				lpSooundPross.PlayBackSound(SOUNDNAME_SE::Delete, lpSooundPross.GetVolume(), false);

				// 値を戻す
				nowBlock_.blockDelete_[x][y] = 0;	
				nowBlock_.blockType[x][y] = -1;

				// スコアを加算する
				score_ = score_ + 100;
			}
		}
	}

}

void Block::DownBlock(void)
{
	// ブロックが消えたらブロックを落とす
	// ブロックが何かしらある場合
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
						nowBlock_.blockDrop_[x][y] = nowBlock_.blockDrop_[x][y] + 1;
					}
				}
			}

			// 落ちる処理を実際に動かす
			for (int y = 6 - 1; y > -1; y = y - 1)
			{
				for (int x = 0; x < 6; x = x + 1)
				{
					if (nowBlock_.blockDrop_[x][y] != 0)
					{
						nowBlock_.blockType[x][y + nowBlock_.blockDrop_[x][y]] = nowBlock_.blockType[x][y];
						nowBlock_.blockType[x][y] = -1;
						nowBlock_.blockDrop_[x][y + nowBlock_.blockDrop_[x][y]] = 0;
						nowBlock_.blockDrop_[x][y] = 0;
					}
				}
			}
		}
	}
}

void Block::Draw(void)
{
	// 背景の描画
	DrawBG();

	// ブロックの描画
	DrawBlock();

	// セレクターの描画
	DrawSelector();

	// フォントの描画
	DrawFont();

	// ランクの描画
	DrawRank();

	// 終了時のランクの描画
	DrawFinishRank();
}

void Block::DrawBG(void)
{
	// ブロックの背景
	DrawGraph(0, 0, backImage_, true);

	// 枠組みの描画
	DrawGraph(30, -35, blueFrameBlock_, true);
	DrawGraph(0, -30, blueFrameTimeAndUntilscore_, true);
	DrawGraph(0, -30, blueFrameRank_, true);
	DrawGraph(0, -32, blueFrameCong_, true);
}

void Block::DrawBlock(void)
{
	// ブロックの描画
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			if (nowBlock_.blockType[x][y] != -1)
			{
				DrawRotaGraph(
					x * blockSize_.x_ + blockValSize_.x_ + 30,
					y * blockSize_.y_ + blockValSize_.y_,
					blockMult_,
					0,
					blockPic_[nowBlock_.blockType[x][y]],
					true
				);
			}
		}
	}
}

void Block::DrawSelector(void)
{
	// セレクターの処理
	for (int y = 0; y < blockNum_.y_; y++)
	{
		for (int x = 0; x < blockNum_.x_; x++)
		{
			if (blockMult_ >= 6)
			{
				if ((static_cast<int>(limitTime_) >= 0))
				{
					if (x == selectorPos_.x_ / blockSize_.x_ &&
						y == selectorPos_.y_ / blockSize_.y_)
					{
						// Zキーの状態によりボックスの色を買える
						switch (zkeyCount_)
						{
						case 0:
							moveTime_ = 5;
							DrawBox(selectorPos_.x_ + selectorSize_.x_ + 30, selectorPos_.y_ + selectorSize_.y_, selectorPos_.x_ + blockSize_.x_ + selectorSize_.x_ + 30, selectorPos_.y_ + blockSize_.y_ + selectorSize_.y_, 0x00ffff, false);
							break;
						case 1:
							DrawBox(selectorSelPos_.x_ + selectorSize_.x_ + 30, selectorSelPos_.y_ + selectorSize_.y_, selectorSelPos_.x_ + blockSize_.x_ + selectorSize_.x_ + 30, selectorSelPos_.y_ + blockSize_.y_ + selectorSize_.y_, 0xff00ff, false);

							// ブロックを扱える時間を計測
							if (moveTime_ >= 0)
							{
								moveTime_ -= deltaTime_;
							}
							else if (moveTime_ <= 0)
							{
								zkeyCount_ = 0;
							}
							DrawFormatString(selectorSelPos_.x_ + selectorSize_.x_ + 30, selectorSelPos_.y_ + selectorSize_.y_, 0x0000ff, "%d", static_cast<int>(moveTime_));

							break;
						}
					}
				}
			}
		}
	}
}

void Block::DrawFont(void)
{
	// フォント（画像）の描画
	DrawGraph(0, -30, timePic_, true);
	DrawGraph(0, 0, conditionPic_, true);
	DrawGraph(0, 0, scorePic_, true);

	// フォントの描画
	DrawFormatStringToHandle(800, 350, 0xffa500, fontHandle_, "%d", static_cast<int>(limitTime_));
	DrawFormatStringToHandle(800, 230, 0xffa500, fontHandle_, "%u", score_);
}

void Block::DrawRank(void)
{
	// スコアに応じてランクを変更
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
}

void Block::DrawFinishRank(void)
{
	// 終了時のランク
	if (static_cast<int>(limitTime_) <= 0)
	{
		for (int y = 0; y < blockNum_.y_; y++)
		{
			for (int x = 0; x < blockNum_.x_; x++)
			{
				// ブロックにフィルターを掛ける
				GraphFilter(blockPic_[nowBlock_.blockType[x][y]], DX_GRAPH_FILTER_MONO, -1, 0, 0, 0);

				// ランクをつける
				if (score_ < 3000)
				{
					// ランクD
					DrawGraph(0, 0, finishPic_[4], true);
				}
				else if (score_ >= 3000 && score_ < 6000)
				{
					// ランクC
					DrawGraph(0, 0, finishPic_[3], true);
				}
				else if (score_ >= 6000 && score_ < 10000)
				{
					// ランクB
					DrawGraph(0, 0, finishPic_[2], true);
				}
				else if (score_ >= 10000 && score_ < 20000)
				{
					// ランクA
					DrawGraph(0, 0, finishPic_[1], true);
				}
				else if (score_ >= 20000)
				{
					// ランクS
					DrawGraph(0, 0, finishPic_[0], true);
				}
			}
		}
	}
}

int Block::GetScore()
{
   	return score_;
}

float Block::GetLimitTime(void)
{
	return limitTime_;
}

