#ifndef _CANVAS_H
#define _CANVAS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/print.h>

#include "data.h"

class Canvas : public wxPanel, public Data, public wxPrintout {
private:
	bool moving;
	Data::shapeType shape;
	wxColour color;
public:
	Canvas(wxFrame *parent) : wxPanel(parent), moving(false) { SetBackgroundStyle(wxBG_STYLE_CUSTOM); }
	void Draw(wxDC& dc);

	void setShape(const Data::shapeType shape) { this->shape = shape; }
	Data::shapeType getShape() const { return this->shape; }
	void setColor(const wxColour& color) { this->color = color; }
	const wxColour& getColor() const { return this->color; }

	void paint(wxPaintEvent& evt);
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	bool OnPrintPage(int pageNum);

	DECLARE_EVENT_TABLE()
};

#endif
