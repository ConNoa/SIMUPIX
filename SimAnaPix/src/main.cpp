

#include "ofAppGLFWWindow.h"
#include "ofxCv.h"
#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "BeamerApp.hpp"
#include "State.h"
#include "ImgPreview.hpp"

//========================================================================
int main()
{
	std::cout <<"main().cpp"<<std::endl;
	// ------All Window Parameters---------------------

	int fhd_w = 1920;
	int fhd_h = 1028;
	int gui_w = 960;
	int gui_h = 1080;
	int output_w = 800;
	int output_h = 600;

	int main_window_w = 1920;
	int main_window_h = 1080;

	// -----------------------------

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


	settings.setSize(output_w, output_h);
	settings.setPosition(ofVec2f(1920, 1140));
	settings.resizable = false;
	settings.title = "BEAMER-OUTPUT";
	shared_ptr<ofAppBaseWindow> beamerWindow = ofCreateWindow(settings);


	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	shared_ptr<BeamerApp> beamerAppl(new BeamerApp);
	shared_ptr<State> shrd(new State);

	// weak_ptr<ofApp>prevLink(new ofApp);
	// weak_ptr<ofApp>beamLink(new BeamerApp);



	mainApp->shrd = shrd;
	mainApp->shrd->main_window_w = main_window_w;
	mainApp->shrd->main_window_h = main_window_h;


	guiApp->shrd = shrd;

	beamerAppl->shrd = shrd;

	// guiApp->beam_win = beamLink;
	// guiApp->prev_win = prevLink;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunApp(beamerWindow, beamerAppl);
	ofRunMainLoop();
}