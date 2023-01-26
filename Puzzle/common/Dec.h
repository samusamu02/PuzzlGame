#pragma once
#include<DxLib.h>
#include"../Blcok/Block.h"


class Key
{
public:
	// キー情報（どれくらい押されているか）
	char input[256];
	// キー入力用関数
	int GetKey(void)
	{
		char allKey[256];
		GetHitKeyStateAll(allKey);
		for (int i = 0; i < 256; i = i + 1)
		{
			if (allKey[i] == 1)
			{
				input[i]++;
			}
			else if (allKey[i] == 0)
			{
				input[i] = 0;
			}
		}
		return 0;
	}
private:
};

