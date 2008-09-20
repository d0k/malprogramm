#ifndef _WINDOW_H
#define _WINDOW_H

#include <wx/wx.h>

#include "canvas.h"

class Window : public wxFrame {
private:
	void createToolbar();
	bool askToSave();
	Canvas *canvas;
public:
	Window();
	void OnShapeSet(wxCommandEvent&);
	void OnColorSet(wxCommandEvent&);

	void OnUndo(wxCommandEvent&);
	void OnPrint(wxCommandEvent&);
	void OnNew(wxCommandEvent&);
	void OnOpen(wxCommandEvent&);
	void OnSave(wxCommandEvent&);
	void OnQuit(wxCommandEvent&);
	void OnClose(wxCloseEvent&);

	DECLARE_EVENT_TABLE()
};

#endif
