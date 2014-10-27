#include <vector>
template<typename T>

class ExtendibleArray 
{
private:
  std::vector<std::unique_ptr<T[]>> index_block;
  unsigned int number_of_elements = 0;

public:
  ExtendibleArray(){
  }
  int grow(unsigned int n)
  {
  }
  int shrink(unsigned int n)
  {
  }
  T& operator[](unsigned int idx){
  }
};
