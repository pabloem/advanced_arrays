#include <stdio.h>
#include <vector>
#include "../include/extendible_array.h"

int main(){
  ExtendibleArray<long int> a;
  std::vector<long int> myvector;
  int mf_EA = 0;
  int mf_V = 0;
  printf("Elements,Capacity EA, Capacity V\n");
  for(int i = 0; i < 4000; i++){
    a.grow(1);
    myvector.push_back(i);
    mf_EA = a.memory_footprint()/sizeof(long int);
    mf_V = myvector.capacity();
    printf("%d,%d,%d\n",i+1,mf_EA,mf_V);
  }
  for(int i = 0; i < 4000; i++){
    a.shrink(1);
    myvector.pop_back();
    mf_EA = a.memory_footprint()/sizeof(long int);
    mf_V = myvector.capacity();
    printf("%d,%d,%d\n",i+1,mf_EA,mf_V);
  }
}
