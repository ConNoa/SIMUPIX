#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <map>

using namespace std;

struct lib_ex{
    map<int, cv::Mat> ex_layer;   //key is cosin_exp , val is cv:Mat
};

struct lib_si{
    map<int, lib_ex> si_layer;    //key is exponent, val is ex_layer
};

struct filter_lib{
    map<int, lib_si>it_layer;     //key is iterations, val is si_layer
};
/*
struct KeyTriple {
    int a;
    int b;
    int c;
};

bool operator<(KeyTriple const & lhs, KeyTriple const & rhs) {
    if (lhs.a < rhs.a) return true;
    if (rhs.a < lhs.a) return false;
    if (lhs.b < rhs.b) return true;
    if (rhs.b < lhs.b) return false;
    if (lhs.c < rhs.c) return true;
    return false;

    // Alternatively, if you can use C++11 but don't want a tuple for a key
    return std::tie(lhs.a, lhs.b, lhs.c) < std::tie(rhs.a, rhs.b, rhs.c);
}
*/


#endif
