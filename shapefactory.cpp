#include "shapefactory.h"

Shape* ShapeFactory::createShape(ShapeFactory::shapeType type, int left, int top, int width, int height, const wxColour& color) {
	switch (type) {
		case SHAPE_LINE:
			return new Line(left, top, width, height, color);
		case SHAPE_TRIANGLE:
			return new Triangle(left, top, width, height, color);
		case SHAPE_RECTANGLE:
			return new Rectangle(left, top, width, height, color);
		case SHAPE_HEXAGON:
			return new Hexagon(left, top, width, height, color);
		case SHAPE_OCTAGON:
			return new Octagon(left, top, width, height, color);
		case SHAPE_CIRCLE:
			return new Circle(left, top, width, height, color);
		case SHAPE_GUY:
			return new Guy(left, top, width, height, color);
		case SHAPE_TEXT:
			return new Text(left, top, width, height, color);
		case SHAPE_UNKNOWN:
		default:
			wxASSERT(false);
	}
	return NULL;
}

ShapeFactory::shapeType ShapeFactory::textToShapeType(const wxString& type) {
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

static long wxstrtol(const wxString& s) {
	long ret;
	s.ToLong(&ret);
	return ret;
}

Shape* ShapeFactory::createShapeFromXML(wxXmlNode *node) {
	shapeType type = textToShapeType(node->GetPropVal(wxT("type"), wxT("line")));
	Shape *s  = createShape(type,
							wxstrtol(node->GetPropVal(wxT("top"), wxT("0"))),
							wxstrtol(node->GetPropVal(wxT("left"), wxT("0"))),
							wxstrtol(node->GetPropVal(wxT("width"), wxT("0"))),
							wxstrtol(node->GetPropVal(wxT("height"), wxT("0"))),
							wxColour(node->GetPropVal(wxT("color"), wxT("#000000"))));

	if (type == SHAPE_TEXT) {
		Text *t = static_cast<Text*>(s);
		t->setText(node->GetNodeContent());
	}

	return s;
}
