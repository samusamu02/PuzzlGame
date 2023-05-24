#pragma once
#include<memory>
#include"../common/Vector2.h"
#include "../Obj/Block.h"
#include "Scene.h"
class BaseScene;

// シーン情報を取得するため
using uniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	// 初期化処理
	virtual bool Init(void) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta">デルタタイム</param>
	/// <param name="ownScene">自分自身のシーンの情報</param>
	/// <returns></returns>
	virtual uniqueScene Updata(double delta, uniqueScene ownScene) = 0;

	// スクリーンの描画
	virtual void Draw(double delta);

	// 描画処理
	virtual void DrawOwnScreen(double delta) = 0;

	// 現在のシーンの取得
	virtual Scene GetSceneID(void) = 0;		
private:
protected:
	// データの格納
	int screenID_;		

	// 描画先のサイズ
	Vector2 screenSize_;	

	// キーの情報取得
	Key key_;			

	// ブロッククラス
	std::shared_ptr<Block> block_;
};

