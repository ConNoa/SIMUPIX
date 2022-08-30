#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"
#include "radarApp.hpp"
#include "State.h"
//#include "ImgPrev.hpp"

//========================================================================
int main()
{
	std::cout <<"main().cpp"<<std::endl;
	// ------All Window Parameters---------------------

	int fhd_w = 1920;
	int fhd_h = 1028;
	int gui_w = 960;
	int gui_h = 1080;

	int main_window_w = 1920;
	int main_window_h = 1080;

	// -----------------------------
	std::cout << "main().cpp 1" << std::endl;

	ofGLFWWindowSettings settings;

	settings.setSize(fhd_w, fhd_h);
	settings.setPosition(ofVec2f(1920, 0));
	settings.resizable = true;
	settings.title = "PREVIEW";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	std::cout << "main().cpp 2" << std::endl;

	settings.setSize(gui_w, gui_h);
	settings.setPosition(ofVec2f(100, 100));
	settings.resizable = false;
	settings.title = "USER-INTERFACE";
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	std::cout << "main().cpp 3" << std::endl;

	settings.setSize(fhd_w, fhd_h);
	settings.setPosition(ofVec2f(1920, 1140));
	settings.resizable = false;
	settings.title = "BEAMER-OUTPUT";
	shared_ptr<ofAppBaseWindow> radarWindow = ofCreateWindow(settings);
	std::cout << "main().cpp 4" << std::endl;

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	shared_ptr<radarApp> radarAppl(new radarApp);
	std::cout << "main().cpp 5" << std::endl;

	shared_ptr<State> shrd(new State);
	std::cout << "main().cpp 6" << std::endl;

	mainApp->shrd = shrd;
	mainApp->shrd->main_window_w = main_window_w;
	mainApp->shrd->main_window_h = main_window_h;
	std::cout << "main().cpp 7" << std::endl;

	guiApp->shrd = shrd;
	radarAppl->shrd = shrd;


	std::cout << "ofRunApp guiWin" << std::endl;

	ofRunApp(guiWindow, guiApp);

	std::cout << "ofRunApp mainWindow" << std::endl;

	ofRunApp(mainWindow, mainApp);

	std::cout << "ofrunApp radarWindow" << std::endl;

	ofRunApp(radarWindow, radarAppl);
	ofRunMainLoop();
}