#include <wx/dcbuffer.h>

#include "canvas.h"

BEGIN_EVENT_TABLE(Canvas, wxPanel)
EVT_PAINT(Canvas::paint)

EVT_MOTION(Canvas::mouseMoved)
EVT_LEFT_DOWN(Canvas::mouseDown)
EVT_LEFT_UP(Canvas::mouseReleased)
END_EVENT_TABLE()

void Canvas::mouseDown(wxMouseEvent& evt) {
	Shape s = { shape, evt.GetPosition().x, evt.GetPosition().y, 0, 0, color };
	if (shape == Data::SHAPE_TEXT) {
		wxTextEntryDialog d(this, _("Text"));
		if (d.ShowModal() == wxID_OK) {
			s.text = d.GetValue();
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
	if (moving) {
		Shape& s = *(shapelist.rbegin());
		s.width = evt.GetPosition().x - s.left;
		s.height = evt.GetPosition().y - s.top;
		Refresh();
	}
}

void Canvas::paint(wxPaintEvent& WXUNUSED(evt)) {
	wxAutoBufferedPaintDC dc(this);
	Draw(dc);
}

void Canvas::Draw(wxDC& dc)
{
	// clear screen
	dc.Clear();

	for (std::list<Data::Shape>::const_iterator i = shapelist.begin(); i != shapelist.end(); ++i) {
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(wxBrush(i->color));
		if (i->type == Data::SHAPE_LINE) {
			dc.SetPen(wxPen(i->color));
			dc.DrawLine(i->left, i->top, i->width+i->left, i->height+i->top);
		} else if (i->type == Data::SHAPE_RECTANGLE) {
			dc.DrawRectangle(i->left, i->top, i->width, i->height);
		} else if (i->type == Data::SHAPE_TRIANGLE) {
			wxPoint points[] = {
				wxPoint(i->left + i->width/2, i->top),
				wxPoint(i->left + i->width, i->top + i->height),
				wxPoint(i->left, i->top + i->height)
			};
			dc.DrawPolygon(3, points);
		} else if (i->type == Data::SHAPE_HEXAGON) {
			wxPoint points[] = {
				wxPoint(i->left, i->top + i->height/4),
				wxPoint(i->left + i->width/2, i->top),
				wxPoint(i->left + i->width, i->top + i->height/4),
				wxPoint(i->left + i->width, i->top + i->height/4*3),
				wxPoint(i->left + i->width/2, i->top + i->height),
				wxPoint(i->left, i->top + i->height/4*3)
			};
			dc.DrawPolygon(6, points);
		} else if (i->type == Data::SHAPE_OCTAGON) {
			wxPoint points[] = {
				wxPoint(i->left, i->top + i->height/3*2),
				wxPoint(i->left, i->top + i->height/3),
				wxPoint(i->left + i->width/3, i->top),
				wxPoint(i->left + i->width/3*2, i->top),
				wxPoint(i->left + i->width, i->top + i->height/3),
				wxPoint(i->left + i->width, i->top + i->height/3*2),
				wxPoint(i->left + i->width/3*2, i->top + i->height),
				wxPoint(i->left + i->width/3, i->top + i->height)
			};
			dc.DrawPolygon(8, points);
		} else if (i->type == Data::SHAPE_CIRCLE) {
			dc.DrawEllipse(i->left, i->top, i->width, i->height);
		} else if (i->type == Data::SHAPE_GUY) {
			const int midx = i->left + i->width/2;
			const int midy = i->top + i->height/2;
			const int legs = i->height/4; // offset of arms & legs
			const int head = i->width/4;
			dc.DrawLine(midx, midy-legs, midx, midy+legs); // body
			dc.DrawLine(midx, midy-legs, i->left, midy); // left arm
			dc.DrawLine(midx, midy-legs, i->width+i->left, midy); // right arm
			dc.DrawLine(midx, midy+legs, i->left, i->top+i->height); // left leg
			dc.DrawLine(midx, midy+legs, i->left+i->width, i->top+i->height); // right leg
			dc.DrawEllipse(midx-head/2, i->top, head, legs); // head
		} else if (i->type == Data::SHAPE_TEXT) {
			dc.SetTextForeground(i->color);
			dc.DrawText(i->text, i->left, i->top);
		}
	}
}

bool Canvas::OnPrintPage(int WXUNUSED(pageNum)) {
	FitThisSizeToPage(GetClientSize());
	Draw(*GetDC());
	return true;
}
