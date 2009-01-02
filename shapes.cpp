#include "shapes.h"

wxXmlNode* Shape::toXML(wxXmlNode *root) const {
	wxXmlNode* ret = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("shape"));
	ret->AddProperty(wxT("type"), typeAsString());
	ret->AddProperty(wxT("top"), wxString::Format(wxT("%d"), top));
	ret->AddProperty(wxT("left"), wxString::Format(wxT("%d"), left));
	ret->AddProperty(wxT("width"), wxString::Format(wxT("%d"), width));
	ret->AddProperty(wxT("height"), wxString::Format(wxT("%d"), height));
	ret->AddProperty(wxT("color"), color.GetAsString(wxC2S_HTML_SYNTAX));
	return ret;
}

void Line::draw(wxDC& dc) const {
	dc.SetPen(wxPen(color));
	dc.DrawLine(left, top, width+left, height+top);
}

void Triangle::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	wxPoint points[] = {
		wxPoint(left + width/2, top),
		wxPoint(left + width, top + height),
		wxPoint(left, top + height)
	};
	dc.DrawPolygon(3, points);
}

void Rectangle::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	dc.DrawRectangle(left, top, width, height);
}

void Hexagon::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	wxPoint points[] = {
		wxPoint(left, top + height/4),
		wxPoint(left + width/2, top),
		wxPoint(left + width, top + height/4),
		wxPoint(left + width, top + height/4*3),
		wxPoint(left + width/2, top + height),
		wxPoint(left, top + height/4*3)
	};
	dc.DrawPolygon(6, points);
}

void Octagon::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	wxPoint points[] = {
		wxPoint(left, top + height/3*2),
		wxPoint(left, top + height/3),
		wxPoint(left + width/3, top),
		wxPoint(left + width/3*2, top),
		wxPoint(left + width, top + height/3),
		wxPoint(left + width, top + height/3*2),
		wxPoint(left + width/3*2, top + height),
		wxPoint(left + width/3, top + height)
	};
	dc.DrawPolygon(8, points);
}

void Circle::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	dc.DrawEllipse(left, top, width, height);
}

void Guy::draw(wxDC& dc) const {
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(wxBrush(color));
	const int midx = left + width/2;
	const int midy = top + height/2;
	const int legs = height/4; // offset of arms & legs
	const int head = width/4;
	dc.DrawLine(midx, midy-legs, midx, midy+legs); // body
	dc.DrawLine(midx, midy-legs, left, midy); // left arm
	dc.DrawLine(midx, midy-legs, width+left, midy); // right arm
	dc.DrawLine(midx, midy+legs, left, top+height); // left leg
	dc.DrawLine(midx, midy+legs, left+width, top+height); // right leg
	dc.DrawEllipse(midx-head/2, top, head, legs); // head
}

void Text::draw(wxDC& dc) const {
	dc.SetTextForeground(color);
	dc.DrawText(text, left, top);
}

wxXmlNode* Text::toXML(wxXmlNode *root) const {
	wxXmlNode *n = Shape::toXML(root);
	wxXmlNode *text = new wxXmlNode(n, wxXML_TEXT_NODE, wxEmptyString, this->text);
	n->AddChild(text);
	return n;
}
