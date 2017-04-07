#include"InputListener.h"

InputListener::InputListener(Render* render)
{
	m_render = render;
}

bool InputListener::MouseMove(const MouseEvent & arg)
{
	m_render->Rotation(arg.x, arg.y, 0.00001f);
	m_render->UpdateCamera();
	return false;
}

bool InputListener::PreasedUp()
{
	m_render->MoveBackForward(M_STEP);
	m_render->UpdateCamera();
	return false;
}

bool InputListener::PreasedDown()
{
	m_render->MoveBackForward(-M_STEP);
	m_render->UpdateCamera();
	return false;
}

bool InputListener::PreasedLeft()
{
	m_render->MoveLeftRight(-M_STEP);
	m_render->UpdateCamera();
	return false;
}

bool InputListener::PreasedRight()
{
	m_render->MoveLeftRight(M_STEP);
	m_render->UpdateCamera();
	return false;
}