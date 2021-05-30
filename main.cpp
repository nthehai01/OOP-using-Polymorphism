#include "figure.h"

int main()
{
  ComplexShape<vector<Shape *>> shape;
  // ComplexShape<DynamicArray> shape;
  // ComplexShape<LinkedList> shape;
  shape.input();
  cout << "--------" << endl;
  shape.sortByPerimeter();
  shape.output();

  return 0;
}