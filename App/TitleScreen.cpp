#include "TitleScreen.h"
#include "../Key.h"
#include "../KeyInput.h"
#include "../BillboardString.h"
#include "MahjongScreen.h"
#include <tchar.h>
#include <iostream>
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }


TitleScreen::TitleScreen() :
Screen(),
m_pushKeyState(0),
m_pTitle(new BillboardString()),
m_pTitle2(new BillboardString()),
m_pKeyState(new BillboardString()),
m_keyStateColor(255),
colorFug(true)
{
	assert(m_pTitle);
	assert(m_pTitle2);
	assert(m_pKeyState);
	m_pTitle->SetPosition(80, 80);
	m_pTitle->SetScale(2.5f,2.5f);

	m_pTitle2->SetPosition(300,180);
	m_pTitle2->SetScale(2.0f,2.0f);

	m_pKeyState->SetPosition(210, 320);
	m_pKeyState->SetScale(0.8f, 0.8f);
}

TitleScreen::~TitleScreen()  throw()
{
	SAFE_DELETE(m_pTitle);

	SAFE_DELETE(m_pTitle2);

	SAFE_DELETE(m_pKeyState);
}

void TitleScreen::Update()
{ 
	KeyInput* input = KeyInput::GetInstance();
	input->Update();

	if (input->GetKeys()[DIK_SPACE]->IsPushed()) {
		m_isNext = true;
	}

	m_pTitle->RegistString(_T("extreme"));
	m_pTitle->SetColor(0x00FF0000);		//Ô

	m_pTitle2->RegistString(_T("‚Ü`"));
	m_pTitle2->SetColor(0x00FF33CC);	//ƒsƒ“ƒN

	m_pKeyState->RegistString(_T("Push Key SPACE"));
	m_pKeyState->SetColor(0x00FFFF00);

	if (colorFug){
		m_keyStateColor-=5;
	}
	else if (!colorFug){
		m_keyStateColor+=5;
	}

	m_pKeyState->SetAlpha(m_keyStateColor);
	
	if ((m_keyStateColor < 20) && colorFug){
		colorFug = false;
	}
	if ((m_keyStateColor > 230)&& !colorFug){
		colorFug = true;
	}



//	m_frame++;											//ŽžŠÔ‚Å•\Ž¦
//	if ((m_frame % MAX_FRAME) == (MAX_FRAME - 1)){
//		m_isNext = true;
//	}
}

void TitleScreen::Draw()
{
	m_pTitle->Draw();
	m_pTitle2->Draw();
	m_pKeyState->Draw();
}

Screen* TitleScreen::ChangeScreen()
{
	Screen* pScreen = new MahjongScreen();
	assert((pScreen != NULL) && "Impossible!");
	return pScreen;
}
