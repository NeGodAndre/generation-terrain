#include "stdafx.h"
#include "Framework.h"
#include "macros.h"
#include "Log.h"

Framework::Framework() :
	m_wnd(nullptr),
	m_render(nullptr),
	m_input(nullptr),
	m_init(false)
{
}

Framework::~Framework()
{
}

void Framework::AddInputListener(InputListener *listener)
{
	if (m_input)
		m_input->AddListener(listener);
}

void Framework::Run()
{
	if (m_init)
	{
		while (m_frame());
	}
}

bool Framework::Init()
{
	m_wnd = new Window();
	m_input = new InputMgr();

	if (!m_wnd || !m_input)
	{
		Log::Get()->Err("Не удалось выделить память");
		return false;
	}
		
	DescWindow desc;
	if (!m_wnd->Create(desc))
	{
		Log::Get()->Err("Не удалось создать окно");
		return false;
	}
	//m_input->Init(m_wnd->GetHWND());
	m_wnd->SetInputMgr(m_input);

	if (!m_render->Init(m_wnd->GetHWND()))
	{
		Log::Get()->Err("Не удалось создать рендер");
		return false;
	}

	m_init = true;
	return true;
}

bool Framework::m_frame()
{
	m_wnd->RunEvent();

	if (!m_wnd->IsActive())
		return true;

	if (m_wnd->IsExit())
		return false;

	if (m_wnd->IsResize())
	{
	}

	m_render->UpdateScene();
	m_render->DrawScene();

	return true;
}

void Framework::Close()
{
	m_init = false;
	_CLOSE(m_render);
	_CLOSE(m_wnd);
	_CLOSE(m_input);
}