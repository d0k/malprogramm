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

	enum fileFormat { FORMAT_XML = 0, FORMAT_16 = 1, FORMAT_32 = 2 };

	bool toFile(const wxString& filename);
	bool fromFile(const wxString& filename, const fileFormat format = FORMAT_XML);
protected:
	bool modified;
	std::list<Shape> shapelist;
private:
	bool fromLegacyFile(const wxString& filename, const fileFormat format);
};

#endif
