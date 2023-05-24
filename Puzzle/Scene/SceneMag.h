#pragma once

#include "../Scene/BaseScene.h"

// �}�l�[�W���[�N���X�̌Ăяo��
#define lpSceneMng SceneMag::GetInstance()		

class SceneMag
{
public:
	// s_Instance�ɃA�N�Z�X���邽�߂̊֐�
	static SceneMag& GetInstance(void)
	{
		static SceneMag s_Instance;
		return s_Instance;
	}
	void Run(void);
	void Update(void);
	void Draw(void);
private:
	// �������֐�
	bool SysInit(void);		

	// �������t���O
	bool initFlag_;			

	SceneMag();
	~SceneMag();

	// Scne��unique_ptr�ŊǗ���錾
	uniqueScene scene_;

};

