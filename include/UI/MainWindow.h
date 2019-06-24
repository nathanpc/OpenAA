/**
 * UI/MainWindow.h
 * The main window where all the magic happens.
 *
 * @author: Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <wx/wx.h>
#include <wx/menu.h>

class MainWindow: public wxFrame {
	private:
	// Menu items.
	wxMenu *menuFile;
	wxMenu *menuHelp;
	wxMenuBar *menuBar;
	
	// UI generation.
	void generateMenuBar();
	
	// Events.
	void OnExit(wxCommandEvent& evt);
	void OnAbout(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
	
	public:
	MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
};

#endif /* _MAINWINDOW_H_ */
