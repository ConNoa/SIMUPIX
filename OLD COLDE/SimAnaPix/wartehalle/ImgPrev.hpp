 #pragma once

#include "ofxCv.h"
#include "ofxOpenCv.h"
// #include <opencv2/highgui.hpp>
// #include <memory>
// #include "State.h"


class ImgPreview{
public:
    //ImgPreview();
    //ImgPreview(const ImgPreview& img_pr) = default;
    //ImgPreview(ofTexture const& img_in, int x, int y, int w, int h);


    // void setup();
    // void update();
    // void draw();

    // void set_x(int x);
    // void set_y(int y);
    // void set_w(int w);
    // void set_h(int h);
    // //void set_img(ofTexture const& img);

    // int get_x();
    // int get_y();
    // int get_w();
    // int get_h();

    // void load_prev();

    // ///ImgPreview& operator=(ImgPreview newPrev);




    int pos_x_;
    int pos_y_;
    int max_w_;
    int max_h_;

    float truth_scalefac;
    float scalefac;
    float m_zoom_fac;

    ofPoint pnt[4];

    ofTexture prev_img;

};


