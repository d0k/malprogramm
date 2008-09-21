#ifndef _DATA_H
#define _DATA_H

#include <list>
#include <wx/wx.h>

class Data {
public:
	class Shape {
	public:
		wxString type;
		long left, top, width, height;
		wxColour color;
		wxString text;
	};
	Data() : modified(false) {}
	void undo();
	void clear() { shapelist.clear(); }
	bool isModified() const { return modified; }

	void toFile(const wxString& filename);
	void fromFile(const wxString& filename);
protected:
	bool modified;
	std::list<Shape> shapelist;
};

#endif
