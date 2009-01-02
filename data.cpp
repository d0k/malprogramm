#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>

#include "data.h"
#include "shapefactory.h"

void Data::undo() {
	if (!shapelist.empty()) {
		Shape *s = *(shapelist.rbegin());
		shapelist.pop_back();
		delete s;
	}
}

void Data::clear() {
	while (!shapelist.empty())
		undo();
}

bool Data::toFile(const wxString& filename) {
	wxXmlDocument doc;

	wxXmlNode *root = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("shapes"));
	doc.SetRoot(root);

	for (std::list<Shape*>::reverse_iterator i = shapelist.rbegin(); i != shapelist.rend(); ++i)
		root->SetNext((*i)->toXML(root));

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
			if (node->GetName() == wxT("shape"))
				shapelist.push_back(ShapeFactory::createShapeFromXML(node));
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

		Shape *s = ShapeFactory::createShape(static_cast<ShapeFactory::shapeType>(type-1),
											 x1,
											 y1,
											 x2-x1,
											 y2-y1,
											 type == 1 ? *wxBLACK : wxColor(r, g, b));

		shapelist.push_back(s);
	}
	modified = false;
	return true;
}
