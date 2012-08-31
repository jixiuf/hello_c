#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;
using std::runtime_error;

ifstream &open_file(ifstream &in,char *file_name){
  in.close();
  in.clear();
  in.open(file_name,fstream::in);
  return in;
}
int main(int argc, char *argv[]){
  ifstream in;
  string line;
  if(argc!=2) throw runtime_error("need a argv as filename");
  if(!open_file(in,argv[1]))  throw runtime_error("open file error;");
  while(getline(in,line)){
    istringstream instr(line);
    string word;
    while(instr>>word){
      cout<<"    "<<word;
    }
    cout<<endl;
  }
  return 0;
}
