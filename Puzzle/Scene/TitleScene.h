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
    // ����������
    bool Init(void) override;

    // �X�V����
    uniqueScene Updata(double delta, uniqueScene ownScene) override;

    // �`�揈��
    void DrawOwnScreen(double delta) override;

    Scene GetSceneID(void) override { return Scene::Title; };

    // �^�C�g�����S�̍��W
    Vector2 titlePicPos_;

    // �^�C�g�����S�̃T�C�Y
    Vector2 titlePicSize_;

    // �L�[���͉摜�̍��W
    Vector2 playKeyPicPos_;

    // �L�[���͉摜�̃T�C�Y
    Vector2 playKeyPicSize_;

    // �^�C�g�����S�̊g��{��
    double titleExrate;

    // �^�C�g���̔w�i
    int titleBackPic_;

    // �^�C�g�����S
    int titlePic_;

    // �L�[���͑҂��̉摜
    int playKeyPic_;
 

    // �_�ł��邽�߂̃J�E���^�[�ϐ�
    int count = 0;

};

