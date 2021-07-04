#include "../Field/Field.h"
#include <iostream>
int
main()
{
  std::cout << "Hello world!" << std::endl;

  Field f;
  f.CreateField(8, 8);
  return 0;
}