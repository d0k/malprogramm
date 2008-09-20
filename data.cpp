#include <wx/xml/xml.h>

#include "data.h"

void Data::undo() {
	if (!shapelist.empty())
		shapelist.pop_back();
}

void Data::toFile(const wxString& filename) {
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
		root->SetNext(test);
	}

	doc.Save(filename);
	modified = false;
}

void Data::fromFile(const wxString &filename) {
	wxXmlDocument doc(filename);

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

			shapelist.push_back(s);
		}
		node = node->GetNext();
	}
	modified = false;
}
