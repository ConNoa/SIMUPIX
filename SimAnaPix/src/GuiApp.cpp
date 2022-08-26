#include "GuiApp.h"

void GuiApp::setup(){
    ofSetVerticalSync(true);
    // Backgroundcolor
    ofBackground(999999);

    shrd->gui_changed = false;
    shrd->bHide = false;
    shrd->filter_loaded = false;
    shrd->pixel_filter_exists = false;
    shrd->x_roi = 100;
    shrd->y_roi = 100;
    shrd->width_roi = 10;
    shrd->height_roi = 10;

    read_Corpus();
    ofLoadImage(shrd->prev_img, shrd->image_files[0]);
    setup_gui();
    setup_filter();

    setup_imgPreview();

    if (!(shrd->bHide))draw_gui();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() - 200, 20);
    ofDrawBitmapString(ofToString(shrd->mouse_x), ofGetWidth() - 200, 40);
    ofDrawBitmapString(ofToString(shrd->mouse_y), ofGetWidth() - 200, 60);
}

void GuiApp::update(){
    // recompute sizes and dimensions
    shrd->dim_SP_ges_x = shrd->superpixel_width + shrd->border_width;
    shrd->dim_SP_ges_y = shrd->superpixel_height + shrd->border_height;

    for (int i = 0; i < shrd->components.size(); i++)
        shrd->components[i]->update();
}

void GuiApp::draw(){

    draw_filterPreview();

    draw_imgPreview();

    draw_Preview_Rect();

    if (!shrd->bHide)draw_gui();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() - 200, 20);
    ofDrawBitmapString(ofToString(shrd->mouse_x), ofGetWidth() - 200, 40);
    ofDrawBitmapString(ofToString(shrd->mouse_y), ofGetWidth() - 200, 60);
}

// Get files of input folder:
void GuiApp::read_Corpus(){
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(shrd->source_folder.c_str())) == NULL)
    {
        std::cout << "Error(" << errno << ") opening " << shrd->source_folder << std::endl;
    }

    const std::string srce_fldr_path = shrd->source_folder;
    const char* chr_srce_fldr_path = srce_fldr_path.c_str();

    while ((dirp = readdir(dp)) != NULL)
    {
        if (((std::string("README")).compare(dirp->d_name) != 0) && ((std::string(".")).compare(dirp->d_name) != 0) && ((std::string("..")).compare(dirp->d_name) != 0))
        {
            std::cout << "Found " << dirp->d_name << std::endl;
            // Magick::Image local_file_image(source_folder + "/" + dirp->d_name);
            // if (check_format(local_file_image) == true)
            // {
            char newname[800];
            strcpy(newname, "01_possible_corpus/");
            std::strcat(newname, dirp->d_name);
            std::cout<< "newname before pushback! "<< newname <<std::endl;
            shrd->image_files.push_back(std::string(newname));

            // }
            // else
            // {
            // 	std::cout << source_folder + "/" + dirp->d_name << " has wrong format" << std::endl;
            // 	moveFileTo(dirp->d_name, source_folder, reject_folder);
            // 	char newname[800];
            // 	strcpy(newname, "wrong_format_");
            // 	std::strcat(newname, dirp->d_name);
            // 	rename_file(dirp->d_name, reject_folder, newname);
            // }
        }
        std::cout << std::endl;
    }
    closedir(dp);
    std::cout << "Number of files in possible corpus: " << shrd->image_files.size() << std::endl;
    return;
}

void GuiApp::setup_gui()
{
    //-------------GÚI INTERFACE------------------------------------------------
    shrd->pos_s1_x = 10;
    shrd->pos_s1_y = 100;
    shrd->pos_s2_x = 10;
    shrd->pos_s2_y = 350;
    shrd->pos_s3_x = 10;
    shrd->pos_s3_y = 10;

    shrd->m_sampleamm_abs.set("Sampleammount ABS", 1000, 10, 200000);
    shrd->m_sampleamm_rel.set("Sampleammount REL", 10, 0, 100);
    shrd->m_superpix_res.set("Superpixel Res.", 100, 0, 100);
    shrd->superpixel_width.set("S.Pix width", 10, 1, 19);
    shrd->superpixel_height.set("S.Pix height", 10, 1, 19);
    shrd->cosx_e.set("Cosx^", 1, 0, 15);
    shrd->cosy_e.set("Cosy^", 1, 0, 15);
    shrd->border_width.set("Border width", 0, 0, 5);
    shrd->border_height.set("Border height", 0, 0, 5);

    shrd->m_gui = new ofxDatGui();
    shrd->m_gui->addLabel("Sample Parameters");
    shrd->m_gui->addSlider(shrd->m_sampleamm_abs);
    shrd->m_gui->addSlider(shrd->m_sampleamm_rel);
    shrd->m_gui->addSlider(shrd->m_superpix_res);
    shrd->m_gui->addSlider(shrd->superpixel_width);
    shrd->m_gui->addSlider(shrd->superpixel_height);
    shrd->m_gui->addSlider(shrd->cosx_e);
    shrd->m_gui->addSlider(shrd->cosy_e);
    shrd->m_gui->addSlider(shrd->border_width);
    shrd->m_gui->addSlider(shrd->border_height);
    shrd->m_gui->setPosition(20, 100);
    shrd->m_gui->onSliderEvent(this, &GuiApp::onSliderEvent);

    shrd->dropdown = new ofxDatGuiDropdown("Image Data", shrd->image_files);
    shrd->dropdown->setPosition(20, 700);
    shrd->dropdown->expand();
    shrd->dropdown->onDropdownEvent(this, &GuiApp::onDropdownEvent);
    shrd->components.push_back(shrd->dropdown);

    shrd->m_zoom_fac.set("Zoom Factor Main", 1, 1, 20);
    shrd->zoom_gui = new ofxDatGui();
    shrd->zoom_gui->addLabel("additional Parameters");
    shrd->zoom_gui->addSlider(shrd->m_zoom_fac);
    shrd->zoom_gui->setPosition(315, 950);
    shrd->zoom_gui->onSliderEvent(this, &GuiApp::onSliderEvent);

}

void GuiApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << e.target->getName() << " : " << e.value << endl;
    compute_alphfilter(shrd->superpixel_width, shrd->superpixel_height, shrd->cosx_e, shrd->cosy_e);
}

void GuiApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    shrd->dropdownvalue = e.child;
    shrd->gui_changed = true;
    load_selImg(e);
}

void GuiApp::compute_alphfilter(int w_, int h_, int cosx_, int cosy_)
{
    // cout<<"compute_aplhfilter"<<endl;
    shrd->actual_filterdata = shrd->pix_filter.get_FMat2D(w_, h_, cosx_, cosy_);
    draw_filterPreview();
    return;
}

void GuiApp::load_selImg(ofxDatGuiDropdownEvent in_)
{
    cout << "onDropdownEvent: " << in_.child << endl;

    ofLoadImage(shrd->prev_img, shrd->image_files[in_.child]);
}

void GuiApp::draw_filterPreview()
{
    // cout<<"drawing Filterprev"<<endl;
    int x_ = 300;
    int y_ = 50;
    int wi_ = 250;
    int he_ = 250;
    int fp_w = wi_ / shrd->dim_SP_ges_x;
    int fp_h = he_ / shrd->dim_SP_ges_y;
    int scale_fak = min(fp_w, fp_h);

    // cout << actual_filterdata << endl;
    fp_w = 20;
    fp_h = fp_w;

    ofSetRectMode(OF_RECTMODE_CORNER);
    ofBeginShape();
    // ofSetColor(255);
    // ofDrawRectangle(x_, y_, fp_w*dim_SP_ges_x, fp_h*dim_SP_ges_y);
    for (int i = 0; i < shrd->superpixel_width; i++)
    {
        for (int j = 0; j < shrd->superpixel_height; j++)
        {
            // Mat actual_filterdata = pix_filter.get_FMat2D(superpixel_width, superpixel_height, cosx_e, cosy_e);
            int field_alpha = shrd->actual_filterdata.at<uchar>(j, i);
            ofFill();
            ofSetColor(field_alpha);
            // draw rectangle for Pixel
            // with (pos_x, pos_y, breite, höhe)
            ofDrawRectangle(x_ + fp_w * i, y_ + fp_h * j, fp_w - 2, fp_h - 2);
        }
    }
    ofSetColor(0);
    // draw under Border
    ofDrawRectangle(x_, y_ + fp_h * shrd->superpixel_height, fp_w * shrd->dim_SP_ges_x, fp_h * shrd->border_height);
    // draw right Border
    ofDrawRectangle(x_ + fp_w * shrd->superpixel_width, y_, fp_w * shrd->border_width, fp_h * shrd->dim_SP_ges_y);
    ofEndShape();
    shrd->compute_filter = false;
    return;
}

void GuiApp::setup_filter()
{
    shrd->pix_filter.intg_array_map(1, 20, 1000);

    shrd->pix_filter.createFilter_xy(shrd->superpixel_width, shrd->superpixel_height, shrd->cosx_e, shrd->cosy_e);
    shrd->filter_exists = true;
    cout << "setup_filter()" << endl;

    compute_alphfilter(shrd->superpixel_width, shrd->superpixel_height, shrd->cosx_e, shrd->cosy_e);
}

void GuiApp::setup_imgPreview()
{

    shrd->PR_pos_x_ = 300;
    shrd->PR_pos_y_ = 600;
    shrd->PR_max_w_ = 400;
    shrd->PR_max_h_ = 300;

    shrd->pnt[0].x = 0;
    shrd->pnt[0].y = 0;
    shrd->pnt[1].x = (float)(ofGetWidth());
    shrd->pnt[1].y = 0;
    shrd->pnt[2].x = (float)ofGetWidth();
    shrd->pnt[2].y = (float)ofGetHeight();
    shrd->pnt[3].x = 0;
    shrd->pnt[3].y = (float)(ofGetHeight());
    shrd->draw_bnds.set(shrd->pnt[0], shrd->pnt[2]);

    shrd->mouse_x_dr = shrd->PR_pos_x_ + shrd->PR_max_w_ / 2;
    shrd->mouse_y_dr = shrd->PR_pos_y_ + shrd->PR_max_h_ / 2;

    shrd->dragOffset_x = 0;
    shrd->dragOffset_y = 0;
}

void GuiApp::draw_imgPreview(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofBeginShape();
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(shrd->PR_pos_x_ + shrd->PR_max_w_ / 2, shrd->PR_pos_y_ + shrd->PR_max_h_ / 2, shrd->PR_max_w_, shrd->PR_max_h_);
    ofEndShape();
    ofSetColor(255);
    shrd->scalefac = max((shrd->prev_img.getWidth() / shrd->PR_max_w_), (shrd->prev_img.getHeight() / shrd->PR_max_h_));
    shrd->truth_scalefac = shrd->scalefac * (float)shrd->m_zoom_fac;
    shrd->prev_img.draw(shrd->PR_pos_x_ + shrd->PR_max_w_ / 2, shrd->PR_pos_y_ + shrd->PR_max_h_ / 2, shrd->prev_img.getWidth() / shrd->scalefac, shrd->prev_img.getHeight() / shrd->scalefac);
    ofBeginShape();
    ofNoFill();
    ofSetColor(50, 205, 50);
    ofDrawRectangle(shrd->PR_pos_x_ + shrd->PR_max_w_ / 2, shrd->PR_pos_y_ + shrd->PR_max_h_ / 2, shrd->PR_max_w_, shrd->PR_max_h_);
    ofEndShape();
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CORNER);

    return;
}

void GuiApp::draw_Preview_Rect()
{
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofBeginShape();
    ofNoFill();
    ofSetColor(255, 0, 255);
    shrd->prevrw = shrd->main_window_w / shrd->prev_img.getWidth() * (shrd->prev_img.getWidth() / shrd->truth_scalefac);
    shrd->prevrh = shrd->main_window_h / shrd->prev_img.getHeight() * (shrd->prev_img.getHeight() / shrd->truth_scalefac);
    shrd->prevrx = shrd->mouse_x_dr + shrd->dragOffset_x / shrd->truth_scalefac;
    shrd->prevry = shrd->mouse_y_dr + shrd->dragOffset_y / shrd->truth_scalefac;

    ofDrawRectangle(shrd->prevrx, shrd->prevry, shrd->prevrw, shrd->prevrh);
    ofEndShape();
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void GuiApp::draw_gui()
{

    for (int i = 0; i < shrd->components.size(); i++)
        shrd->components[i]->draw();
    // gui.draw();
    // gui_s2.draw();
    // gui_s3.draw();
    return;
}

void GuiApp::mouseDragged(int x, int y, int button)
{
    if ((shrd->last_click_x > shrd->PR_pos_x_) && (shrd->last_click_x < (shrd->PR_pos_x_ + shrd->PR_max_w_)) && (shrd->last_click_y > shrd->PR_pos_y_) && (shrd->last_click_y < (shrd->PR_pos_y_ + shrd->PR_max_h_)))
    {
        // cout << "mouse-dr   x:" << x << " y:" << y << " button:" << button << endl;
        if ((x > (shrd->PR_pos_x_ + shrd->prevrw / 2)) && (x < (shrd->PR_pos_x_ + shrd->PR_max_w_ - shrd->prevrw / 2)))
        {
            shrd->mouse_x_dr = x;
            if ((y >= (shrd->PR_pos_y_ + shrd->prevrh / 2)) && (y < (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2)))
            {
                shrd->mouse_y_dr = y;
            }
        }
        else if ((y >= (shrd->PR_pos_y_ + shrd->prevrh / 2)) && (y < (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2)))
        {
            shrd->mouse_y_dr = y;
        }
    }

    shrd->mouse_x = x;
    shrd->mouse_y = y;
    // compute_filter = true;
}

void GuiApp::mousePressed(int x, int y, int button)
{
    shrd->last_click_x = x;
    shrd->last_click_y = y;

    if ((shrd->last_click_x > shrd->PR_pos_x_) && (shrd->last_click_x < (shrd->PR_pos_x_ + shrd->PR_max_w_)) && (shrd->last_click_y > shrd->PR_pos_y_) && (shrd->last_click_y < (shrd->PR_pos_y_ + shrd->PR_max_h_)))
    {

        cout << "mouse-pr   x:" << x << " y:" << y << " button:" << button << endl;
        if ((x > (shrd->PR_pos_x_ + shrd->prevrw / 2)) && (x < (shrd->PR_pos_x_ + shrd->PR_max_w_ - shrd->prevrw / 2)))
        {
            shrd->mouse_x_dr = x;
            if ((y >= (shrd->PR_pos_y_ + shrd->prevrh / 2)) && (y < (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2)))
            {
                shrd->mouse_y_dr = y;
            }
        }
        else if ((y >= (shrd->PR_pos_y_ + shrd->prevrh / 2)) && (y < (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2)))
        {
            shrd->mouse_y_dr = y;
        }

        if ((y >= (shrd->PR_pos_y_)) && (y < (shrd->PR_pos_y_ + shrd->prevrh / 2)))
        {
            shrd->mouse_y_dr = (shrd->PR_pos_y_ + shrd->prevrh / 2);
        }
        else if ((y >= (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2)) && (y < (shrd->PR_pos_y_ + shrd->PR_max_h_)))
        {
            shrd->mouse_y_dr = (shrd->PR_pos_y_ + shrd->PR_max_h_ - shrd->prevrh / 2);
        }

        if ((x >= (shrd->PR_pos_x_)) && (x < (shrd->PR_pos_x_ + shrd->prevrw / 2)))
        {
            shrd->mouse_x_dr = (shrd->PR_pos_x_ + shrd->prevrw / 2);
        }
        else if ((x >= (shrd->PR_pos_x_ + shrd->PR_max_w_ - shrd->prevrw / 2)) && (x < (shrd->PR_pos_x_ + shrd->PR_max_w_)))
        {
            shrd->mouse_x_dr = (shrd->PR_pos_x_ + shrd->PR_max_w_ - shrd->prevrw / 2);
        }
    }

    shrd->mouse_x = x;
    shrd->mouse_y = y;
}

void GuiApp::keyReleased(int key)
{
}

void GuiApp::mouseMoved(int x, int y)
{
    // cout << "mooove GUI mouse-pr   x:" << x << " y:" << y << " button:" << endl;
    // mouse_x = x;
    // mouse_y = y;
    // return;
}

void GuiApp::mouseReleased(int x, int y, int button)
{
    std::cout << "mouse released" << std::endl;
}

void GuiApp::mouseEntered(int x, int y)
{
}

void GuiApp::mouseExited(int x, int y)
{
    // gui->scalefac) / 2) * gui->scalefac
    return;
}

void GuiApp::keyPressed(int key)
{
    // if(key == 'h'){
    // 	bHide = !bHide;
    // }
    // else if(key == 's'){
    // 	gui.saveToFile("settings.xml");
    // }
    // else if(key == 'l'){
    // 	gui.loadFromFile("settings.xml");
    // }
    // else if(key == ' '){
    //   ofSetColor(255);
    // }
}
