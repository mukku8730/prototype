#ifndef _MAHJONG_PON_HAI_HEADER_2015_0212_
#define _MAHJONG_PON_HAI_HEADER_2015_0212_

#pragma once
#include "FuuroHai.h"
class PonHai :
	public FuuroHai
{
public:
	PonHai(HaiType hai, RelativePlace receivedPlace);
	virtual ~PonHai() throw();
};

#endif //_MAHJONG_PON_HAI_HEADER_2015_0212_
