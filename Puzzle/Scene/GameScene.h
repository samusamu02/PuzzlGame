#pragma once
#include "BaseScene.h"
#include"../common/Dec.h"
#include "../Obj/Block.h"
class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
private:
    // 初期化処理
    bool Init(void) override;

    // 更新処理
    uniqueScene Updata(double delta, uniqueScene ownScene) override;

    // 描画処理
    void DrawOwnScreen(double delta) override; 

    Scene GetSceneID(void) override { return Scene::Game; };    
};


