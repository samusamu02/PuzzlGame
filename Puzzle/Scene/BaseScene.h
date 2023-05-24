#pragma once
#include<memory>
#include"../common/Vector2.h"
#include "../Obj/Block.h"
#include "Scene.h"
class BaseScene;

// �V�[�������擾���邽��
using uniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	// ����������
	virtual bool Init(void) = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta">�f���^�^�C��</param>
	/// <param name="ownScene">�������g�̃V�[���̏��</param>
	/// <returns></returns>
	virtual uniqueScene Updata(double delta, uniqueScene ownScene) = 0;

	// �X�N���[���̕`��
	virtual void Draw(double delta);

	// �`�揈��
	virtual void DrawOwnScreen(double delta) = 0;

	// ���݂̃V�[���̎擾
	virtual Scene GetSceneID(void) = 0;		
private:
protected:
	// �f�[�^�̊i�[
	int screenID_;		

	// �`���̃T�C�Y
	Vector2 screenSize_;	

	// �L�[�̏��擾
	Key key_;			

	// �u���b�N�N���X
	std::shared_ptr<Block> block_;
};

