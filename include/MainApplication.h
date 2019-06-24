/**
 * MainApplication.h
 * The main entry point for the wxWidgets application.
 *
 * @author: Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _MAINAPPLICATION_H_
#define _MAINAPPLICATION_H_

#include <wx/wx.h>

class MainApplication: public wxApp {
	public:
	virtual bool OnInit();
};

#endif /* _MAINAPPLICATION_H_ */
