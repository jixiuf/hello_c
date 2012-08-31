#include <iostream>
#include <map>
using namespace std;

int main(int argc, char *argv[]){
  map<string,int> m;

  m.insert(make_pair("k1",1));
  m.insert(make_pair("k1",11111));
  m.insert(make_pair("k2",2));
  cout<<"size="<< m.size()<<endl;
  cout<<m["k1"]<<endl;                // 用下标访问，如果map中有以此key为key的，则返回 ，没有的话则会创建之
  cout<<m["k100000"]<<endl;                // 用下标访问，如果map中有以此key为key的，则返回 ，没有的话则会创建之

  int cnt = m.count("k1");      // 存不存在
  cout <<"exits? "<<cnt<<endl;
  map<string,int>::iterator it = m.find("k1");
  cout<<"key="<<it->first<<",value="<<it->second<<endl;
  return 0;
}
