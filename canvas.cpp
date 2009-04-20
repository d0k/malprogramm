#include <wx/dcbuffer.h>

#include "canvas.h"

BEGIN_EVENT_TABLE(Canvas, wxPanel)
EVT_PAINT(Canvas::paint)

EVT_MOTION(Canvas::mouseMoved)
EVT_LEFT_DOWN(Canvas::mouseDown)
EVT_LEFT_UP(Canvas::mouseReleased)
END_EVENT_TABLE()

void Canvas::mouseDown(wxMouseEvent& evt) {
	Shape *s = ShapeFactory::createShape(shape, evt.GetPosition().x, evt.GetPosition().y, 0, 0, color);
	if (shape == ShapeFactory::SHAPE_TEXT) {
		wxTextEntryDialog d(this, _("Text"));
		if (d.ShowModal() == wxID_OK) {
			Text* t = static_cast<Text*>(s);
			t->setText(d.GetValue());
			shapelist.push_back(s);
			Refresh();
		}
	} else {
		shapelist.push_back(s);
		moving = true;
	}
	modified = true;
}

void Canvas::mouseReleased(wxMouseEvent& WXUNUSED(evt)) {
	moving = false;
}

void Canvas::mouseMoved(wxMouseEvent& evt) {
	if (moving && evt.ButtonIsDown(wxMOUSE_BTN_LEFT) && !shapelist.empty()) {
		Shape* s = *(shapelist.rbegin());
		s->setEndPos(evt.GetPosition().x, evt.GetPosition().y);
		Refresh();
	}
}

void Canvas::paint(wxPaintEvent& WXUNUSED(evt)) {
	wxAutoBufferedPaintDC dc(this);
	Draw(dc);
}

void Canvas::Draw(wxDC& dc)
{
	dc.SetBackground(*wxWHITE);
	// clear screen
	dc.Clear();

	for (std::list<Shape*>::const_iterator i = shapelist.begin(); i != shapelist.end(); ++i) {
		(*i)->draw(dc);
	}
}

bool Canvas::OnPrintPage(int WXUNUSED(pageNum)) {
	FitThisSizeToPage(GetClientSize());
	Draw(*GetDC());
	return true;
}
