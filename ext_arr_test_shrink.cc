#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "extendible_array.h"

int main(){
  ExtendibleArray<int> a;
  int disp = 7000;
  a.grow(disp);
  a.print();
  for (int i = 0; i < disp; i ++){
    a[i] = i;
    printf("A[%d] = %d\t",i,a[i]);
  }
  printf("\n");
  while(a.number_of_elements > 0 ){
    int r = rand()%200+1;
    if (r > a.number_of_elements) r = a.number_of_elements;
    printf("SZ: %d - Shrinking by %d\n",a.number_of_elements,r);
    a.shrink(r);
    for (int j = 0; j < a.number_of_elements; j ++){
      a[j] = rand()%20; // Checking that each element can be assigned
    }
  }
  printf("\n");
}
