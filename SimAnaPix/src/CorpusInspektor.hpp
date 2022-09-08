#pragma once
#include <opencv2/highgui.hpp>
#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ios>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <experimental/filesystem>
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "State.h"

//#include <Magick++.h>
using namespace cv;
using namespace std;

class CorpusInspektor
{

public:
    void read_corpus();         //read images in folders to get image_file  list

    void load_images();         //load all images from imagelist into vector for image_database fpr fast acces 

    void set_actl_image(int it);
    


    const std::string source_folder = "../01_possible_corpus";
    const std::string res_folder = "../03_received_corpus";
    const std::string reject_folder = "../02_not_used_for_corpus";


    shared_ptr<State> shrd;


    // const std::pair<int, int> disp_res(800, 600);
    // std::vector<std::string> filenames;
    // // std::vector<std::pair<std::string, Mat>> possib_corp_imgs;
    // //std::vector<std::pair<std::string, Magick::Image>> images_possib;
    // std::vector<std::pair<std::string, Mat>> bad_corp;
    // //bool check_format(Magick::Image Image_);

private:
};
