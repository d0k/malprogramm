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

	bool toFile(const wxString& filename);
	bool fromFile(const wxString& filename);

	enum legacyFormat { FORMAT_16, FORMAT_32 };
	bool fromLegacyFile(const wxString& filename, const legacyFormat format);
protected:
	bool modified;
	std::list<Shape> shapelist;
};

#endif
