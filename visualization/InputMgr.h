#pragma once
#include "stdafx.h"
#include "InputMgr.h"
#include "InputCodes.h"
#include "InputListener.h"
#include "Log.h"

class InputListener;

class InputMgr
{
public:
	void Init(HWND window); // ������������� ������
	void Close(); // ������� ������ ��� ���������� ���������� ������

	void Run(const UINT &msg, WPARAM wParam, LPARAM lParam); // ��������� ������� ���������� � ����

	void AddListener(InputListener *Listener); // ���������� ���������� ������ InputListener

	void SetWinRect(const RECT &winrect); // ��������� �������� ��������� m_windowrect ��� ��������� ������� ����.

private:
	void m_eventcursor(); // ��������� �������� ����.

	std::list<InputListener*> m_Listener; // ���� �������� ���� InputLister.

	RECT m_windowrect; // ������� ����
	int m_curx; // x-�� ��������� �������
	int m_cury; // y-�� ��������� �������

	std::unique_ptr<DirectX::Keyboard> m_keyboard; // ����������
	std::unique_ptr<DirectX::Mouse> m_mouse; // ����
};