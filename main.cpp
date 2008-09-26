#include "main.h"
#include "window.h"

IMPLEMENT_APP(Application)

bool Application::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);
	Window *window = new Window();
	if (argc > 1)
		window->openFile(argv[1]);

	return true;
}
