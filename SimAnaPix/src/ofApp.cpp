#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0,100, 25);
	ofSetVerticalSync(false);

	ofEnableAlphaBlending();
 	ofLoadImage(sample_tex_img, shrd->image_files[1]);
	sample_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void ofApp::update()
{
	if(shrd->gui_changed == true){
		ofLoadImage(sample_tex_img, shrd->image_files[shrd->dropdownvalue]);
		sample_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		shrd->gui_changed = false;
	}

}

void ofApp::draw(){
	ofSetColor(255);

	int o_x = -1 * (shrd->mouse_x_dr - shrd->IP_pos_x - shrd->prevrw / 2) * shrd->truth_scalefac;
	int o_y = -1 * (shrd->mouse_y_dr - shrd->IP_pos_y - shrd->prevrh / 2) * shrd->truth_scalefac;

	o_x = o_x + (((shrd->IP_max_w - sample_tex_img.getWidth() / shrd->scalefac) / 2) * shrd->truth_scalefac);
	o_y = o_y + (((shrd->IP_max_h - sample_tex_img.getHeight() / shrd->scalefac) / 2) * shrd->truth_scalefac);
	o_x = o_x - mD_x;
	o_y = o_y - mD_y;
	sample_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	sample_tex_img.draw(o_x, o_y, sample_tex_img.getWidth() * shrd->m_zoom_fac, sample_tex_img.getHeight() * shrd->m_zoom_fac);
	/// cout<< preview_tex_img.getWidth()<< endl;

	ofDrawBitmapString(ofToString(ofGetFrameRate()), 250, 20);
	ofDrawBitmapString(ofToString(shrd->mouse_x), 250, 40);
	ofDrawBitmapString(ofToString(shrd->mouse_y), 250, 60);
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}

void ofApp::gotMessage(ofMessage msg) {}

void ofApp::windowResized(int w, int h){
//	dim_monitor1 = ofToString(w)+ "x" + ofToString(h);

}

void ofApp::mouseDragged(int x, int y, int button){
	mD_x = mP_x - x;
	mD_y = mP_y - y;
	cout << "mouse dragged: " << mD_x << "  " << mD_y << endl;
	shrd->dragOffset_x = mD_x;
	shrd->dragOffset_y = mD_y;
}

void ofApp::mousePressed(int x, int y, int button){
	cout <<"mouse pressed: "<< x << "  " << y <<endl;
	mP_x = x;
	mP_y = y;

}


void ofApp::mouseReleased(int x, int y, int button){
	cout << "mouse released: " << x << "  " << y << endl;
	shrd->prevrx = shrd->prevrx + shrd->dragOffset_x / shrd->truth_scalefac;
	shrd->prevry = shrd->prevry + shrd->dragOffset_y / shrd->truth_scalefac;
//shrd->dragOffset_x = 0;
//	shrd->dragOffset_y = 0;
}

cv::Mat ofApp::ofImgToCVMat(ofImage const& img_in){
	auto pix_ = img_in.getPixels();
	cv::Mat out_m =  cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}

