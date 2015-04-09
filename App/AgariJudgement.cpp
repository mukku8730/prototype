#include "AgariJudgement.h"

#include <cassert>

#define HAI_TYPE_MAX (34)
static const int PATTERN_KOTSU_FIRST = 0;
static const int PATTERN_SYUNTSU_FIRST = 1;
static const int SUUHAI_COLOR_MAX = 3;
static const int UNDER_SYUNTSU_HAI_MENBER_MAX = 7;
static const int SUUHAI_NUMBER_MAX = 9;

/**
	�R���X�g���N�^
*/
AgariJudgement::AgariJudgement()
{
}

/**
	�f�X�g���N�^
*/
AgariJudgement::~AgariJudgement() throw()
{
}

/**
	�A�K�����m�F���邽�߂̊֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �A�K���ۂ��m�F�������v
	return �A�K�����\�Ȃ�true
*/
bool AgariJudgement::JudgeAgari(std::multiset<HaiType> tehai, HaiType hai)
{
	if (JudgeAgariNormal(tehai, hai))
	{
		return true;
	}
	return false;
}

/**
	�ʏ펞�̃A�K�����m�F���邽�߂̊֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �A�K���ۂ��m�F�������v
	return �A�K�����\�Ȃ�true
*/
bool AgariJudgement::JudgeAgariNormal(std::multiset<HaiType> tehai, HaiType hai)
{
	for (int i = 0; i < HAI_TYPE_MAX; i++)
	{
		for (int pattern = PATTERN_KOTSU_FIRST; pattern <= PATTERN_SYUNTSU_FIRST; pattern++)
		{
			std::multiset<HaiType> myHais = tehai;
			int* haiNormal = new int[HAI_TYPE_MAX];
			CountHaiTypes(&haiNormal, tehai);
			//���������o��
			if (haiNormal[i] >= 2)
			{
				haiNormal[i] -= 2;
				//���q���Ɏ��o��
				if(pattern == PATTERN_KOTSU_FIRST)
				{
					for (int j = 0; j < HAI_TYPE_MAX; j++)
					{
						if (haiNormal[j] >= 3)
						{
							haiNormal[j] -= 3;
						}
					}
					for (int a = 0; a < SUUHAI_COLOR_MAX; a++)
					{
						for (int b = 0; b < UNDER_SYUNTSU_HAI_MENBER_MAX; b++)
						{
							if ((haiNormal[(a * SUUHAI_NUMBER_MAX) + b] >= 1)
								&& (haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 1] >= 1)
								&& (haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 2] >= 1))
							{
								haiNormal[(a * SUUHAI_NUMBER_MAX) + b] -= 1;
								haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 1] -= 1;
								haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 2] -= 1;
							}
						}
					}
				}

				//���q���Ɏ��o��
				else
				{
					if (pattern == PATTERN_KOTSU_FIRST)
					{
						for (int a = 0; a < SUUHAI_COLOR_MAX; a++)
						{
							for (int b = 0; b < UNDER_SYUNTSU_HAI_MENBER_MAX; b++)
							{
								if ((haiNormal[(a * SUUHAI_NUMBER_MAX) + b] >= 1)
									&& (haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 1] >= 1)
									&& (haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 2] >= 1))
								{
									haiNormal[(a * SUUHAI_NUMBER_MAX) + b] -= 1;
									haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 1] -= 1;
									haiNormal[((a * SUUHAI_NUMBER_MAX) + b) + 2] -= 1;
								}
							}
						}
						for (int j = 0; j < HAI_TYPE_MAX; j++)
						{
							if (haiNormal[j] >= 3)
							{
								haiNormal[j] -= 3;
							}
						}
					}
				}
			}

			for (int k = 0; k < HAI_TYPE_MAX; k++)
			{
				if (haiNormal[k] != 0)
				{
					break;
				}
				if (k == (HAI_TYPE_MAX - 1))
				{
					delete haiNormal;
					return true;
				}
			}
			delete haiNormal;
		}

	}

	return false;
}
