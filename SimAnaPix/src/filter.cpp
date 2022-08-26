#include "filter.hpp"

//using namespace std;

// Member functions definitions including constructor
Filter::Filter() {
  cout << "Filter is being created" << endl;
}

Filter::~Filter() {
  cout << "Filter is being deleted" << endl;
}

unordered_map<FilterKey, cv::Mat, FilterKey::Hash>Filter::get_filter(){
  return ht_filter;
}

cv::Mat Filter::get_FMat2D()
{
  return m_filter;
}

cv::Mat Filter::get_FMat2D(int x_, int y_, int cosx_, int cosy_)
{
  cv::Mat filter_out = Mat(x_, y_, CV_64FC1);

  Mat x_mult(x_, 1, CV_64FC1);
  Mat y_mult(y_, 1, CV_64FC1);

  if ((m_cosin_map.count(x_) > 0) || m_cosin_map.count(y_) > 0)
  {
   // std::cout << "x_  Found" << std::endl;
    x_mult = get_FMat1D(x_, cosx_);
    //std::cout << "y_  Found" << std::endl;
    y_mult = get_FMat1D(y_, cosy_);
  
 /* else
  {
    intg_array_map(x_, x_, m_iterations);
    cout<< "arraymap for x created"<<endl;
    x_mult = get_FMat1D(x_, cosx_);
  }
  */
 /* else
  {
    intg_array_map(y_, y_, m_iterations);
    cout << "arraymap for x created" << endl;
    y_mult = get_FMat1D(y_, cosy_);
  }
  */
    y_mult = y_mult.t();
    filter_out = y_mult * x_mult;
    //  cout <<"x_mult  ->"<< x_mult<< endl;
    //  cout <<"y_mult  ->"<< y_mult<< endl;
    //  cout <<"filterout  ->"<< filter_out<< endl;
    filter_out = scaleMatto255(filter_out);
    // filter_out = filter_out*-1;
    // cout <<"filterout  ->"<< filter_out<< endl;

    // cv::Mat add_to_mat = cv::Mat(filter_out.size(), CV_64FC1, Scalar(255));
    // cout <<"addout  ->"<< add_to_mat<< endl;
    // filter_out = filter_out+add_to_mat;
    // cout <<"filterout  ->"<< filter_out<< endl;
    filter_out = convertTo_CV_8U(filter_out);
    //  cout <<"filterout  ->"<< filter_out<< endl;
    m_filter =  filter_out;
  }
  else{
    createFilter_xy(x_, y_, cosx_, cosy_);
  }
  return m_filter;
}

cv::Mat Filter::get_FMat1D(int key_, int exp_){
  cv::Mat tempMat = cv::Mat(m_cosin_map[key_].at(exp_));
  return tempMat;
}

map<int, vector<cv::Mat>>Filter::get_map(){
  return m_cosin_map;
}

void Filter::set_exp(int exp_){
  m_exponent = exp_;
  return;
}

void Filter::set_it(int it_){
  m_iterations = it_;
  return;
}

void Filter::set_filtersize(int fs_){
  m_filtersize = fs_;
  return;
}


void Filter::createFilter(int size_, int exp_, int iterations_){
  set_filtersize(size_);
  set_exp(exp_);
  set_it(iterations_);
  cv::Mat output = doppelintegral_array(low_bound, high_bound, m_filtersize, m_iterations, m_exponent);

  cout << "Filter cos^"<<m_exponent<<" with size "<< m_filtersize<<" computed with "<< m_iterations << " iterations.  M="  << output<< endl << endl;

  ht_filter.insert(make_pair<FilterKey>({to_string(m_iterations), to_string(m_exponent), to_string(m_filtersize)},output));

  return;
}

void Filter::createFilter_xy(int width_, int height_, int cosx_, int cosy_){
  cv::Mat filter_out = Mat(height_, width_, CV_64FC1);
  cout << filter_out.rows <<" rows in mat [createfilter], cols:"<<filter_out.cols<<endl;
  //
  //---------------------if bedingung läuft noch nicht keine matritzen vorgespeichert
  //
  cout<< "no filtermats"<<endl;
  cv::Mat x_mult = integral_array(width_, 1000, cosx_);
  cv::Mat y_mult = integral_array(height_,1000,  cosy_);
  y_mult = y_mult.t();
  filter_out = y_mult * x_mult;
  //cout <<"x_mult  ->"<< x_mult<< endl;
  //cout <<"y_mult  ->"<< y_mult<< endl;
  //cout << "filterout  ->" << filter_out << endl;
  filter_out = scaleMatto255(filter_out);
  // filter_out = filter_out*-1;
  // cout <<"filterout  ->"<< filter_out<< endl;
  // cv::Mat add_to_mat = cv::Mat(filter_out.size(), CV_64FC1, Scalar(255));
    // cout <<"addout  ->"<< add_to_mat<< endl;
    // filter_out = filter_out+add_to_mat;
//    cout << "filterout  ->" << filter_out << endl;
  filter_out = convertTo_CV_8U(filter_out);
    //cout << "filterout  ->" << filter_out << endl;
 
  m_filter = filter_out;
  return;
}


double Filter::fun (double x, int exp){
  double func = pow(cos(x), exp);
  return func;
}

cv::Mat Filter::convertTo_CV_8U (cv::Mat const& input_mat){
  cv::Mat output_mat;
  input_mat.convertTo(output_mat, CV_8U);

  return output_mat;
}

cv::Mat Filter::scaleMatto255 (cv::Mat const& input_mat){
  cv::Mat output(input_mat);
  double minVal;
  double maxVal;
  cv::minMaxLoc(input_mat, &minVal, &maxVal);
//  cout<< "maxval is : "<< maxVal<< endl;

  double mult_factor = 255/maxVal;
  output = output * mult_factor;

  return output;
}

double Filter::integral(double lbx, double ubx, double steps, int exp_){

  double range_x = ubx-lbx;
  double d_x = range_x/steps;
  double act_x = lbx;

  double sum = 0;
    for(int j = 0; j < steps; j++){
      double area_x = fun(act_x, exp_)* d_x;
      sum =  sum + area_x;
      act_x = act_x + d_x;
      //cout << " act_x = "<< act_x<< endl;
    }
    return sum;
}

cv::Mat Filter::integral_array (int size_, int partial_steps_, int exp_){
  cv::Mat mat_temp = cv::Mat(1,size_, CV_64FC1);

  double d_xy = (double)(high_bound-low_bound)/size_;

  double act_lbx = low_bound;
  double act_ubx = low_bound+d_xy;

    for(int j=0; j < size_; j++){
      double val = integral(act_lbx, act_ubx, partial_steps_, exp_);
      mat_temp.at<double>(j) = val;
      act_lbx += d_xy;
      act_ubx += d_xy;
    }
  mat_temp = scaleMatto255(mat_temp);
  //cout << mat_temp << endl;
  //cv::Mat mat_CV_8U = convertTo_CV_8U(mat_temp);

  return mat_temp;
}

map<int, vector<cv::Mat>>Filter::get_intgrl_array_map(int size_from, int size_to, int iterations_){

    map<int,vector<cv::Mat>> integralMap;
    for(int i= size_from; i <= size_to; i++ ){
    for(int j = 1 ; j <= m_exp_max; j++){
      vector<cv::Mat> tempVec;
      if ( integralMap.find(i) == integralMap.end() ) {
        cout << " key " << i <<" not found: inserting map" <<endl;
        cv::Mat mat_temp = cv::Mat(1,i, CV_64FC1);
        mat_temp = integral_array(i,iterations_, j);
        tempVec.push_back(mat_temp);
        integralMap.insert(std::pair<int,vector<cv::Mat>>(i, tempVec));
        cout << " immer noch hier "<< endl;

    } else {
        cout << " Key found before"<<  i << " got pushed back to vec in integalmap[""<<i<<""]" ;
    // found
        tempVec = integral_array(i,iterations_, j);

        integralMap[i].push_back(integral_array(i, iterations_, j));
      }
    }
  }
  return integralMap;
}

void Filter::intg_array_map(int size_from, int size_to, int iterations_){

    for(int i= size_from; i <= size_to; i++ ){
    for(int j = 1 ; j <= m_exp_max; j++){
      vector<cv::Mat> tempVec;
      if ( m_cosin_map.find(i) == m_cosin_map.end() ) {
        cout << " key " << i <<" not found. adding size "<< i<<"cosin^"<<j<<" ." <<endl;
        cv::Mat mat_temp = cv::Mat(1,i, CV_64FC1);
        mat_temp = integral_array(i,iterations_, j);
        tempVec.push_back(mat_temp);
        m_cosin_map.insert(std::pair<int,vector<cv::Mat>>(i, tempVec));

    } else {
        cout << "found before size "<<  i << ", adding cosin^"<<j<<"]" ;
        cv::Mat mat_temp = cv::Mat(1,i, CV_64FC1);
        mat_temp = integral_array(i,iterations_, j);
        tempVec.push_back(mat_temp);
        //m_cosin_map.insert(std::pair<int,vector<cv::Mat>>(i, tempVec));
        m_cosin_map[i].push_back(integral_array(i, iterations_, j));
      }
    }
  }

  return;
}


double Filter::doppelintegral(double lbx, double ubx, double lby, double uby, double steps, int m_exp){

  double range_x = ubx-lbx;
  double d_x = range_x/steps;
  double act_x = lbx;
  double range_y = uby-lby;
  double d_y = range_y/steps;
  double act_y = lby;

  double sum = 0;

  for(int i = 0; i < steps ; i++){
    for(int j = 0; j < steps; j++){
      double area_x = fun(act_x, m_exp)* d_x;
      double area_y = fun(act_y, m_exp)* d_y;
      sum =  sum + (area_x * area_y);
      act_x = act_x + d_x;
      //cout << " act_x = "<< act_x<< endl;
    }
    act_x = lbx;
    act_y = act_y + d_y;
    //cout << " act_y = "<< act_y<< endl;
  }
 return sum;
}

cv::Mat Filter::doppelintegral_array (double lb, double ub, int n, int partial_steps_, int m_exp){
  cv::Mat mat_temp = cv::Mat(n,n, CV_64FC1);

  double d_xy = (double)(ub-lb)/n;

  double act_lbx = lb;
  double act_ubx = lb+d_xy;
  double act_lby = lb;
  double act_uby = lb+d_xy;

  for(int i=0; i < n; i++){
    for(int j=0; j < n; j++){
      double val = doppelintegral(act_lbx, act_ubx, act_lby, act_uby, partial_steps_, m_exp);
      mat_temp.at<double>(j,i) = val;
      act_lbx += d_xy;
      act_ubx += d_xy;
    }
    act_lbx = lb;
    act_ubx = lb+d_xy;
    act_lby += d_xy;
    act_uby += d_xy;
  }

  mat_temp = scaleMatto255(mat_temp);
  cv::Mat mat_CV_8U = convertTo_CV_8U(mat_temp);

  return mat_CV_8U;
}

/*void Filter::write_to_database(int  loop_nmbr, int max_size){
  //setting txt name
  stringstream sstxt;
  sstxt << database_folder<< "/filterdata_n"<<loop_nmbr<<"_"<<max_size<<".txt";
  string filenametxt = sstxt.str();
  cout<< "writing file "<<filenametxt <<"\n";
  //writing readable txt-file
  int filtercounter = 0;

  for(auto& siz_it : m_filterlibrary){
    for(auto& ex_it : siz_it.second){
      for(auto& loop_it : ex_it.second){


        cv::FileStorage fs(filenametxt,cv::FileStorage::WRITE);
        //stringstream fle_txt;
        //fle_txt << "F"<<filtercounter<<siz_it.first <<"_"<< ex_it.first << "_" << loop_it.first<<"_";
        fs << "F"<<filtercounter<<"25"<<"_"<< "10" << "_" <<"1000" <<"_"<< m_filterlibrary[25][10][1000];
        filtercounter += 1;
      }
   }
 }
  cout << "file written \n";
  return;
}
*/

void read(const cv::FileNode& node, filterdata& x, const filterdata& default_value = {1,1,1}){
  if(node.empty())
    x = default_value;
  else
    x.read(node);
}

void write(cv::FileStorage& fs, const std::string&, const filterdata& x){
  x.write(fs);
}


void Filter::save_file(){
  //The data structure identifying XML and YAML in OpenCV is FileStorage
  stringstream sstxt;
  sstxt << database_folder<< "/filterdata_n.yaml";
  string filename = sstxt.str();
  cv::FileStorage fs(filename, cv::FileStorage::WRITE);
  //output
  for(auto& [key, val] : ht_filter){
//    fs << "Filter";
    fs << "i"<<key.s1;
    fs << "e"<<key.s2;
    fs << "s"<<key.s3;
    fs << "Mat"<<val;
  }
  return;
}


void Filter::save_file(int maxsize_, int iters_){
  //The data structure identifying XML and YAML in OpenCV is FileStorage
  stringstream sstxt;
  sstxt << database_folder<< "/filterdata_"<<maxsize_<<"x"<<maxsize_<<"_"<<iters_<<".yaml";
  string filename = sstxt.str();
  cv::FileStorage fs(filename, cv::FileStorage::WRITE);
  //output
  for(auto& [key_it, val_it] : ht_filter){
  std::stringstream ss_k;
  ss_k  <<"F_"<< key_it.s1 << "_"<< key_it.s2 << "_"  << key_it.s3;
  std::string key_str = ss_k.str();
  fs <<"Filtertable";
  fs << "i"<<key_it.s1 <<"e"<< key_it.s2 << "s"<<key_it.s3 <<"m" <<val_it;
  cout << key_it.s1 << "  "<< key_it.s2 << "  "  << key_it.s3 <<"         "  << val_it <<endl;
  }
  return;
}

/*
void Filter::parse_file(){
  stringstream sstxt;
  sstxt << database_folder<< "/filterdata_12x12_100.yaml";
  string filename = sstxt.str();
  cv::FileStorage fs(filename, cv::FileStorage::READ);
  cv::FileNodeIterator mIte = fs.begin(); mIte != fs.end(); mIte++) {
    auto node = file[idx];
    cout<< node->Type()<<endl;
  }
}
*/

void Filter::read_file(){
  cout<< "read_file()"<<endl;
  stringstream sstxt;
  sstxt << database_folder<< "/filterdata_12x12_100.yaml";
  string filename = sstxt.str();
  // read:
  cv::FileStorage fs(filename, cv::FileStorage::READ);
  cv::FileNode key = fs["Filtertable"];
  cv::FileNodeIterator it = key.begin();
  cv::FileNodeIterator it_end = key.end(); // Go through the node
  for (; it != it_end; ++it){
    cout << "reading filenode\n";
    string keyname;
    pair<filterdata, cv::Mat> p;
    fs["Filtertable"] >> keyname;
    cout << "keyname is " << keyname<< endl;
    cv::Mat tempMat;
    fs["FilterMat"] >> p.second;
/*
    if ( !m_filter_lib.insert(p).second ) {
      cout<<"  Element already present..."<<"\n";
    }
*/
/*
    cout << "m_filter_libbev.insert(p);mapsize : "<< ht_filter.size()<<endl;
    m_filter_lib.insert(p);
    cout << "after.insert(p)mapsize : "<< m_filter_lib.size()<<endl;


    cout<<"  Element "<< p.first.filtersize<<" "<<p.first.cosin_exp<<" "<<p.first.number_iterations<<" "<<"\n";

    for(map<filterdata, cv::Mat>::const_iterator it = m_filter_lib.begin(); it != m_filter_lib.end(); ++it){
        std::cout << " M =  "<< it->second << "\n";
    }
*/
  }
  return;
}
