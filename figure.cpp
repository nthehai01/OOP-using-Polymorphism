#include "figure.h"

double getDistance(Point a, Point b)
{
  return sqrt(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2));
}

// Circle
Circle::Circle()
{
  C.X = 0;
  C.Y = 0;
  R = 0;
}

Circle::Circle(Point p, double radius)
{
  C.X = p.X;
  C.Y = p.Y;
  R = radius;
}

Circle::~Circle()
{
  C.X = 0;
  C.Y = 0;
  R = 0;
}

bool Circle::IsSelectedPoint(Point p)
{
  int dist = getDistance(p, C);
  if (dist <= R)
    return true;
  return false;
}

Shape *Circle::Clone()
{
  // Shape *c=new Circle;
  Circle *c = new Circle;

  c->C.X = C.X;
  c->C.Y = C.Y;
  c->R = R;

  return c;
}

void Circle::input()
{
  cout << "Input of Circle" << endl;
  cout << "Enter x-axis of the center: ";
  cin >> C.X;
  cout << "Enter y-axis of the center: ";
  cin >> C.Y;
  cout << "Enter radius: ";
  cin >> R;
}

void Circle::output()
{
  cout << "Circle ";
  cout << "has center (" << C.X << ", " << C.Y << "); ";
  cout << "radius " << R << endl;
}

double Circle::getPerimeter()
{
  return 2 * 3.14 * R;
}

double Circle::getArea()
{
  return R * R * 3.14;
}

int Circle::getType()
{
  return 1;
}

Circle &Circle::operator=(Circle &src)
{
  C.X = src.C.X;
  C.Y = src.C.Y;
  R = src.R;
  return *this;
}

// Rectangle
Rectangle::Rectangle()
{
  X.X = 0;
  X.Y = 0;
  W = H = 0;
}

Rectangle::Rectangle(Point p, double _W, double _H)
{
  X.X = p.X;
  X.Y = p.Y;
  W = _W;
  H = _H;
}

Rectangle::~Rectangle()
{
  X.X = 0;
  X.Y = 0;
  W = H = 0;
}

bool Rectangle::IsSelectedPoint(Point p)
{
  Point top_left;
  top_left.X = X.X - W / 2;
  top_left.Y = X.Y + H / 2;

  Point bottom_right;
  bottom_right.X = X.X + W / 2;
  bottom_right.Y = X.Y - H / 2;

  if (p.X >= top_left.X && p.X <= bottom_right.X && p.Y >= bottom_right.Y && p.Y <= top_left.Y)
    return true;
  return false;
}

Shape *Rectangle::Clone()
{
  Rectangle *r = new Rectangle;

  r->X.X = X.X;
  r->X.Y = X.Y;
  r->W = W;
  r->H = H;

  return r;
}

void Rectangle::input()
{
  cout << "Input of Rectangle" << endl;
  cout << "Enter x-axis of the center: ";
  cin >> X.X;
  cout << "Enter y-axis of the center: ";
  cin >> X.Y;
  cout << "Enter width: ";
  cin >> W;
  cout << "Enter heigh: ";
  cin >> H;
}

void Rectangle::output()
{
  cout << "Rectangle ";
  cout << "has center (" << X.X << ", " << X.Y << "); ";
  cout << "width " << W << ", heigh " << H << endl;
}

double Rectangle::getPerimeter()
{
  return 2 * (W + H);
}

double Rectangle::getArea()
{
  return W * H;
}

int Rectangle::getType()
{
  return 2;
}

Rectangle &Rectangle::operator=(Rectangle &src)
{
  X.X = src.X.X;
  X.Y = src.X.Y;
  W = src.W;
  H = src.H;
  return *this;
}

// declaration of DynamicArray class
DynamicArray::DynamicArray()
{
  pHead = NULL;
  n = 0;
}

int DynamicArray::size()
{
  return n;
}

Shape *DynamicArray::at(int pos)
{
  if (pos < n)
    return pHead[pos];
  return NULL;
}

void DynamicArray::push_back(Shape *value)
{
  if (!n)
    pHead = new Shape *[100];
  pHead[n++] = value;
}

void DynamicArray::clear()
{
  if (pHead)
    delete[] pHead;
}

DynamicArray::~DynamicArray()
{
  if (pHead)
    for (int i = 0; i < n; i++)
      delete pHead[i];
}

void DynamicArray::erase(int pos)
{
  if (pos < n && pos >= 0)
  {
    for (int i = pos; i < n - 1; i++)
      pHead[i] = pHead[i + 1];
    n--;
  }
}

void DynamicArray::insert(int pos, Shape *val)
{
  if (pos >= 0 && pos <= n)
  {
    for (int i = n; i > pos; i--)
      pHead[i] = pHead[i - 1];
    pHead[pos] = val;
    n++;
  }
}

int DynamicArray::begin()
{
  return 0;
}

// declaration of LinkedList class
LinkedList::LinkedList()
{
  pHead = NULL;
  n = 0;
}

int LinkedList::size()
{
  return n;
}

Shape *LinkedList::at(int index)
{
  Node *current = pHead;

  int count = 0;
  while (current != NULL)
  {
    if (count == index)
      return current->data;
    count++;
    current = current->pNext;
  }

  return NULL;
}

void LinkedList::push_back(Shape *new_data)
{
  Node *new_node = new Node;

  Node *last = pHead;

  new_node->data = new_data;

  new_node->pNext = NULL;

  if (pHead == NULL)
  {
    pHead = new_node;
    n++;
    return;
  }

  while (last->pNext != NULL)
    last = last->pNext;

  last->pNext = new_node;
  n++;
}

void LinkedList::clear()
{
  Node *current = pHead;
  Node *next = NULL;

  while (current != NULL)
  {
    next = current->pNext;
    delete current->data;
    delete current;
    current = next;
  }

  pHead = NULL;
}

LinkedList::~LinkedList()
{
  if (pHead != NULL)
    delete pHead;
  pHead = NULL;
  n = 0;
}

void LinkedList::erase(int position)
{
  if (position < 0 || position >= n)
    return;

  if (pHead == NULL)
    return;

  Node *current = pHead;
  if (position == 0)
  {
    pHead = current->pNext;
    delete current;
    n--;
    return;
  }

  int i = 0;
  while (i < position - 1)
  {
    current = current->pNext;
    i++;
  }

  Node *next = current->pNext->pNext;
  delete current->pNext;
  current->pNext = next;
  n--;
}

void LinkedList::insert(int pos, Shape *value)
{
  if (pos < 0 || pos > n)
    return;

  Node *new_node = new Node;
  new_node->data = value;
  new_node->pNext = NULL;

  if (pos == 0)
  {
    new_node->pNext = pHead;
    pHead = new_node;
    n++;
    return;
  }

  int i = 0;
  Node *current = pHead;
  while (i < pos - 1)
  {
    current = current->pNext;
    i++;
  }

  new_node->pNext = current->pNext;
  current->pNext = new_node;
  n++;
}

int LinkedList::begin()
{
  return 0;
}