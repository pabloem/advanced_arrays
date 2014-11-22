#ifndef ADVANCED_ARRAYS
#define ADVANCED_ARRAYS

#define FINE 0
#define FAIL 1
#define FAIL_TO_ALLOC 2
#define BAD_INPUT 3

#define COLLISION 1

#define MAX(X,Y) (((X)>(Y)) ? (X):(Y))

#define PRIME_SDD 99839
int Hash(long int key, int k){
  return (key*k)%PRIME_SDD;
}

/*
  Function generate_k()
  Returns: This function returns the value of K such that 0<=K<=PRIME_SDD.
  K is calculated at random, but in this case it uses modulo operator over
  the rand() function. This makes elements at the beginning more likely.

  === TODO: A more robust implementation of generate_k() ===
 */
#include <cstdlib>
int generate_k(){
  return rand() % PRIME_SDD;
}

#include <assert.h>
#endif
