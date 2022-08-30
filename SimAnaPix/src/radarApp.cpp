#include "radarApp.hpp"

void radarApp::setup(){

	pnt[0].x = (float)-100;
	pnt[0].y = (float)-500;
	pnt[2].x = (float)preview_tex_img.getWidth();
	pnt[2].y = (float)preview_tex_img.getHeight();
	//	draw_bnds.set(pnt[0], pnt[2]);
	pnt[1].x = shrd->mouse_x_dr - shrd->IP_pos_x;
	pnt[1].y = shrd->mouse_y_dr - shrd->IP_pos_y;
	pnt[3].x = (float)ofGetWindowWidth();
	pnt[3].y = (float)ofGetWindowHeight();
	// subsec_bnds.set(pnt[1], pnt[3]);



	ofBackground(0);
	ofSetVerticalSync(false);

	ofEnableAlphaBlending();
	ofLoadImage(preview_tex_img, shrd->image_files[0]);
	preview_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void radarApp::update(){
	if (shrd->gui_changed == true)
	{

		ofLoadImage(preview_tex_img, shrd->image_files[shrd->dropdownvalue]);
		preview_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

		shrd->gui_changed = false;
	}
}

void radarApp::draw(){
	ofSetColor(255);

	int o_x = -1 * (shrd->mouse_x_dr - shrd->IP_pos_x - shrd->prevrw / 2) * shrd->truth_scalefac;
	int o_y = -1 * (shrd->mouse_y_dr - shrd->IP_pos_y - shrd->prevrh / 2) * shrd->truth_scalefac;

	o_x = o_x + (((shrd->IP_max_w - preview_tex_img.getWidth() / shrd->scalefac) / 2) * shrd->truth_scalefac);
	o_y = o_y + (((shrd->IP_max_h - preview_tex_img.getHeight() / shrd->scalefac) / 2) * shrd->truth_scalefac);
	o_x = o_x - mD_x;
	o_y = o_y - mD_y;
	preview_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	preview_tex_img.draw(o_x, o_y, preview_tex_img.getWidth() * shrd->m_zoom_fac, preview_tex_img.getHeight() * shrd->m_zoom_fac);
	/// cout<< preview_tex_img.getWidth()<< endl;

	ofDrawBitmapString(ofToString(ofGetFrameRate()), 250, 20);
	ofDrawBitmapString(ofToString(shrd->mouse_x), 250, 40);
	ofDrawBitmapString(ofToString(shrd->mouse_y), 250, 60);
}

cv::Mat radarApp::ofImgToCVMat(ofImage const &img_in)
{
	auto pix_ = img_in.getPixels();
	cv::Mat out_m = cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}
