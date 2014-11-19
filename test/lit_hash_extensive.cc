#include "../include/little_hash.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  LittleHashTable<int> *lht;
  srand(10);
  int k = rand()%PRIME_SDD;
  int inserted_elms = 20;
  int arr_sz = 2*inserted_elms*(inserted_elms-1);
  arr_sz -= (1-arr_sz%2);
  k -= (1-k%2);
  printf("Creating hash table with %d elms, and k = %d\n",arr_sz,k);
  lht = new LittleHashTable<int>(arr_sz, k);

  srand(0);
  printf("\nInserting... \n");
  for ( int i = 0; i < 20; i ++){
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm - %d | Hash: %d | Idx: %d\n",elm,h,h%arr_sz);
    int res = lht->insert(elm);
    if ( res == COLLISION ) printf("Not inserted - COLLISION\n");
  }

  srand(0);
  printf("\n\nLooking up...\n");
  for ( int i = 0; i < 30; i++ ){
    if ( i == 20 ){
      printf("\n\nNow failures:\n");
    }
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm - %d | Hash: %d | Idx: %d\n",elm,h,h%arr_sz);
    int res = lht->lookup(elm);
    if ( res != FINE ) fprintf(stdout," - > ERROR\n");
  }

  srand(0);
  printf("\n\nRemoving...\n");
  for ( int i = 0; i < 20; i++ ){
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm - %d | Hash: %d | Idx: %d\n",elm,h,h%arr_sz);
    int res = lht->lookup(elm);
    if ( res != FINE ) fprintf(stdout," - > ERROR\n");
  }

  for ( int i = 0; i < 10000; i++){
    lht = new LittleHashTable<int>(200, k);
    delete lht;
  }
  printf("\n\nEND\n");
}
