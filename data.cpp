#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>

#include "data.h"

void Data::undo() {
	if (!shapelist.empty())
		shapelist.pop_back();
}

const wxString Data::shapeTypeToText(const Data::shapeType type) {
	switch (type) {
		case SHAPE_LINE:
			return wxT("line");
		case SHAPE_TRIANGLE:
			return wxT("triangle");
		case SHAPE_RECTANGLE:
			return wxT("rectangle");
		case SHAPE_HEXAGON:
			return wxT("hexagon");
		case SHAPE_OCTAGON:
			return wxT("octagon");
		case SHAPE_CIRCLE:
			return wxT("circle");
		case SHAPE_GUY:
			return wxT("guy");
		case SHAPE_TEXT:
			return wxT("text");
	}
	wxASSERT(false);
	return wxEmptyString;
}

Data::shapeType Data::textToShapeType(const wxString& type) {
	if (type == wxT("line"))
		return SHAPE_LINE;
	if (type == wxT("triangle"))
		return SHAPE_TRIANGLE;
	if (type == wxT("rectangle"))
		return SHAPE_RECTANGLE;
	if (type == wxT("hexagon"))
		return SHAPE_HEXAGON;
	if (type == wxT("octagon"))
		return SHAPE_OCTAGON;
	if (type == wxT("circle"))
		return SHAPE_CIRCLE;
	if (type == wxT("guy"))
		return SHAPE_GUY;
	if (type == wxT("text"))
		return SHAPE_TEXT;

	wxASSERT(false);
	return SHAPE_UNKNOWN;
}

bool Data::toFile(const wxString& filename) {
	wxXmlDocument doc;

	wxXmlNode *root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("shapes"));
	doc.SetRoot(root);

	for (std::list<Shape>::reverse_iterator i = shapelist.rbegin(); i != shapelist.rend(); ++i) {
		wxXmlNode *test = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("shape"));
		test->AddProperty(wxT("type"), shapeTypeToText(i->type));
		test->AddProperty(wxT("top"), wxString::Format(wxT("%d"), i->top));
		test->AddProperty(wxT("left"), wxString::Format(wxT("%d"), i->left));
		test->AddProperty(wxT("width"), wxString::Format(wxT("%d"), i->width));
		test->AddProperty(wxT("height"), wxString::Format(wxT("%d"), i->height));
		test->AddProperty(wxT("color"), i->color.GetAsString(wxC2S_HTML_SYNTAX));
		if (i->type == SHAPE_TEXT) {
			wxXmlNode *text = new wxXmlNode(test, wxXML_TEXT_NODE, wxEmptyString, i->text);
			test->AddChild(text);
		}
		root->SetNext(test);
	}

	modified = !doc.Save(filename);
	return !modified;
}

bool Data::fromFile(const wxString &filename, const Data::fileFormat format) {
	if (format == FORMAT_XML) {
		wxXmlDocument doc;

		if (!doc.Load(filename))
			return false;

		wxXmlNode *node = doc.GetRoot()->GetChildren();
		while (node) {
			if (node->GetName() == wxT("shape")) {
				Shape s;
				s.type = textToShapeType(node->GetPropVal(wxT("type"), wxT("line")));
				(node->GetPropVal(wxT("top"), wxT("0"))).ToLong(&s.top);
				(node->GetPropVal(wxT("left"), wxT("0"))).ToLong(&s.left);
				(node->GetPropVal(wxT("width"), wxT("0"))).ToLong(&s.width);
				(node->GetPropVal(wxT("height"), wxT("0"))).ToLong(&s.height);
				s.color = wxColour(node->GetPropVal(wxT("color"), wxT("#000000")));
				s.text = node->GetNodeContent();
				shapelist.push_back(s);
			}
			node = node->GetNext();
		}
		modified = false;
		return true;
	} else {
		return fromLegacyFile(filename, format);
	}

}

bool Data::fromLegacyFile(const wxString &filename, const Data::fileFormat format) {
	wxFileInputStream file(filename);

	if (!file.IsOk())
		return false;

	wxDataInputStream doc(file);

	while (!file.Eof()) {
		wxInt32 type, x1, x2, y1, y2;
		wxUint8 r, g, b, a;

		if (format == FORMAT_32)
			type = doc.Read32();
		else
			type = doc.Read16();

		r = doc.Read8();
		g = doc.Read8();
		b = doc.Read8();
		a = doc.Read8();

		if (format == FORMAT_32) {
			x1 = doc.Read32();
			y1 = doc.Read32();
			x2 = doc.Read32();
			y2 = doc.Read32();
		} else {
			x1 = doc.Read16();
			y1 = doc.Read16();
			x2 = doc.Read16();
			y2 = doc.Read16();
		}

		Shape s;
		s.left = x1;
		s.top = y1;
		s.width = x2-x1;
		s.height = y2-y1;

		if (type == 1)
			s.color = *wxBLACK;
		else
			s.color = wxColor(r, g, b);

		s.type = static_cast<shapeType>(type-1);

		shapelist.push_back(s);
	}
	modified = false;
	return true;
}
