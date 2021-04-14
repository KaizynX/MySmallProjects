/*
 * @Author: Kaizyn
 * @Date: 2021-04-14 10:58:08
 * @LastEditTime: 2021-04-14 11:48:50
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double PI = 3.1416;

class Shape {
 public:
  friend istream& operator >>(istream &is, Shape &s) {
    return is >> s;
  }
  virtual double Area() {
    return Area();
  }
};

class Circle : public Shape { //（圆形）
 public:
  friend istream& operator >>(istream &is, Circle &c) {
    return is >> c.r;
  }
  virtual double Area() {
    return PI*r*r;
  }
 private:
  double r;
};

class Rectangle : public Shape { //（ 长方形）
 public:
  friend istream& operator >>(istream &is, Rectangle &r) {
    return is >> r.a >> r.b;
  }
  virtual double Area() {
    return a*b;
  }
 private:
  double a, b;
};

class Triangle : public Shape { //（三角形）
 public:
  friend istream& operator >>(istream &is, Triangle &t) {
    return is >> t.a >> t.b >> t.c;
  }
  virtual double Area() {
    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
  }
 private:
  double a, b, c;
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
  string str;
  vector<Shape*> vec;
  while (cin >> str) {
    Shape *cur;
    if (str == "circle") {
      cur = new Circle;
    } else if (str == "rectangle") {
      cur = new Rectangle;
    } else if (str == "triangle") {
      cur = new Triangle;
    }
    cin >> *cur;
    vec.emplace_back(cur);
  }
  printf("%.4f\n", TotalArea(vec));
  clear(vec);
  return 0;
}