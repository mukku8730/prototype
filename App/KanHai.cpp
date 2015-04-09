#include "KanHai.h"


KanHai::KanHai(HaiType hai, RelativePlace receivedPlace) : FuuroHai()
{
	m_receivedPlace = receivedPlace;
	m_fuuroHai.push_back(hai);
	m_fuuroHai.push_back(hai);
	m_fuuroHai.push_back(hai);
	m_fuuroHai.push_back(hai);

}


KanHai::~KanHai() throw()
{
}
