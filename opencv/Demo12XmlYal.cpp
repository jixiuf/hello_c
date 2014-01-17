//  -*- coding:utf-8-dos -*-
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
// opencv 对xml  yaml 格式的操作，
// 比如 读 写 mat 对象 ， 序列 ， map  ，及自定义对象
// http://docs.opencv.org/doc/tutorials/core/file_input_output_with_xml_yml/file_input_output_with_xml_yml.html#fileinputoutputxmlyaml
// 自定义对象 本例未给出示例
void write_mat_test(){

  // <?xml version="1.0"?>
  // <opencv_storage>
  // <mymat type_id="opencv-matrix">
  //   <rows>3</rows>
  //   <cols>2</cols>
  //   <dt>"3u"</dt>
  //   <data>
  //     0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0</data></mymat>
  // </opencv_storage>

  Mat m = Mat::zeros(3 ,2,CV_8UC3);
  FileStorage fs("out_demo12_mat.xml",FileStorage::WRITE); //
  fs<<"mymat" <<m;
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
  // 我测试的时候 yaml 格式的没输出出来
  FileStorage fs2("out_demo12_mat.yml",FileStorage::WRITE); //
  fs<<"mymat" <<m;
  fs.release();         //
}
void read_mat_test(){
  FileStorage fs("out_demo12_mat.xml",FileStorage::READ);
  Mat m;
  fs["mymat"]>>m;               // 读取数据的方式
  std::cout << m.size() << std::endl;
}
void  write_string(){
  FileStorage fs("out_demo12_string.xml",FileStorage::WRITE); //
  fs<<"str" <<"hello";
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}
void  read_string(){
  FileStorage fs("out_demo12_string.xml",FileStorage::READ); //
  string str;
  fs["str"]>>str;
  std::cout << "read the string:"<<str << std::endl;
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}


void  write_seq(){
  FileStorage fs("out_demo12_seq.xml",FileStorage::WRITE); //
  // strings=["hello" ,"world"];
  fs<<"strings" <<"[";
  fs<<"hello" <<"world";
  fs<<"]";
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}
void  read_seq(){
  FileStorage fs("out_demo12_seq.xml",FileStorage::READ); //
  FileNode node=fs["strings"];
  if(node.type()!=FileNode::SEQ){
    std::cout << "seq format error!!!!!" << std::endl;
    exit(1);
  }

  FileNodeIterator it = node.begin(),end=node.end();
  std::cout << "string seq:[" ;
  for (; it!=end; it++) {
    std::cout << (string)*it<<"," ;
  }
  std::cout << "]" << std::endl;

  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}


void  write_map(){
  FileStorage fs("out_demo12_map.xml",FileStorage::WRITE); //
  double d=4;
  int i =2;
  fs<<"mymap" <<"{";
  fs<<"key1" <<"value1";
  fs<<"key2" <<i;
  fs<<"key3" <<d;
  fs<<"}";
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}

void  read_map(){
  FileStorage fs("out_demo12_map.xml",FileStorage::READ); //
  FileNode node=fs["mymap"];
  string key1=(string)node["key1"];
  int key2=(int)node["key2"];
  double key3=(double)node["key3"];

  std::cout << "map::  " <<"stringkey:"<<key1 <<","<<"intkey:"<<key2<<","<<"doublekey3:"<<key3<< std::endl;
  fs.release();                 // 主动释放 ， 不调用也可以， 对像销毁的时候  ，自动释放
}
int main(int argc, char *argv[]) {
  write_mat_test();
  read_mat_test();

  write_string();
  read_string();

  write_seq();
  read_seq();

  write_map();
  read_map();
  return 0;
}
