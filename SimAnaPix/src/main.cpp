#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"
#include "radarApp.hpp"
#include "State.h"

//========================================================================
int main()
{

	// ------All Window Parameters---------------------

	int fhd_w = 1920;
	int fhd_h = 1028;
	int gui_w = 960;
	int gui_h = 1080;

	int main_window_w = 1920;
	int main_window_h = 1080;

	// ---------------------------


	ofGLFWWindowSettings settings;

	settings.setSize(fhd_w, fhd_h);
	settings.setPosition(ofVec2f(1920, 0));
	settings.resizable = true;
	settings.title = "PREVIEW";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.setSize(gui_w, gui_h);
	settings.setPosition(ofVec2f(100, 100));
	settings.resizable = false;
	settings.title = "USER-INTERFACE";
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	settings.setSize(fhd_w, fhd_h);
	settings.setPosition(ofVec2f(1920, 1140));
	settings.resizable = false;
	settings.title = "BEAMER-OUTPUT";
	shared_ptr<ofAppBaseWindow> radarWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	shared_ptr<radarApp> radarAppl(new radarApp);

	shared_ptr<State> shrd(new State);
	mainApp->shrd = shrd;
	mainApp->shrd->main_window_w = main_window_w;
	mainApp->shrd->main_window_h = main_window_h;
	guiApp->shrd = shrd;
	radarAppl->shrd = shrd;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunApp(radarWindow, radarAppl);

	ofRunMainLoop();
}