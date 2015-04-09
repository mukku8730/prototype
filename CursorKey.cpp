#include "CursorKey.h"
#include "Key.h"
#include "KeyInput.h"
#define STANDBY_TIME (30)

CursorKey::CursorKey() :
m_cursor(),
m_frame(0),
m_isPushed(false)
{
	m_cursor.set(CursorType_None);
}


CursorKey::~CursorKey()
{
}


void CursorKey::Update() {
	if (m_isPushed) {
		m_frame++;
		if (m_frame > STANDBY_TIME) {
			m_frame = 0;
			m_isPushed = false;
		}
	}
	else {
		KeyInput* input = KeyInput::GetInstance();
		input->Update();

		if (input->GetKeys()[DIK_RIGHT]->IsPushed()) {
			m_isPushed = true;
			m_cursor.set(CursorType_Right);
		}
		else if (input->GetKeys()[DIK_LEFT]->IsPushed()) {
			m_isPushed = true;
			m_cursor.set(CursorType_Left);
		}
		else if (input->GetKeys()[DIK_UP]->IsPushed()) {
			m_isPushed = true;
			m_cursor.set(CursorType_Up);
		}
		else if (input->GetKeys()[DIK_DOWN]->IsPushed()) {
			m_isPushed = true;
			m_cursor.set(CursorType_Down);
		}
		else if (input->GetKeys()[DIK_RETURN]->IsPushed()) {
			m_isPushed = true;
			m_cursor.set(CursorType_Enter);
		}

	}

}


CursorType CursorKey::GetCursor() {
	if (m_cursor[CursorType_None]) return CursorType_None;
	if (m_cursor[CursorType_Left]) return CursorType_Left;
	if (m_cursor[CursorType_Right]) return CursorType_Right;
	if (m_cursor[CursorType_Up]) return CursorType_Up;
	if (m_cursor[CursorType_Down]) return CursorType_Down;
	if (m_cursor[CursorType_Enter]) return CursorType_Enter;
}
