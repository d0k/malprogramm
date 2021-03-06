#include <wx/print.h>
#include <wx/colordlg.h>

#include "window.h"
#include "images.h"

BEGIN_EVENT_TABLE(Window, wxFrame)
EVT_MENU_RANGE(0, 7, Window::OnShapeSet)
EVT_MENU_RANGE(10, 18, Window::OnColorSet)

EVT_MENU(wxID_UNDO, Window::OnUndo)
EVT_MENU(wxID_PRINT, Window::OnPrint)
EVT_MENU(wxID_NEW, Window::OnNew)
EVT_MENU(wxID_OPEN, Window::OnOpen)
EVT_MENU(wxID_SAVE, Window::OnSave)
EVT_MENU(wxID_CLOSE, Window::OnQuit)

EVT_CLOSE(Window::OnClose)
END_EVENT_TABLE()

Window::Window() : wxFrame(NULL, wxID_ANY, _("Malprogramm"), wxDefaultPosition, wxSize(800, 600)) {
#ifdef __WXMSW__
	SetIcon(wxICON(MAINICON));
#endif
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	canvas = new Canvas(this);
	sizer->Add(canvas, 1, wxEXPAND);

	SetSizer(sizer);
	SetAutoLayout(true);

	createToolbar();

	canvas->setShape(ShapeFactory::SHAPE_LINE);
	canvas->setColor(*wxBLACK);
	canvas->SetCursor(*wxCROSS_CURSOR);

	Show();
}

void Window::createToolbar() {
	wxToolBar *toolbar = CreateToolBar();

	wxBitmap bline = wxMEMORY_BITMAPEX(line, wxBITMAP_TYPE_PNG);
	wxBitmap btriangle = wxMEMORY_BITMAPEX(triangle, wxBITMAP_TYPE_PNG);
	wxBitmap bquad = wxMEMORY_BITMAPEX(quad, wxBITMAP_TYPE_PNG);
	wxBitmap bhexa = wxMEMORY_BITMAPEX(hexagon, wxBITMAP_TYPE_PNG);
	wxBitmap bocta = wxMEMORY_BITMAPEX(octagon, wxBITMAP_TYPE_PNG);
	wxBitmap bcircle = wxMEMORY_BITMAPEX(circle, wxBITMAP_TYPE_PNG);
	wxBitmap bguy = wxMEMORY_BITMAPEX(guy, wxBITMAP_TYPE_PNG);
	wxBitmap btext = wxMEMORY_BITMAPEX(text, wxBITMAP_TYPE_PNG);

	toolbar->AddRadioTool(0, wxT("Line"), bline, wxNullBitmap, _("Line"));
	toolbar->AddRadioTool(1, wxT("Triangle"), btriangle, wxNullBitmap, _("Undo"));
	toolbar->AddRadioTool(2, wxT("Quad"), bquad, wxNullBitmap, _("Rectangle"));
	toolbar->AddRadioTool(3, wxT("6"), bhexa, wxNullBitmap, _("Hexagon"));
	toolbar->AddRadioTool(4, wxT("8"), bocta, wxNullBitmap, _("Octagon"));
	toolbar->AddRadioTool(5, wxT("Circle"), bcircle, wxNullBitmap, _("Circle"));
	toolbar->AddRadioTool(6, wxT("Guy"), bguy, wxNullBitmap, _("Guy"));
	toolbar->AddRadioTool(7, wxT("Text"), btext, wxNullBitmap, _("Text"));

	toolbar->AddSeparator();

	wxBitmap bcolor1 = wxMEMORY_BITMAPEX(color1, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor2 = wxMEMORY_BITMAPEX(color2, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor3 = wxMEMORY_BITMAPEX(color3, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor4 = wxMEMORY_BITMAPEX(color4, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor5 = wxMEMORY_BITMAPEX(color5, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor6 = wxMEMORY_BITMAPEX(color6, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor7 = wxMEMORY_BITMAPEX(color7, wxBITMAP_TYPE_PNG);
	wxBitmap bcolor8 = wxMEMORY_BITMAPEX(color8, wxBITMAP_TYPE_PNG);
	wxBitmap bchoosecolor = wxMEMORY_BITMAPEX(choosecolor, wxBITMAP_TYPE_PNG);

	toolbar->AddRadioTool(13, wxT("Black"), bcolor4, wxNullBitmap, _("Black"));
	toolbar->AddRadioTool(12, wxT("Gray"), bcolor3, wxNullBitmap, _("Gray"));
	toolbar->AddRadioTool(11, wxT("Light Gray"), bcolor2, wxNullBitmap, _("Light Gray"));
	toolbar->AddRadioTool(10, wxT("White"), bcolor1, wxNullBitmap, _("White"));
	toolbar->AddRadioTool(14, wxT("Red"), bcolor5, wxNullBitmap, _("Red"));
	toolbar->AddRadioTool(15, wxT("Yellow"), bcolor6, wxNullBitmap, _("Yellow"));
	toolbar->AddRadioTool(16, wxT("Green"), bcolor7, wxNullBitmap, _("Green"));
	toolbar->AddRadioTool(17, wxT("Blue"), bcolor8, wxNullBitmap, _("Blue"));
	toolbar->AddRadioTool(18, wxT("Custom"), bchoosecolor, wxNullBitmap, _("Custom"));

	toolbar->AddSeparator();

	wxBitmap bundo = wxMEMORY_BITMAPEX(undo, wxBITMAP_TYPE_PNG);
	wxBitmap bprint = wxMEMORY_BITMAPEX(print, wxBITMAP_TYPE_PNG);
	wxBitmap bnewfile = wxMEMORY_BITMAPEX(newfile, wxBITMAP_TYPE_PNG);
	wxBitmap bopenfile = wxMEMORY_BITMAPEX(openfile, wxBITMAP_TYPE_PNG);
	wxBitmap bsave = wxMEMORY_BITMAPEX(save, wxBITMAP_TYPE_PNG);
	wxBitmap bquit = wxMEMORY_BITMAPEX(quit, wxBITMAP_TYPE_PNG);

	toolbar->AddTool(wxID_UNDO, wxT("Undo"), bundo, _("Undo"));
	toolbar->AddTool(wxID_PRINT, wxT("Print"), bprint, _("Print"));
	toolbar->AddTool(wxID_NEW, wxT("New"), bnewfile, _("New"));
	toolbar->AddTool(wxID_OPEN, wxT("Open"), bopenfile, _("Open"));
	toolbar->AddTool(wxID_SAVE, wxT("Save"), bsave, _("Save"));
	toolbar->AddTool(wxID_CLOSE, wxT("Quit"), bquit, _("Quit"));
	toolbar->Realize();
}

void Window::OnShapeSet(wxCommandEvent& evt) {
	canvas->setShape(static_cast<ShapeFactory::shapeType>(evt.GetId()));
}

void Window::OnColorSet(wxCommandEvent& evt) {
	switch (evt.GetId()) {
	case 10:
		canvas->setColor(*wxWHITE);
		break;
	case 11:
		canvas->setColor(wxColour(wxT("#C0C0C0")));
		break;
	case 12:
		canvas->setColor(wxColour(wxT("#808080")));
		break;
	case 13:
		canvas->setColor(*wxBLACK);
		break;
	case 14:
		canvas->setColor(*wxRED);
		break;
	case 15:
		canvas->setColor(wxColour(wxT("yellow")));
		break;
	case 16:
		canvas->setColor(*wxGREEN);
		break;
	case 17:
		canvas->setColor(*wxBLUE);
		break;
	case 18:
		canvas->setColor(wxGetColourFromUser(this, canvas->getColor()));
		break;
	}
}

void Window::OnUndo(wxCommandEvent& WXUNUSED(event)) {
	canvas->undo();
	canvas->Refresh();
}

void Window::OnPrint(wxCommandEvent& WXUNUSED(event)) {
	wxPrinter print;
	print.GetPrintDialogData().GetPrintData().SetOrientation(wxLANDSCAPE);
	print.Print(this, canvas);
}

bool Window::askToSave() {
	if (canvas->isModified()) {
		int out = wxMessageBox(_("Save unsaved data?"), wxMessageBoxCaptionStr, wxYES_NO|wxCANCEL);
		if (out == wxYES) {
			wxCommandEvent tmp;
			OnSave(tmp);
		} else if (out == wxCANCEL) {
			return false;
		}
	}
	return true;
}

void Window::OnNew(wxCommandEvent& WXUNUSED(event)) {
	if (askToSave()) {
		canvas->clear();
		canvas->Refresh();
	}
}

void Window::openFile(const wxString& filename, const Data::fileFormat format) {
	canvas->clear();

	if (canvas->fromFile(filename, format)) {
		canvas->Refresh();
		SetTitle(wxString::Format(_("%s - Malprogramm"), filename.c_str()));
	} else {
		wxMessageBox(_("Error reading File!"), _("Error"), wxICON_ERROR);
	}
}

void Window::OnOpen(wxCommandEvent& WXUNUSED(event)) {
	if (askToSave()) {
		wxFileDialog d(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, wxT("Native (*.zngx)|*.zngx|Legacy 16 Bit (*.ZNG)|*.ZNG|Legacy 32 Bit (*.ZNG)|*.ZNG"));

		if (d.ShowModal() == wxID_OK)
			openFile(d.GetPath(), static_cast<Data::fileFormat>(d.GetFilterIndex()));
	}
}

void Window::OnSave(wxCommandEvent& WXUNUSED(event)) {
	wxFileDialog d(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, wxT("Native (*.zngx)|*.zngx|PNG (*.png)|*.png"), wxFD_SAVE);
	bool saved = false;

	while (!saved && d.ShowModal() == wxID_OK) {
		switch (d.GetFilterIndex()) {
		case 0:
			saved = canvas->toFile(d.GetPath());
			if (saved)
				SetTitle(wxString::Format(_("%s - Malprogramm"), d.GetFilename().c_str()));
			break;
		case 1:
			{
			const wxSize& cs = canvas->GetClientSize();
			wxBitmap buffer(cs.GetWidth(), cs.GetHeight());
			wxMemoryDC dc(buffer);
			canvas->Draw(dc);
			saved = buffer.SaveFile(d.GetPath(), wxBITMAP_TYPE_PNG);
			}
			break;
		}
		if (!saved)
			wxMessageBox(_("Error writing File!"), _("Error"), wxICON_ERROR);
	}
}

void Window::OnQuit(wxCommandEvent& WXUNUSED(event)) {
	Close();
}

void Window::OnClose(wxCloseEvent& evt) {
	if (!askToSave())
		evt.Veto();
	else
		Destroy();
}
