#pragma once
#include<memory>
#include"../common/Vector2.h"
#include "../Obj/Block.h"
#include "Scene.h"
class BaseScene;

// usingで短く
using uniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual bool Init(void) = 0;
	virtual uniqueScene Updata(double delta, uniqueScene ownScene) = 0;
	virtual void Draw(double delta);
	virtual void DrawOwnScreen(double delta) = 0;

	// 現在のシーンの取得
	virtual Scene GetSceneID(void) = 0;		
private:
protected:
	// データの格納
	int screenID_;		

	int nowScore = 0;

	Vector2 screenSize_;		// 描画先のサイズ
	Key key_;					// キーの情報取得

	std::shared_ptr<Block> block_;
};

