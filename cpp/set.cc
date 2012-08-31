#include <iostream>
#include <set>
using namespace std;

int main(int argc, char *argv[]){
  set<string> s;
  s.insert("s");
  if( s.count("s")){
    set<string>::iterator it =s.find("s");
    cout << *it;
  }
  return 0;
}
