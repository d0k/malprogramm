#include "main.h"
#include "window.h"

IMPLEMENT_APP(Application)

bool Application::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);
	new Window();

	return true;
}
