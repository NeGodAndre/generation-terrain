#include "InputMgr.h"

void InputMgr::Init(HWND window)
{
	m_curx = m_cury = 0;

	m_keyboard.reset(new DirectX::Keyboard);
	m_mouse.reset(new DirectX::Mouse);
	m_mouse->SetWindow(window);

	Log::Get()->Debug("InputMgr init");
}

void InputMgr::Close()
{
	if (!m_Listener.empty())
		m_Listener.clear();
	Log::Get()->Debug("InputMgr close");
}

void InputMgr::SetWinRect(const RECT &winrect)
{
	m_windowrect.left = winrect.left;
	m_windowrect.right = winrect.right;
	m_windowrect.top = winrect.top;
	m_windowrect.bottom = winrect.bottom;
}

void InputMgr::AddListener(InputListener *Listener)
{
	m_Listener.push_back(Listener);
}

void InputMgr::Run(const UINT &msg, WPARAM wParam, LPARAM lParam)
{
	if (m_Listener.empty())
		return;

	eKeyCodes KeyIndex;
	wchar_t buffer[1];
	BYTE lpKeyState[256];


	DirectX::Keyboard::ProcessMessage(msg, wParam, lParam);
	auto kb = m_keyboard->GetState();

	if (kb.W)
	{
		for (auto it = m_Listener.begin(); it != m_Listener.end(); ++it)
		{
			if (!(*it))
				continue;
			if ((*it)->PreasedUp() == true)
				return;
		}
	}
	if (kb.A)
	{
		for (auto it = m_Listener.begin(); it != m_Listener.end(); ++it)
		{
			if (!(*it))
				continue;
			if ((*it)->PreasedLeft() == true)
				return;
		}
	}
	if (kb.S)
	{
		for (auto it = m_Listener.begin(); it != m_Listener.end(); ++it)
		{
			if (!(*it))
				continue;
			if ((*it)->PreasedDown() == true)
				return;
		}
	}
	if (kb.D)
	{
		for (auto it = m_Listener.begin(); it != m_Listener.end(); ++it)
		{
			if (!(*it))
				continue;
			if ((*it)->PreasedRight() == true)
				return;
		}
	}

	m_eventcursor();
}

void InputMgr::m_eventcursor()
{
	auto mouse = m_mouse->GetState();

	if (m_curx == mouse.x && m_cury == mouse.y)
		return;

	m_curx = mouse.x;
	m_cury = mouse.y;

	for (auto it = m_Listener.begin(); it != m_Listener.end(); ++it)
	{
		if (!(*it))
			continue;
		else if ((*it)->MouseMove(MouseEvent(mouse.x - (m_windowrect.right - m_windowrect.left) / 2, mouse.y - (m_windowrect.bottom - m_windowrect.top) / 2)) == true)
			return;
	}
}