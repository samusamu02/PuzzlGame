#pragma once
#include<DxLib.h>
#include"../Blcok/Block.h"


class Key
{
public:
	// �L�[���i�ǂꂭ�炢������Ă��邩�j
	char input[256];
	// �L�[���͗p�֐�
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

