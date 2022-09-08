#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include <memory>
#include "filter.hpp"
//#include "ImgPrev.hpp"




struct State{
    int main_window_w;
    int main_window_h;

    int last_click_x, last_click_y;

    //---- deklaration for Previewvariables
    int IP_pos_x = 300;
    int IP_pos_y = 600;
    int IP_max_w = 400;
    int IP_max_h = 300;

    int prevrw;
    int prevrh;
    int prevrx;
    int prevry;

    float truth_scalefac;
    float scalefac;

    int mouse_x_dr, mouse_y_dr;
    int dragOffset_x, dragOffset_y;

    //-----------some FLAGS
    bool gui_changed;
    bool prev_mode_bypass;


    int dropdownvalue;

    bool filter_loaded;
    bool filter_exists;
    bool pixel_filter_exists;
    bool bHide;

    const std::string source_folder = "01_possible_corpus";
    const std::string res_folder = "../03_received_corpus";
    const std::string reject_folder = "../02_not_used_for_corpus";

    //--cv::STRUCTS
    Filter pix_filter;



    cv::Mat actual_filterdata;
    cv::Mat lena_mat;
    cv::Mat submat;
    cv::Mat test;

    // Images
    vector<string> image_files = {};
    vector<ofTexture> image_database = {};

    ofTexture prev_img;
    ofPoint pnt[4];
    ofRectangle draw_bnds;

    // ofImage test2_img;
    ofImage filterImage;
    // ofImage roi_1;
    // ofImage roi2;

    ofPixels lena_pix;

    // testparameter
    int x_roi, y_roi;
    int width_roi, height_roi;

    int mouse_x, mouse_y;

    ofxPanel gui;
    float pos_s1_x;
    float pos_s1_y;
    float pos_s2_x;
    float pos_s2_y;
    float pos_s3_x;
    float pos_s3_y;

    ofxPanel gui_s2;
    ofxPanel gui_s3;

    ofxDatGui* m_gui;
    ofxDatGuiDropdown* dropdown;
    ofxDatGui* zoom_gui;
    ofxDatGuiToggle* sample_toggle;

    vector<ofxDatGuiComponent *> components;

    // ofParameterGroup sample_slider_1;
    // ofParameterGroup command_slider_2;
    // ofParameterGroup info_slider_3;

    //-----sampleparameters
    ofParameter<int> m_sampleamm_abs;
    ofParameter<float> m_sampleamm_rel;
    ofParameter<int> m_superpix_res;
    ofParameter<int> superpixel_width;
    ofParameter<int> superpixel_height;
    ofParameter<int> cosx_e;
    ofParameter<int> cosy_e;
    ofParameter<int> border_width;
    ofParameter<int> border_height;

    //-----zoom-GUI
    ofParameter<int> m_zoom_fac;

    //-----command-GUI

    ofParameter<bool> compute_filter;
    ofParameter<bool> randomsamp;
    ofParameter<bool> switch_screen1;
    ofParameter<bool> switch_screen2;

    //----informational-GUI

    ofParameter<int> dim_SP_ges_x;
    ofParameter<int> dim_SP_ges_y;
    ofxLabel dim_monitor1;
    ofxLabel label;

    
};
