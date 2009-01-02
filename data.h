#ifndef DATA_H
#define DATA_H

#include "shapes.h"

#include <list>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Data {
public:
	Data() : modified(false) {}
	void undo();
	void clear();
	bool isModified() const { return modified; }

	enum fileFormat { FORMAT_XML = 0, FORMAT_16, FORMAT_32 };

	bool toFile(const wxString& filename);
	bool fromFile(const wxString& filename, const fileFormat format = FORMAT_XML);
	virtual ~Data() { clear(); }
protected:
	bool modified;
	std::list<Shape*> shapelist;
private:
	bool fromLegacyFile(const wxString& filename, const fileFormat format);
};

#endif
