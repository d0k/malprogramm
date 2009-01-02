#ifndef _WINDOW_H
#define _WINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "canvas.h"

class Window : public wxFrame {
private:
	void createToolbar();
	bool askToSave();
	Canvas *canvas;
public:
	Window();
	void openFile(const wxString& filename, const Data::fileFormat format = Data::FORMAT_XML);

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
