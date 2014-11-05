#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "extendible_array.h"

int main(){
  ExtendibleArray<int> a;
  int disp = 0;
  for (int i = 0; i < 10; i ++ ){
    int r = rand()%100;
    printf("Randomly growing by.. %d\n",r);
    a.grow(r);
    for (int j = 0; j < r; j++){
      a[disp+j] = disp+j;
    }
    disp+=r;
  }
  a.print();
  for (int i = 0; i < disp; i ++){
    if ( a[i] != i ) printf("\nERROR! --- \n");
    printf("A[%d] = %d\t",i,a[i]);
  }
  printf("\n");
}
