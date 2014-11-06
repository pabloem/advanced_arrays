#include "../include/extendible_array.h"

#define GROW 0
#define SHRINK 1

int main(){
  ExtendibleArray<int> a;
  a.grow(500);
  while ( a.number_of_elements > 0 ){
    for ( int i = 0; i < a.number_of_elements; i++ ){
      a[i] = i;
    }
    int op = rand()%2;
    if ( op == GROW ){
      int chg = rand()%5+1;
      a.grow(chg);
      printf("GROW %d elms - SZ:%d\n",chg,a.number_of_elements);
    }
    if ( op == SHRINK ){
      int chg = rand()%10+1;
      //      if ( chg > a.number_of_elements ) chg = a.number_of_elements;
      a.shrink(chg);
      printf("SHRINK %d elms - SZ:%d\n",chg,a.number_of_elements);
    }
  }
}
