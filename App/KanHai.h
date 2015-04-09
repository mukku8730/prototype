#ifndef _MAHJONG_KAN_HAI_HEADER_2015_0212_
#define _MAHJONG_KAN_HAI_HEADER_2015_0212_

#include "FuuroHai.h"
class KanHai :
	public FuuroHai
{
public:
	KanHai(HaiType hai, RelativePlace receivedPlace);
	virtual ~KanHai() throw();
};

#endif //_MAHJONG_KAN_HAI_HEADER_2015_0212_
