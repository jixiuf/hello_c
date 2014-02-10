#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
// http://code.google.com/codejam/contest/351101/dashboard#s=p0
using namespace std;

void find_out_result(int test_case_index,int credit_sum_value,int* elems,int elem_cnt){
  for (int i = 0; i < elem_cnt-1; ++i){
      for (int j = i+1; j < elem_cnt; ++j){
        if (elems[i]+elems[j]==credit_sum_value){
          std::cout <<"Case #"<<test_case_index <<": "<< i+1<<" "<<j+1<<std::endl;
          return;
        }
      }
  }
}

int main(int argc, char *argv[]){
  // ifstream fin("A-small-practice.in");
  ifstream fin("A-large-practice.in");
  //
  int test_case_cnt;
  int credit_sum_value;
  int elem_cnt;
  int tmp;


  if(!fin){
    std::cerr << "no input file found"<<std::endl;
    throw runtime_error("no input file found");
  }

  fin>>test_case_cnt;

  for (int test_case_idx = 0; test_case_idx < test_case_cnt; ++test_case_idx){
    fin>>credit_sum_value;
    fin>>elem_cnt;
    int elems[elem_cnt];
    for (int j = 0; j < elem_cnt; ++j){
      fin>>tmp;
      elems[j]=tmp;
    }
    find_out_result(test_case_idx,credit_sum_value,elems,elem_cnt);
  }

  fin.close();

  return 0;
}
