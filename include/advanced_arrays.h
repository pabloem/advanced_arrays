#ifndef ADVANCED_ARRAYS
#define ADVANCED_ARRAYS

#define FINE 0
#define FAIL 1
#define FAIL_TO_ALLOC 2
#define BAD_INPUT 3

#define COLLISION 1

#define MAX(X,Y) (((X)>(Y)) ? (X):(Y))

#define PRIME_SDD 6143
int Hash(long int key, int k){
  return (key*k)%PRIME_SDD;
}

#endif
