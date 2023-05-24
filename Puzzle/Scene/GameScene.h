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
    // ‰Šú‰»ˆ—
    bool Init(void) override;

    // XVˆ—
    uniqueScene Updata(double delta, uniqueScene ownScene) override;

    // •`‰æˆ—
    void DrawOwnScreen(double delta) override; 

    Scene GetSceneID(void) override { return Scene::Game; };    
};


