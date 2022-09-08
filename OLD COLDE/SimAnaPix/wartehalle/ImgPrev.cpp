#include "ImgPrev.hpp"


// ImgPreview::ImgPreview():
//     prev_img{},
//     pos_x_{0},
//     pos_y_{0},
//     max_w_{100},
//     max_h_{100}
//     {
//         cout << "ImgPreview is being created" << endl;
//     }

// ImgPreview::~ImgPreview()
//     {
//         cout <<"ImgPreview is being deleted"  << endl;
//     }

// ImgPreview::ImgPreview(ofTexture const& img_in, int x, int y, int w, int h) : 
//     prev_img{img_in},
//     pos_x_{x},
//     pos_y_{y},
//     max_w_{w},
//     max_h_{h}{}


// void ImgPreview::setup()
// {
//     pnt[0].x = 0;
//     pnt[0].y = 0;
//     pnt[1].x = (float)(ofGetWidth());
//     pnt[1].y = 0;
//     pnt[2].x = (float)ofGetWidth();
//     pnt[2].y = (float)ofGetHeight();
//     pnt[3].x = 0;
//     pnt[3].y = (float)(ofGetHeight());
//    // shrd->draw_bnds.set(pnt[0], pnt[2]);

//     // shrd->mouse_x_dr = pos_x_ + max_w_ / 2;
//     // shrd->mouse_y_dr = pos_y_ + max_h_ / 2;

//     // shrd->dragOffset_x = 0;
//     // shrd->dragOffset_y = 0;
// }

// void ImgPreview::draw()
// {
//   /*  if(prev_img != NULL){

//         ofSetRectMode(OF_RECTMODE_CENTER);
//         ofBeginShape();
//         ofFill();
//         ofSetColor(0);
//         ofDrawRectangle(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, max_w_, max_h_);
//         ofEndShape();
//         ofSetColor(255);
//         scalefac = max((prev_img.getWidth() / max_w_), (prev_img.getHeight() / max_h_));
//         truth_scalefac = scalefac * (float)m_zoom_fac;
//         prev_img.draw(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, prev_img.getWidth() / scalefac, prev_img.getHeight() /scalefac);
//         ofBeginShape();
//         ofNoFill();
//         ofSetColor(50, 205, 50);
//         ofDrawRectangle(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, max_w_, max_h_);
//         ofEndShape();
//         ofSetColor(255);
//         ofSetRectMode(OF_RECTMODE_CORNER);
//     }

//     */
//     cout << "weite von prev image "   <<  prev_img.getWidth() <<  endl;

//     return;
// }

// void ImgPreview::set_x(int x)
// {
//     pos_x_ = x;
// }

// void ImgPreview::set_y(int y)
// {
//     pos_y_ = y;
// }

// void ImgPreview::set_w(int w)
// {
//     max_w_ = w;
// }

// void ImgPreview::set_h(int h)
// {
//     max_h_ = h;
// }

// void ImgPreview::set_img(ofTexture const& img){
//     prev_img = img;
// }


// int ImgPreview::get_x()
// {
//     return pos_x_;
// }

// int ImgPreview::get_y()
// {
//     return pos_y_;
// }

// int ImgPreview::get_w()
// {
//     return max_w_;
// }

// int ImgPreview::get_h()
// {
//     return max_h_;
// }
// /*
// ImgPreview& Imgpreview::operator=(ImgPreview newPrev){
    
//     pos_x_ = newPrev.pos_x_;
//     pos_y_ = newPrev.pos_y_;
//     max_w_ = newPrev.max_w_;
//     max_h_ = newPrev.max_h_;
//     prev_img = newPrev.prev_img;
//     return *this;
// }
// */