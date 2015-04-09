#ifndef _MAHJONG_FUURO_HAI_HEADER_2015_0212_
#define _MAHJONG_FUURO_HAI_HEADER_2015_0212_
#pragma once
#include "Hai.h"
#include "RelativePlace.h"
#include <vector>

class FuuroHai
{
public:
	FuuroHai();
	virtual ~FuuroHai() throw();
	virtual std::vector<HaiType> GetHais() const;// ˆê‚Â–Ú‚ªŽó‚¯Žæ‚Á‚½”v
	virtual RelativePlace GetReceivedPlace() const;
protected:
	std::vector<HaiType> m_fuuroHai;
	RelativePlace m_receivedPlace;
};

#endif //_MAHJONG_FUURO_HAI_HEADER_2015_0212_
