#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "extendible_array.h"

int main(){
  ExtendibleArray<int> a;
  int disp = 0;
  for (int i = 0; i < 20; i ++ ){
    int r = rand()%10;
    printf("Randomly growing by.. %d\n",r);
    a.grow(r);
    for (int j = 0; j < r; j++){
      a[disp+j] = disp+j;
    }
    disp+=r;
  }
  a.print();
  for (int i = 0; i < disp; i ++){
    printf("A[%d] = %d\t",i,a[i]);
  }
  printf("\n");
  while(a.number_of_elements > 0 ){
    int r = rand()%5;
    if (r > a.number_of_elements) r = a.number_of_elements;
    a.shrink(r);
    for (int j = 0; j < a.number_of_elements; j ++){
      a[j] = rand()%20;
    }
  }
  printf("\n");
}
