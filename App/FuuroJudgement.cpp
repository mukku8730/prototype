#include "FuuroJudgement.h"

#include "PonHai.h"
#include <cassert>
#include <typeinfo>

#define HAI_TYPE_MAX (34)
static const int OVER_CHII_HAI_NUMBER_MIN = 3;
static const int UNDER_CHII_HAI_NUMBER_MAX = 7;
static const int CHII_HAI_OVER_SUB_UNDER = 2;

/**
	�R���X�g���N�^
*/
FuuroJudgement::FuuroJudgement()
{

}

/**
	�f�X�g���N�^
*/
FuuroJudgement::~FuuroJudgement() throw()
{

}

/**
	�`�[�̔�����s���֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �t�[���ۂ��m�F�������v
	return �t�[�����\�Ȃ�true
*/
bool FuuroJudgement::JudgeChii(std::multiset<HaiType> tehai, HaiType hai)
{
	if ((hai != HaiType_none) && (hai <= HaiType_sou_9))
	{
		int* haiTypes = new int[HAI_TYPE_MAX];
		CountHaiTypes(&haiTypes, tehai);
		HaiType chiiHaiMin = HaiType_none;
		HaiType chiiHaiMax = HaiType_none;
		if (Hai::GetHaiNum(hai) < OVER_CHII_HAI_NUMBER_MIN)
		{
			chiiHaiMin = Hai::GetHaiType(Hai::GetHaiNumber(hai) - (OVER_CHII_HAI_NUMBER_MIN - (Hai::GetHaiNum(hai))));
		}
		else
		{
			chiiHaiMin = Hai::GetHaiType(Hai::GetHaiNumber(hai) - CHII_HAI_OVER_SUB_UNDER);
		}

		if (Hai::GetHaiNum(hai) > UNDER_CHII_HAI_NUMBER_MAX)
		{
			chiiHaiMax = Hai::GetHaiType(Hai::GetHaiNumber(hai) + ((Hai::GetHaiNum(hai) - UNDER_CHII_HAI_NUMBER_MAX)));
		}
		else
		{
			chiiHaiMax = Hai::GetHaiType(Hai::GetHaiNumber(hai) + CHII_HAI_OVER_SUB_UNDER);
		}

		bool canChii = false;
		for (int i = chiiHaiMin; i < (chiiHaiMax - 1); i++)
		{
			if ((haiTypes[i] >= 1) && (haiTypes[i + 1] >= 1) && (haiTypes[(i + 2)] >= 1))
			{
				delete haiTypes;
				return true;
			}
		}
		delete haiTypes;
		return canChii;
	}
	return false;
}

/**
	�|���̔�����s���֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �t�[���ۂ��m�F�������v
	return �t�[�����\�Ȃ�true
*/
bool FuuroJudgement::JudgePon(std::multiset<HaiType> tehai, HaiType hai)
{
	if ((hai != HaiType_none) && (hai != HaiType_MAX))
	{
		int* haiTypes = new int[HAI_TYPE_MAX];
		CountHaiTypes(&haiTypes, tehai);
		if (haiTypes[(hai - 1)] >= 2)
		{
			return true;
		}
	}
	return false;
}

/**
	�A���J���̔�����s���֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �t�[���ۂ��m�F�������v
	return �t�[�����\�Ȃ�true
*/
bool FuuroJudgement::JudgeAnkan(std::multiset<HaiType> tehai, HaiType hai)
{
	int* haiTypes = new int[HAI_TYPE_MAX];
	if ((hai != HaiType_none) && (hai != HaiType_MAX))
	{
		CountHaiTypes(&haiTypes, tehai);
		if (haiTypes[(hai - 1)] >= 4)
		{
			delete haiTypes;
			return true;
		}
	}
	delete haiTypes;
	return false;
}

/**
	�~���J���̔�����s���֐�
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �t�[���ۂ��m�F�������v
	return �t�[�����\�Ȃ�true
*/
bool FuuroJudgement::JudgeMinkan(std::multiset<HaiType> tehai, HaiType hai)
{
	int* haiTypes = new int[HAI_TYPE_MAX];
	if ((hai != HaiType_none) && (hai != HaiType_MAX))
	{
		CountHaiTypes(&haiTypes, tehai);
		if (haiTypes[(hai - 1)] >= 3)
		{
			delete haiTypes;
			return true;
		}
	}
	delete haiTypes;
	return false;
}

/**
	�J�J���̔�����s���֐�
	@param fuuroHais vector�Ɋi�[���ꂽ�t�[���v�N���X
	@param tehai vector�Ɋi�[���ꂽHaiType�B��v
	@param hai �t�[���ۂ��m�F�������v
	return �t�[�����\�Ȃ�true

*/
bool FuuroJudgement::JudgeKakan(std::vector<std::shared_ptr<FuuroHai>> fuuroHais, std::multiset<HaiType> tehai, HaiType hai)
{
	int* haiTypes = new int[HAI_TYPE_MAX];
	if ((hai != HaiType_none) && (hai != HaiType_MAX))
	{
		CountHaiTypes(&haiTypes, tehai);
		if (haiTypes[(hai - 1)] >= 1)
		{
			for (std::vector<std::shared_ptr<FuuroHai>>::const_iterator fuuroIt = fuuroHais.begin(); fuuroIt != fuuroHais.end(); fuuroIt++)
			{
				if (typeid(*fuuroIt) == typeid(PonHai))
				{
					std::vector<HaiType> hais = (*fuuroIt)->GetHais();
					if (hais.back() == hai)
					{
						delete haiTypes;
						return true;
					}
				}
			}
		}
	}
	delete haiTypes;
	return false;
}
