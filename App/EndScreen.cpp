#include "EndScreen.h"
#include "../Key.h"
#include "../KeyInput.h"
#include "TitleScreen.h"
#include <iostream>
#include <cassert>

static const int MAX_FRAME = 20;			//数値の数だけ表示　/****テスト***/


EndScreen::EndScreen() : Screen()
{
}

EndScreen::~EndScreen()  throw()
{
}

void EndScreen::Update()
{
	KeyInput* input = KeyInput::GetInstance();
	input->Update();

	if (input->GetKeys()[DIK_RETURN]->IsPushed()) {
		m_isNext = true;
	}
//	m_frame++;
//	if ((m_frame % MAX_FRAME) == (MAX_FRAME - 1)){
//		m_isNext = true;
//	}
}

void EndScreen::Draw()
{
//	std::cout << "EndScreen" << std::endl;
}

Screen* EndScreen::ChangeScreen()
{
	Screen* pScreen = new TitleScreen();
	assert((pScreen != NULL) && "Impossible!");
	return pScreen;
}
