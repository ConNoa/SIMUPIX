#pragma once

struct filterdata{

public:
  int filtersize;
  int cosin_exp;
  int number_iterations;

    filterdata() : filtersize(1), cosin_exp(1), number_iterations(1){}
    filterdata(int size_, int exp_, int iters_){
        filtersize = size_;
        cosin_exp = exp_;
        number_iterations = iters_;
    }

    void read(const cv::FileNode& node){
      filterdata fd;
      filtersize = (int)node["Size"];
      cosin_exp = (int)node["Exponent"];
      number_iterations = (int)node["Iterations"];
      return;

    }
    void write(cv::FileStorage& fs) const {
        fs << "{" << "Size" << filtersize << "Exponent" << cosin_exp << "Iterations" << number_iterations << "}";
    }
    bool  operator==(const filterdata &o) const {
        return (cosin_exp == o.cosin_exp && filtersize == o.filtersize && number_iterations == o.number_iterations);
  }
    bool operator<(const filterdata &o) const {
      return (cosin_exp != o.cosin_exp || filtersize != o.filtersize || number_iterations != o.number_iterations);
    }
};
