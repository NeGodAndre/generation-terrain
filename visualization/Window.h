#pragma once

class InputMgr;

struct DescWindow
{
	DescWindow() :
		caption(L""),
		width(800),
		height(600),
		posx(300),
		posy(200),
		resizing(true)
	{}

	int posx;
	int posy;
	std::wstring caption;	
	int width;				
	int height;			
	bool resizing;
};

class Window
{
public:
	Window(); // ����������� ������ Window.

	static Window* Get(){ return m_wndthis; }

	bool Create(const DescWindow &desc); // �������� ����.

	void RunEvent(); // ��������� ����.

	void Close(); // �������� ����, ������� ������.

	void SetInputMgr(InputMgr *inputmgr); // ������������ ��������� �� ��������� ������ InputMgr.

	HWND GetHWND() const { return m_hwnd; } // ���������� ���������� ����.
	int Window::GetLeft() const { return m_desc.posx; } // ���������� �� ������� ������� ���� �� ����� ������� ������.
	int Window::GetTop() const { return m_desc.posy; } // ���������� �� ������� ������� ���� �� ������� ������� ������.
	int Window::GetWidth() const { return m_desc.width; } // ���������� ������ ����.
	int Window::GetHeight() const { return m_desc.height; } // ���������� ������ ����.

	const std::wstring& GetCaption() const { return m_desc.caption; } // ���������� ��������� ����.

	bool IsExit() const { return m_isexit; } // ���� �������?
	bool IsActive() const { return m_active; } // ���� �������?
	bool IsResize()
	{
		bool ret = m_isresize;
		m_isresize = false;
		return ret;
	} // ���� �������� ������?

	LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam); // ��������� ����������� �� ������������ ������� ��������.

private:
	void m_UpdateWindowState(); // ���������� ���������� �� ����.

	static Window *m_wndthis; // ��������� �� ������ ��������� ����.

	DescWindow m_desc; // ��������� ��������� ���������� ���������� �� ����(���������, ������� � �.�.)
	InputMgr *m_inputmgr; // ��������� �� ��������� ������ InputMgr.
	HWND m_hwnd;	 // ���������� ����.
	bool m_isexit;	 // True ���� ���������� ������� ������, � ��������� ������ false.
	bool m_active;   // True ���� ���� �������, false � ��������� ������.
	bool m_minimized; // True ���� ���� ��������, false � ��������� ������.
	bool m_maximized; // True ���� ���� ����������, false � ��������� ������.
	bool m_isresize;  // True ���� ���� �������� ������, false � ��������� ������.
};

static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);