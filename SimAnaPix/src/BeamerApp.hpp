#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "State.h"

class BeamerApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	cv::Mat ofImgToCVMat(ofImage const &img_in);

	shared_ptr<State> shrd;

	ofTexture preview_tex_img;
	ofPoint pnt[4];
	ofRectangle draw_bnds;

	int mP_x, mP_y;
	int mD_x = 0;
	int mD_y = 0;
};

