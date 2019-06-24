/**
 * MainApplication.cpp
 * The main entry point for the wxWidgets application.
 *
 * @author: Nathan Campos <nathanpc@dreamintech.net>
 */

#include "MainApplication.h"

#include <wx/wx.h>
#include "UI/MainWindow.h"

// Implement the wxWidgets application.
wxIMPLEMENT_APP(MainApplication);

/**
 * Application initialization.
 * 
 * @return True if everything went fine.
 */
bool MainApplication::OnInit() {
	MainWindow *mainWindow = new MainWindow("OpenAA", wxPoint(100, 100),
											wxSize(700, 500));
	mainWindow->Show(true);
	
	return true;
}
