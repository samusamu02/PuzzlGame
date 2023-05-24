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
    // ����������
    bool Init(void) override;

    // �X�V����
    uniqueScene Updata(double delta, uniqueScene ownScene) override;

    // �`�揈��
    void DrawOwnScreen(double delta) override; 

    Scene GetSceneID(void) override { return Scene::Game; };    
};


