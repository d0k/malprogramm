#ifndef _CANVAS_H
#define _CANVAS_H

#include <wx/wx.h>
#include <wx/print.h>

#include "data.h"

class Canvas : public wxPanel, public Data, public wxPrintout {
private:
	bool moving;
	wxString shape;
	wxColour color;
public:
	Canvas(wxFrame *parent) : wxPanel(parent), moving(false) { SetBackgroundStyle(wxBG_STYLE_CUSTOM); }
	void Draw(wxDC& dc);

	void setShape(const wxString& shape) { this->shape = shape; }
	void setColor(const wxColour& color) { this->color = color; }

	void paint(wxPaintEvent& evt);
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	bool OnPrintPage(int pageNum);

	DECLARE_EVENT_TABLE()
};

#endif
