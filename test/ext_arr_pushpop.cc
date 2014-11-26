#include "../include/extendible_array.h"

#define GROW 0
#define SHRINK 1

int main(){
  ExtendibleArray<int> a;
  for(int i = 0; i < 300; i++){
    int ps_el = rand();
    printf("Pushing %d\n",ps_el);
    a.push(ps_el);
  }
  for(int i = 0; i < 300; i ++){
    int pp_el = a.pop();
    printf("Popping %d\n",pp_el);
  }

  for(int i = 0; i < 400; i ++){
    int op = rand()%2;
    if(op == GROW){
      printf("It %d - Pushing | SZ:%d\n",i,a.number_of_elements);
      a.push(rand());
    }
    if(op == SHRINK){
      printf("It %d - Popping | SZ:%d\n",i,a.number_of_elements);
      a.pop();
    }
  }
  return 0;
}
