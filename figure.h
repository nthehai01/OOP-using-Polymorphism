#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

// Cau truc Diem
struct Point
{
  double X;
  double Y;
};

double getDistance(Point, Point);

// Lop doi tuong hinh ve tong quat 'Shape'
class Shape
{
public:
  // Constructor/Destructor
  // Shape() {  };
  // ~Shape();
  // process methods
  virtual Shape *Clone() = 0;
  /* Se cai dat lai trong tung lop dan xuat */
  virtual bool IsSelectedPoint(Point p) = 0;
  /* Sẽ cài đặt lại trong từng lớp con */
  virtual void input() = 0;
  virtual void output() = 0;
  virtual double getPerimeter() { return 0; };
  virtual double getArea() { return 0; };
  virtual int getType() { return 0; };
  // others
};

// Lớp Circle
class Circle : public Shape
{
private:
  Point C;
  double R;

public:
  // Constructor/Destructor
  Circle();
  Circle(Point, double);
  ~Circle();
  // process methods
  bool IsSelectedPoint(Point);
  Shape *Clone();
  void input();
  void output();
  double getPerimeter();
  double getArea();
  int getType();
  Circle &operator=(Circle &);
};

// Lớp hình chu nhat
class Rectangle : public Shape
{
private:
  // X is the center of the rectangle
  Point X;
  double W, H;

public:
  //Constructor/Destructor
  Rectangle();
  Rectangle(Point, double, double);
  ~Rectangle();
  bool IsSelectedPoint(Point);
  Shape *Clone();
  void input();
  void output();
  double getPerimeter();
  double getArea();
  int getType();
  Rectangle &operator=(Rectangle &);
  // others
};

// Lớp ComplexShape
template <typename T>
class ComplexShape : public Shape
{
protected:
  // Các hình vẽ thành phần: Circle, rectangle, ...
  T Children;

public:
  // Constructor/Destructor
  ComplexShape() {}

  ComplexShape(T ds)
  {
    for (int i = 0; i < ds.size(); i++)
      Children.at(i) = ds.at(i);
  }

  ComplexShape(const ComplexShape<T> &src)
  {
    for (int i = 0; i < src.Children.size(); i++)
      Children.at(i) = src.Children.at(i);
  }

  bool IsSelectedPoint(Point p)
  {
    for (int i = 0; i < Children.size(); i++)
      if (Children.at(i)->IsSelectedPoint(p))
        return true;
    return false;
  }

  Shape *Clone()
  {
    ComplexShape<T> *res = new ComplexShape<T>;
    for (int i = 0; i < Children.size(); i++)
      res->Children.push_back(Children.at(i));
    return res;
  }
  /* Se cai dat lai trong tung lop dan xuat */
  /* Sẽ cài đặt lại trong từng lớp con */
  void input()
  {
    cout << "Input of Complex Shape" << endl;

    int type = -1;
    while (type)
    {
      cout << "Chose Type of Shape (1.Circle, 2.Rectangle, 0.Break): ";
      cin >> type;

      Shape *temp = NULL;
      switch (type)
      {
      case 1:
        temp = new Circle;
        break;
      case 2:
        temp = new Rectangle;
        break;
      default:
        break;
      }

      if (temp)
      {
        temp->input();
        Children.push_back(temp);
      }
    }
  }

  void output()
  {
    cout << "Complex Shape: " << endl;
    for (int i = 0; i < Children.size(); i++)
      Children.at(i)->output();
  }

  ~ComplexShape()
  {
    for (int i = 0; i < Children.size(); i++)
      delete Children.at(i);
    Children.clear();
  }

  void computeAreaByShape()
  {
    double sumCircleArea = 0;
    double sumRectangleArea = 0;

    for (int i = 0; i < Children.size(); i++)
    {
      int type = Children.at(i)->getType();
      switch (type)
      {
      case 1:
        sumCircleArea += Children.at(i)->getArea();
        break;
      case 2:
        sumRectangleArea += Children.at(i)->getArea();
      default:
        break;
      }
    }

    cout << "Total Circle Area: " << sumCircleArea << endl;
    cout << "Total Rectangle Area: " << sumRectangleArea << endl;
  }

  void sortByPerimeter(bool isDecreasing = false)
  {
    int i, j;
    Shape *key;
    for (i = 1; i < Children.size(); i++)
    {
      key = Children.at(i);
      j = i - 1;

      while (j >= 0 && pow(-1, isDecreasing) * (Children.at(j)->getPerimeter() - key->getPerimeter()) > 0)
      {
        Children.erase(Children.begin() + j + 1);
        Children.insert(Children.begin() + j + 1, Children.at(j));
        j = j - 1;
      }

      Children.erase(Children.begin() + j + 1);
      Children.insert(Children.begin() + j + 1, key);
    }
  }
  //others
};

template <typename T>
class List
{
protected:
  T *pHead;
  int n;

public:
  virtual int size() = 0;
  virtual Shape *at(int) = 0;
  virtual void push_back(Shape *) = 0;
  virtual void clear() = 0;
  virtual int begin() = 0;
  virtual void erase(int) = 0;
  virtual void insert(int, Shape *) = 0;
};

class DynamicArray : List<Shape *>
{
public:
  DynamicArray();
  int size();
  Shape *at(int);
  void push_back(Shape *);
  void clear();
  ~DynamicArray();
  void erase(int);
  void insert(int, Shape *);
  int begin();
};

struct Node
{
  Shape *data;
  Node *pNext;
};

class LinkedList : List<Node>
{
public:
  LinkedList();
  int size();
  Shape *at(int);
  void push_back(Shape *);
  void clear();
  ~LinkedList();
  void erase(int);
  void insert(int, Shape *);
  int begin();
};