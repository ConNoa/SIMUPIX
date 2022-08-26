#include "radarApp.hpp"

void radarApp::setup(){
	ofBackground(0);
	ofSetVerticalSync(false);

}

void radarApp::update(){

}

void radarApp::draw(){

}

cv::Mat radarApp::ofImgToCVMat(ofImage const &img_in)
{
	auto pix_ = img_in.getPixels();
	cv::Mat out_m = cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}
