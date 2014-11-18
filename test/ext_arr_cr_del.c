#include "../include/extendible_array.h"

int main(){
  ExtendibleArray<int>* a = new ExtendibleArray<int>();
  a->grow(3000);
  delete a;
}
