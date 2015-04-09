#include "FuuroHai.h"


FuuroHai::FuuroHai()
	: m_fuuroHai()
	, m_receivedPlace()
{
}

FuuroHai::~FuuroHai() throw()
{
}

std::vector<HaiType> FuuroHai::GetHais() const
{
	return m_fuuroHai;
}

RelativePlace FuuroHai::GetReceivedPlace() const{
	return m_receivedPlace;
}
