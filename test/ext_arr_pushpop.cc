#include "../include/extendible_array.h"

#define GROW 0
#define SHRINK 1

int main(){
  ExtendibleArray<int> a;
  for(int i = 0; i < 20; i++){
    int ps_el = rand();
    printf("Pushing %d\n",ps_el);
    a.push(ps_el);
  }
  for(int i = 0; i < 20; i ++){
    int pp_el = a.pop();
    printf("Popping %d\n",pp_el);
  }
  return 0;
}
