#ifndef SHAPES_H
#define SHAPES_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/xml/xml.h>

class Shape {
public:
	virtual void draw(wxDC& dc) const = 0;
	virtual void setPos(int left, int top) { this->left = left; this->top = top; }
	virtual void setSize(int width, int height) { this->width = width; this->height = height; }
	virtual void setEndPos(int left, int top) { this->width = left - this->left; this->height = top - this->top; }
	virtual void setColor(const wxColour& color) { this->color = color; }
	virtual wxXmlNode* toXML(wxXmlNode *root) const;
	virtual const wxString typeAsString() const = 0;
	virtual ~Shape() {}
protected:
	Shape(int left, int top, int width, int height, const wxColour& color)
		 : left(left), top(top), width(width), height(height), color(color) {}
	int left, top;
	int width, height;
	wxColour color;
};

class Line : public Shape {
public:
	Line(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("line"); }
};

class Triangle : public Shape {
public:
	Triangle(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("triangle"); }
};

class Rectangle : public Shape {
public:
	Rectangle(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("rectangle"); }
};

class Hexagon : public Shape {
public:
	Hexagon(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("hexagon"); }
};

class Octagon : public Shape {
public:
	Octagon(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("octagon"); }
};

class Circle : public Shape {
public:
	Circle(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("circle"); }
};

class Guy : public Shape {
public:
	Guy(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	const wxString typeAsString() const { return wxT("guy"); }
};

class Text : public Shape {
public:
	Text(int left, int top, int width, int height, const wxColour& color)
		: Shape(left, top, width, height, color), text(wxT("")) {}
	Text(int left, int top, int width, int height, const wxColour& color, const wxString& text)
		: Shape(left, top, width, height, color) {}
	void draw(wxDC& dc) const;
	void setText(const wxString& text) { this->text = text; }
	wxXmlNode* toXML(wxXmlNode *root) const;
	const wxString typeAsString() const { return wxT("text"); }
private:
	wxString text;
};

#endif
