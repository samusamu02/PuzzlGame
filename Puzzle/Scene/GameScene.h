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
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::Game; };    // �����̓Q�[���V�[��
};


