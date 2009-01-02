#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "shapes.h"

class ShapeFactory {
public:
	enum shapeType { SHAPE_LINE = 0, SHAPE_TRIANGLE, SHAPE_RECTANGLE, SHAPE_HEXAGON,
	SHAPE_OCTAGON, SHAPE_CIRCLE, SHAPE_GUY, SHAPE_TEXT, SHAPE_UNKNOWN=-1 };
	static Shape* createShape(shapeType type, int left, int top, int width, int height, const wxColour& color);
	static Shape* createShapeFromXML(wxXmlNode *node);
private:
	static shapeType textToShapeType(const wxString& type);
};

#endif
