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
	Window(); // конструктор класса Window.

	static Window* Get(){ return m_wndthis; }

	bool Create(const DescWindow &desc); // Создание окна.

	void RunEvent(); // Обработка окна.

	void Close(); // Закрытие окна, очистка памяти.

	void SetInputMgr(InputMgr *inputmgr); // Установление указателя на экземпляр класса InputMgr.

	HWND GetHWND() const { return m_hwnd; } // Возвращает дескриптор окна.
	int Window::GetLeft() const { return m_desc.posx; } // Возвращает на сколько удалено окно от левой стороны экрана.
	int Window::GetTop() const { return m_desc.posy; } // Возвращает на сколько удалено окно от верхней стороны экрана.
	int Window::GetWidth() const { return m_desc.width; } // Возвращает ширину окна.
	int Window::GetHeight() const { return m_desc.height; } // Возвращает высоту окна.

	const std::wstring& GetCaption() const { return m_desc.caption; } // Возвращает заголовок окна.

	bool IsExit() const { return m_isexit; } // Окно закрыто?
	bool IsActive() const { return m_active; } // Окно активно?
	bool IsResize()
	{
		bool ret = m_isresize;
		m_isresize = false;
		return ret;
	} // Окно изменило размер?

	LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam); // обработка поступивших от операционной системы действий.

private:
	void m_UpdateWindowState(); // Обновление информации об окне.

	static Window *m_wndthis; // Указатель на данный экземпляр окна.

	DescWindow m_desc; // Экземпляр структуры содержащий информацию об окне(заголовок, размеры и т.д.)
	InputMgr *m_inputmgr; // Указатель на экземпляр класса InputMgr.
	HWND m_hwnd;	 // Дескриптор окна.
	bool m_isexit;	 // True если происходит событие выхода, в противном случай false.
	bool m_active;   // True если окно активно, false в противном случай.
	bool m_minimized; // True если окно свернуто, false в противном случай.
	bool m_maximized; // True если окно развернуто, false в противном случай.
	bool m_isresize;  // True если окно изменило размер, false в противном случай.
};

static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);