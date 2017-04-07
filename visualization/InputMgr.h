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
	void Init(HWND window); // Инициализация класса
	void Close(); // Очистка памяти при завершении выполнения класса

	void Run(const UINT &msg, WPARAM wParam, LPARAM lParam); // Обработка событий клавиатуры и мыши

	void AddListener(InputListener *Listener); // Добавление экземпляра класса InputListener

	void SetWinRect(const RECT &winrect); // Изменение значение переменой m_windowrect при изменении размера окна.

private:
	void m_eventcursor(); // Обработка движение мыши.

	std::list<InputListener*> m_Listener; // Стек объектов типа InputLister.

	RECT m_windowrect; // Размеры окна
	int m_curx; // x-ая кордината курсора
	int m_cury; // y-ая кордината курсора

	std::unique_ptr<DirectX::Keyboard> m_keyboard; // Клавиатура
	std::unique_ptr<DirectX::Mouse> m_mouse; // Мышь
};