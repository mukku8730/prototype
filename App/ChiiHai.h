#ifndef _MAHJONG_CHII_HAI_HEADER_2015_0212_
#define _MAHJONG_CHII_HAI_HEADER_2015_0212_

#include "FuuroHai.h"
class ChiiHai :
	public FuuroHai
{
public:
	ChiiHai(HaiType receivedHai, HaiType hai_1, HaiType hai_2);
	virtual ~ChiiHai() throw();
};

#endif //_MAHJONG_CHII_HAI_HEADER_2015_0212_
