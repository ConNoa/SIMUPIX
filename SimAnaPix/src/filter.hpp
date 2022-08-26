#pragma once

#include <iosfwd>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <tuple>
#include <unordered_map>
#include "structs.hpp"
#include "filterdata.hpp"
#include "filterkey.hpp"
#include <vector>



using namespace std;
using namespace cv;


class Filter {

    public:
        Filter();
        ~Filter();

        unordered_map<FilterKey, cv::Mat, FilterKey::Hash>get_filter();
        cv::Mat get_FMat2D();
        cv::Mat get_FMat2D(int x_, int y_, int cosx_, int cosy_);
        cv::Mat get_FMat1D(int key_, int exp_);
        map<int, vector<cv::Mat>>get_map();
        void set_exp(int exp_);
        void set_it(int it_);
        void set_filtersize(int fs_);
        void createFilter(int size_, int exp_, int iterations_);
        void createFilter(int size_x, int size_y, int exp_, int iterations_);
        void createFilter_xy(int width_, int height_, int cosx_, int cosy_);
        double fun(double x, int exp);
        cv::Mat convertTo_CV_8U(cv::Mat const& input_mat);
        double integral(double lbx, double ubx, double steps, int m_exp);
        cv::Mat integral_array (int size_, int partial_steps, int m_exp);
        map<int, vector<cv::Mat>> get_intgrl_array_map(int size_from, int size_to, int iterations_);
        void intg_array_map(int size_from, int size_to, int iterations_);
        cv::Mat scaleMatto255(cv::Mat const& input_mat);
        double doppelintegral(double lbx, double ubx, double lby, double uby, double steps, int m_exp);
        cv::Mat doppelintegral_array(double lb, double ub, int n, int partial_steps, int m_exp);
        void save_file();
        void save_file(int maxsize_, int iters_);
        //void write_to_database(int loop_nmbr, int max_size);
        static void write(cv::FileStorage& fs, const std::string&, const filterdata& x);
        void parse_file();
        void read_file();



    private:
      const std::string database_folder= "../04_database";

      const double m_pi = 3.14159265358979323846;
      const double low_bound  = -m_pi/2;
      const double high_bound = m_pi/2;
            std::unordered_map<FilterKey, cv::Mat, FilterKey::Hash> ht_filter;

            int m_size_x = 3;
            int m_size_y = 3;
            int m_filtersize = 3;
            int m_iterations = 1000;
            int m_exponent = 4;
            int m_exp_max = 16;

            map<int, vector<cv::Mat>> m_cosin_map;
            //key is size  vec[0] -> cos^0 .....
            cv::Mat m_filter;
            map<int, vector<int>> granularity_cosinmap;

};
