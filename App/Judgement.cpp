#include "Judgement.h"
#define HAI_TYPE_MAX (34)

#include <cassert>
Judgement::Judgement()
{
}

Judgement::~Judgement() throw()
{
}

void Judgement::CountHaiTypes(int** haiTypes, std::multiset<HaiType> hais)
{
	if (*haiTypes == NULL)
	{
		assert(false);
	}
	for (std::multiset<HaiType>::const_iterator it = hais.begin(); it != hais.end(); it++)
	{
		for (int i = 0; i < HAI_TYPE_MAX; i++)
		{
			if ((*it) == Hai::GetHaiType(i + 1))
			{
				*haiTypes[i] += 1;
			}
			break;
		}
	}
}
