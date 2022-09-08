#pragma once

#include <opencv2/highgui.hpp>
#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "State.h"
#include "GuiApp.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "BeamerApp.hpp"
#include <memory>

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();


	void drawPresentWindow();

	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	shared_ptr<State> shrd;

	cv::Mat ofImgToCVMat(ofImage const &img_in);

	// ofImage test_img;
	ofTexture act_shown_img;

	float scalefac;


	//ofTexture preview_tex_img;
	ofTexture sample_tex_img;
	ofPoint pnt[4];
	ofRectangle draw_bnds;
	// ofRectangle subsec_bnds;

	int mP_x, mP_y;
	int mD_x = 0;
	int mD_y = 0;

};
