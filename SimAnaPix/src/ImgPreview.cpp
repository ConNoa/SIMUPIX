#include "ImgPreview.hpp"

ImgPreview::ImgPreview()
    {
        std::cout << "ImgPreview is being created" << std::endl;
    }

ImgPreview::~ImgPreview()
    {
        std::cout <<"ImgPreview is being deleted"  << std::endl;
    }

ImgPreview::ImgPreview(ofTexture const& img_in, int x, int y, int w, int h) : 
    prev_img{img_in},
    pos_x_{x},
    pos_y_{y},
    max_w_{w},
    max_h_{h}{}


void ImgPreview::setup()
{
    pos_x_ = shrd->IP_pos_x;
    pos_y_ = shrd->IP_pos_y;
    max_w_ = shrd->IP_max_w;
    max_h_ = shrd->IP_max_h;

    pnt[0].x = 0;
    pnt[0].y = 0;
    pnt[1].x = (float)(ofGetWidth());
    //std::cout << "ImgPreview ofGetWidth" << ofGetWidth() << std::endl;
    //std::cout << "ImgPreview ofGetHeight" << ofGetHeight() << std::endl;
    pnt[1].y = 0;
    pnt[2].x = (float)ofGetWidth();
    pnt[2].y = (float)ofGetHeight();
    pnt[3].x = 0;
    pnt[3].y = (float)(ofGetHeight());
   // shrd->draw_bnds.set(pnt[0], pnt[2]);

     shrd->mouse_x_dr = pos_x_ + max_w_ / 2;
     shrd->mouse_y_dr = pos_y_ + max_h_ / 2;

     shrd->dragOffset_x = 0;
     shrd->dragOffset_y = 0;
}

void ImgPreview::draw()
{       
       // cout<<"Img Preview :: draw()" <<endl;
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofBeginShape();
        ofFill();
        ofSetColor(0);
        ofDrawRectangle(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, max_w_, max_h_);
        ofEndShape();
        ofSetColor(255);
        shrd->scalefac = max((shrd->actl_img.getWidth() / max_w_), (shrd->actl_img.getHeight() / max_h_));
        shrd->truth_scalefac = shrd->scalefac * (float)shrd->m_zoom_fac;
        shrd->actl_img.draw(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, shrd->actl_img.getWidth() / shrd->scalefac, shrd->actl_img.getHeight() /shrd->scalefac);
        ofBeginShape();
        ofNoFill();
        ofSetColor(50, 205, 50);
        ofDrawRectangle(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, max_w_, max_h_);
        ofEndShape();
        ofSetColor(255);
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        draw_prev_rect();

    return;
}

void ImgPreview::draw_prev_rect()
{
    //cout << "Img Preview :: draw_prev_rect()" << endl;

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofBeginShape();
    ofNoFill();
    ofSetColor(255, 0, 255);
    shrd->prevrw = shrd->main_window_w / shrd->actl_img.getWidth() * (shrd->actl_img.getWidth() / shrd->truth_scalefac);
    shrd->prevrh = shrd->main_window_h / shrd->actl_img.getHeight() * (shrd->actl_img.getHeight() / shrd->truth_scalefac);
    shrd->prevrx = shrd->mouse_x_dr + shrd->dragOffset_x / shrd->truth_scalefac;
    shrd->prevry = shrd->mouse_y_dr + shrd->dragOffset_y / shrd->truth_scalefac;

    ofDrawRectangle(shrd->prevrx, shrd->prevry, shrd->prevrw, shrd->prevrh);
    //ofDrawRectangle(pos_x_+0, pos_y_+0, shrd->prevrw, shrd->prevrh);

    ofEndShape();
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void ImgPreview::set_x(int x)
{
    pos_x_ = x;
}

void ImgPreview::set_y(int y)
{
    pos_y_ = y;
}

void ImgPreview::set_w(int w)
{
    max_w_ = w;
}

void ImgPreview::set_h(int h)
{
    max_h_ = h;
}

void ImgPreview::set_img(ofTexture const& img){
    shrd->prev_img = img;
}


int ImgPreview::get_x()
{
    return pos_x_;
}

int ImgPreview::get_y()
{
    return pos_y_;
}

int ImgPreview::get_w()
{
    return max_w_;
}

int ImgPreview::get_h()
{
    return max_h_;
}
