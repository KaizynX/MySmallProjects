/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 10:20:32
 * @LastEditTime: 2021-04-28 10:37:26
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

#define double float

const double PI = 3.14159;

class Shape {
 public:
  virtual void read() {
  }
  virtual double Area() {
    return 0;
  }
};

class Circle : public Shape { //（圆形）
 public:
  virtual void read() {
    cin >> r;
  }
  virtual double Area() {
    return PI*r*r;
  }
 private:
  double r;
};

class Square : public Shape { //（正方形）
 public:
  virtual void read() {
    cin >> a;
  }
  virtual double Area() {
    return a*a;
  }
 private:
  double a;
};

class Rectangle : public Shape { //（ 长方形）
 public:
  virtual void read() {
    cin >> a >> b;
  }
  virtual double Area() {
    return a*b;
  }
 private:
  double a, b;
};

class Trapezoid : public Shape { // （梯形）
 public:
  virtual void read() {
    cin >> a >> b >> h;
  }
  virtual double Area() {
    return (a+b)/2*h;
  }
 private:
  double a, b, h;
};

class Triangle : public Shape { //（三角形）
 public:
  virtual void read() {
    cin >> a >> h;
  }
  virtual double Area() {
    return a*h/2;
  }
 private:
  double a, h;
};

double TotalArea(vector<Shape*> &vec) {
  double sum = 0;
  for (Shape *s : vec) {
    sum += s->Area();
  }
  return sum;
}

void clear(vector<Shape*> &vec) {
  while (vec.size()) {
    delete vec.back();
    vec.pop_back();
  }
}

signed main() {
// 输入在一行中，给出9个大于0的数，用空格分隔，
// 分别代表圆的半径，正方形的边长，矩形的宽和高，梯形的上底、下底和高，三角形的底和高。
  vector<Shape*> vec{new Circle, new Square, new Rectangle, new Trapezoid, new Triangle};
  for (Shape* s : vec) s->read();
  printf("%.3f\n", TotalArea(vec));
  clear(vec);
  return 0;
}