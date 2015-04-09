#include "PonHai.h"


PonHai::PonHai(HaiType hai, RelativePlace receivedPlace) : FuuroHai()
{
	m_receivedPlace = receivedPlace;
	m_fuuroHai.push_back(hai);
	m_fuuroHai.push_back(hai);
	m_fuuroHai.push_back(hai);
}

PonHai::~PonHai() throw()
{
}
