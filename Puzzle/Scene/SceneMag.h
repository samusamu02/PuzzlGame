#pragma once

#include "../Scene/BaseScene.h"

// マネージャークラスの呼び出し
#define lpSceneMng SceneMag::GetInstance()		

class SceneMag
{
public:
	// s_Instanceにアクセスするための関数
	static SceneMag& GetInstance(void)
	{
		static SceneMag s_Instance;
		return s_Instance;
	}
	void Run(void);
	void Update(void);
	void Draw(void);
private:
	// 初期化関数
	bool SysInit(void);		

	// 初期化フラグ
	bool initFlag_;			

	SceneMag();
	~SceneMag();

	// Scneをunique_ptrで管理を宣言
	uniqueScene scene_;

};

