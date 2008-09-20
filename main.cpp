#include "main.h"
#include "window.h"

IMPLEMENT_APP(Application)

bool Application::OnInit()
{
	new Window();

	return true;
}
