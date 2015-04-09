#include "ChiiHai.h"


ChiiHai::ChiiHai(HaiType receivedHai, HaiType hai_1, HaiType hai_2) : FuuroHai()
{
	m_receivedPlace = RelativePlace_Left;
	m_fuuroHai.push_back(receivedHai);
	m_fuuroHai.push_back(hai_1);
	m_fuuroHai.push_back(hai_2);
}

ChiiHai::~ChiiHai() throw()
{
}
