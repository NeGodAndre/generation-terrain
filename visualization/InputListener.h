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
	InputListener(Render* render); // ����������� ������ InputLister

	bool MouseMove(const MouseEvent &arg); // ��������� �������� ����

	bool PreasedUp(); // ��������� ������� �����
	bool PreasedDown(); // ��������� ������� ����
	bool PreasedLeft(); // ��������� ������� �����
	bool PreasedRight(); // ��������� ������� ������

private:
	const float M_STEP = 1.0f; // �� ������� ��������� ������
	Render* m_render; // ��������� �� ��������� ������ Render
};