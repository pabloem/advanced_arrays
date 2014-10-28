#include <vector>
template<typename T>

#define FINE 0
class ExtendibleArray 
{
private:
  std::vector<<T**>2> index_block;
  unsigned int number_of_elements = 0;
  unsigned int capacity = 0;
  unsigned int last_block_size = 0;

public:
  ExtendibleArray(unsigned int n = 0){
    this.index_block = NULL;
    if ( n > 0 ){
      this.grow(n);
    }
  }
  int grow(unsigned int n)
  {
    // If we have not fully taken the last block, we take it
    if ( number_of_elements < capacity ){
      /* If the available elements in the last block are enough, we take them
         otherwise, we fill up the block and prepare to continue */
      int diff = (n > capacity-number_of_elements) ? 
        capacity-number_of_elements : n;
      number_of_elements += diff;
      n = n - diff;
    }
    while ( n > 0 ){
      <T*> new_block = malloc(capacity*sizeof(<T>));
    }
  }
  int shrink(unsigned int n)
  {
  }
  T& operator[](unsigned int idx){
  }
};
