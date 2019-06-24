/**
 * UI/MainWindow.cpp
 * The main window where all the magic happens.
 *
 * @author: Nathan Campos <nathanpc@dreamintech.net>
 */

#include <UI/MainWindow.h>

#include <wx/wx.h>
#include <wx/menu.h>

// Set the events for this window.
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_MENU(wxID_EXIT, MainWindow::OnExit)
	EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
wxEND_EVENT_TABLE();

/**
 * Creates the main window of the application.
 * 
 * @param title Window title.
 * @param pos   Window starting position.
 * @param size  Window starting size.
 */
MainWindow::MainWindow(const wxString& title, const wxPoint& pos,
					   const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	// Create the menu bar and the status bar.
	generateMenuBar();
	CreateStatusBar();
	SetStatusText("Hello, World");
}

/**
 * Generates the window's menu.
 */
void MainWindow::generateMenuBar() {
	// Build the File menu.
	menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT);
	
	// Build the Help menu.
	menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	
	// Create the menu bar.
	menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
}

/**
 * Close the window.
 * 
 * @param evt Event object.
 */
void MainWindow::OnExit(wxCommandEvent& evt) {
	Close(true);
}

/**
 * Show the about message box.
 * 
 * @param evt Event object.
 */
void MainWindow::OnAbout(wxCommandEvent& evt) {
	wxMessageBox("OpenAA v0.1a developed by Nathan Campos", "About",
				 wxOK | wxICON_INFORMATION);
}
