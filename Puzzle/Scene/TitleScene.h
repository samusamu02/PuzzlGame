#pragma once
#include "BaseScene.h"
#include"../common/Dec.h"
class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
private:
    // 初期化処理
    bool Init(void) override;

    // 更新処理
    uniqueScene Updata(double delta, uniqueScene ownScene) override;

    // 描画処理
    void DrawOwnScreen(double delta) override;

    Scene GetSceneID(void) override { return Scene::Title; };

    // タイトルロゴの座標
    Vector2 titlePicPos_;

    // タイトルロゴのサイズ
    Vector2 titlePicSize_;

    // キー入力画像の座標
    Vector2 playKeyPicPos_;

    // キー入力画像のサイズ
    Vector2 playKeyPicSize_;

    // タイトルロゴの拡大倍率
    double titleExrate;

    // タイトルの背景
    int titleBackPic_;

    // タイトルロゴ
    int titlePic_;

    // キー入力待ちの画像
    int playKeyPic_;
 

    // 点滅するためのカウンター変数
    int count = 0;

};

