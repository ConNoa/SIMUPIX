#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "State.h"

class radarApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	cv::Mat ofImgToCVMat(ofImage const &img_in);

		shared_ptr<State> shrd;
};

