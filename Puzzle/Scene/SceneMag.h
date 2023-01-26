#pragma once

#include "../Scene/BaseScene.h"

#define lpSceneMng SceneMag::GetInstance()		// �}�l�[�W���[�N���X�̌Ăяo��

class SceneMag
{
public:
	// s_Instance�ɃA�N�Z�X���邽�߂̊֐�
	static SceneMag& GetInstance(void)
	{
		static SceneMag s_Instance;
		return s_Instance;
	}

	//static void Create(void)
	//{
	//	if (s_Instance == nullptr)
	//	{
	//		s_Instance = new SceneMag();
	//	}
	//}
	//static void Destroy(void)
	//{
	//	delete s_Instance;
	//	s_Instance = nullptr;
	//}
	void Run(void);
	void Update(void);
	void Draw(void);
private:
	//static SceneMag* s_Instance;
	bool SysInit(void);		// �������֐�
	bool initFlag_;			// �������t���O


	SceneMag();
	~SceneMag();

	// Scne��unique_ptr�ŊǗ���錾
	uniqueScene scene_;

};

