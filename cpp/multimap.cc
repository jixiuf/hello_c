#include <iostream>
#include <map>
using namespace std;
using std::multimap;

void test1(){
  multimap<string,int> mmap;
  mmap.insert(make_pair("k",100));
  mmap.insert(make_pair("k",200));
  mmap.insert(make_pair("k2",200000));
  multimap<string,int>::size_type k_cnt = mmap.count("k");
  multimap<string,int>::iterator it= mmap.find("k");
  for (multimap<string,int>::size_type i = 0; i <k_cnt ; i++,it++){
    cout<<"value"<<i<<"="<< it->second<<endl;
  }
  cout<<endl;
}
void test2(){
  multimap<string,int> mmap;
  mmap.insert(make_pair("k",100));
  mmap.insert(make_pair("k",200));
  mmap.insert(make_pair("k2",200000));
  multimap<string,int>::iterator it = mmap.lower_bound("k");
  while (it != mmap.upper_bound("k")){
    cout<<it->first<<"="<< it->second<<endl;
    it++;
  }
  cout<<endl;
}

int main(int argc, char *argv[]){
  test1();
  test2();
  return 0;
}
