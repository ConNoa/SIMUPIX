#include "BeamerApp.hpp"

void BeamerApp::setup(){

	ofBackground(0);
	ofSetVerticalSync(false);

	ofEnableAlphaBlending();
	ofLoadImage(preview_tex_img, shrd->image_files[1]);
	preview_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void BeamerApp::update(){
	if (shrd->gui_changed == true)
	{
		ofLoadImage(preview_tex_img, shrd->image_files[shrd->dropdownvalue]);
		preview_tex_img.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	}
	if (shrd->bor_changed == true)
	{

		ofSetWindowShape(shrd->out_res_x, shrd->out_res_y);
		shrd->bor_changed = false;
	}
}

void BeamerApp::draw(){
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

cv::Mat BeamerApp::ofImgToCVMat(ofImage const &img_in)
{
	auto pix_ = img_in.getPixels();
	cv::Mat out_m = cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}
