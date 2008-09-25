#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>

#include "data.h"

void Data::undo() {
	if (!shapelist.empty())
		shapelist.pop_back();
}

bool Data::toFile(const wxString& filename) {
	wxXmlDocument doc;

	wxXmlNode *root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("shapes"));
	doc.SetRoot(root);

	for (std::list<Shape>::const_reverse_iterator i = shapelist.rbegin(); i != shapelist.rend(); ++i) {
		wxXmlNode *test = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("shape"));
		test->AddProperty(wxT("type"), i->type);
		test->AddProperty(wxT("top"), wxString::Format(wxT("%d"), i->top));
		test->AddProperty(wxT("left"), wxString::Format(wxT("%d"), i->left));
		test->AddProperty(wxT("width"), wxString::Format(wxT("%d"), i->width));
		test->AddProperty(wxT("height"), wxString::Format(wxT("%d"), i->height));
		test->AddProperty(wxT("color"), i->color.GetAsString(wxC2S_HTML_SYNTAX));
		if (i->type == wxT("text")) {
			wxXmlNode *text = new wxXmlNode(test, wxXML_TEXT_NODE, wxEmptyString, i->text);
			test->AddChild(text);
		}
		root->SetNext(test);
	}

	modified = !doc.Save(filename);
	return !modified;
}

bool Data::fromFile(const wxString &filename) {
	wxXmlDocument doc;

	if (!doc.Load(filename))
		return false;

	wxXmlNode *node = doc.GetRoot()->GetChildren();
	while (node) {
		if (node->GetName() == wxT("shape")) {
			Shape s;
			s.type = node->GetPropVal(wxT("type"), wxT("line"));
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
}

bool Data::fromLegacyFile(const wxString &filename, const Data::legacyFormat format) {
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

		s.color = wxColor(r, g, b);

		switch (type) {
			case 1:
				s.type = wxT("line");
				s.color = *wxBLACK;
				break;
			case 2:
				s.type = wxT("triangle");
				break;
			case 3:
				s.type = wxT("rectangle");
				break;
			case 4:
				s.type = wxT("hexagon");
				break;
			case 5:
				s.type = wxT("octagon");
				break;
			case 6:
				s.type = wxT("circle");
				break;
			case 7:
				s.type = wxT("guy");
				break;
		}

		shapelist.push_back(s);
	}
	modified = false;
	return true;
}
