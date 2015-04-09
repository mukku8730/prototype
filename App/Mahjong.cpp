#include "Mahjong.h"
#include "TitleScreen.h"
#include <iostream>
#include <cassert>

Mahjong::Mahjong()
	: m_screenPtr(new TitleScreen())
{
	assert(m_screenPtr);
}

Mahjong::~Mahjong() throw()
{
}

void Mahjong::Update()
{
	m_screenPtr->Update();
	if (m_screenPtr->GetIsNext())
	{
		m_screenPtr.reset(m_screenPtr->ChangeScreen());
	}
}

void Mahjong::Draw()
{
	m_screenPtr->Draw();
}
