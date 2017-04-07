#include "stdafx.h"
#include "Framework.h"
#include "InputListener.h"

int main()
{
	Framework framework;

	Render *render = new Render();
	InputListener *input = new InputListener(render);
	framework.SetRender(render);
	framework.Init();
	framework.AddInputListener(input);

	framework.Run();

	framework.Close();

    return 0;
}

