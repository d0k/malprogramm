#ifndef _DATA_H
#define _DATA_H

#include <list>
#include <wx/wx.h>

class Data {
public:
	enum shapeType { SHAPE_LINE = 0, SHAPE_TRIANGLE, SHAPE_RECTANGLE, SHAPE_HEXAGON,
					 SHAPE_OCTAGON, SHAPE_CIRCLE, SHAPE_GUY, SHAPE_TEXT, SHAPE_UNKNOWN };
	class Shape {
	public:
		shapeType type;
		long left, top, width, height;
		wxColour color;
		wxString text;
	};
	Data() : modified(false) {}
	void undo();
	void clear() { shapelist.clear(); }
	bool isModified() const { return modified; }

	enum fileFormat { FORMAT_XML = 0, FORMAT_16, FORMAT_32 };

	bool toFile(const wxString& filename);
	bool fromFile(const wxString& filename, const fileFormat format = FORMAT_XML);

	static const wxString shapeTypeToText(const shapeType type);
	static shapeType textToShapeType(const wxString& type);
protected:
	bool modified;
	std::list<Shape> shapelist;
private:
	bool fromLegacyFile(const wxString& filename, const fileFormat format);
};

#endif
