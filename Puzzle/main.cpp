#include <memory>
#include <DxLib.h>
#include <chrono>
#include "Scene/SceneMag.h"
#include "Scene/TitleScene.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// シーンの管理クラスのインスタンス。
	lpSceneMng.Run();
	return 0;
}