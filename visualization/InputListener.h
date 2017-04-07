#pragma once
#include"stdafx.h"
#include"InputCodes.h"
#include"Render.h"

struct MouseEvent
{
	MouseEvent(int nx, int ny) : x(nx), y(ny) {}

	int x;
	int y;
};

class InputListener
{
public:
	InputListener(Render* render); // Конструктор класса InputLister

	bool MouseMove(const MouseEvent &arg); // Обработка движения мыши

	bool PreasedUp(); // Обработка нажатия вверх
	bool PreasedDown(); // Обработка нажатия вниз
	bool PreasedLeft(); // Обработка нажатия влево
	bool PreasedRight(); // Обработка нажатия вправо

private:
	const float M_STEP = 1.0f; // на сколько сдвинется камера
	Render* m_render; // указатель на экземпляр класса Render
};