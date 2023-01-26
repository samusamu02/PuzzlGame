#pragma once
#include<memory>
#include"../common/Vector2.h"
#include "../Blcok/Block.h"
#include "Scene.h"
class BaseScene;

// using�ŒZ��
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
	virtual Scene GetSceneID(void) = 0;		// ���ǂ̃V�[���Ȃ̂�
private:
protected:
	int screenID_;		// �f�[�^�̊i�[

	int nowScore = 0;

	Vector2 screenSize_;		// �`���̃T�C�Y
	Key key_;					// �L�[�̏��擾

	std::shared_ptr<Block> block_;
};

