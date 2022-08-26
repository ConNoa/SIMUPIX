#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "State.h"

class radarApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();


	shared_ptr<State> shrd;
};

