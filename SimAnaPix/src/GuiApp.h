#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "State.h"
#include "ImgPreview.hpp"
#include "CorpusInspektor.hpp"
#include "BeamerApp.hpp"
#include "ofApp.h"


class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void read_Corpus();
    void setup_gui();

    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);

    void compute_alphfilter(int w_, int h_, int cosx_, int cosy_);

    void load_selImg(ofxDatGuiDropdownEvent in_);

    void draw_filterPreview();

    void setup_filter();

    // void setup_imgPreview();

    void draw_imgPreview();

    void draw_Preview_Rect();

    void draw_gui();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void mouseEventPos(int x, int y);

    shared_ptr<State> shrd;

    ofTexture actualImg;

    // // ImagePreview  position and width
    // /*
    // int IP_pos_x_ = shrd-> IP_pos_x;
    // int IP_pos_y_ = shrd-> IP_pos_y;
    // int IP_max_w_ = shrd-> IP_max_h;
    // int IP_max_h_ = shrd-> IP_max_w;
    // */

    // //-------------HeavYDUMMYVAULRS------------
    // //-------------HeavYDUMMYVAULRS------------
    // //-------------HeavYDUMMYVAULRS------------
    // int IP_pos_x_;
    // int IP_pos_y_;
    // int IP_max_w_;
    // int IP_max_h_;
    // //-------------HeavYDUMMYVAULRS------------
    // //-------------HeavYDUMMYVAULRS------------
    // //-------------HeavYDUMMYVAULRS------------
    CorpusInspektor img_corpus;
    ImgPreview img_prev;

    // shared_ptr<ImgPreview> img_prev(new ImgPreview);
    // img_prev->shrd = shrd;

};

