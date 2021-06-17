/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 11:08:51
 * @LastEditTime: 2021-04-28 11:33:18
 */
#include <iostream>
using namespace std;
/*
请设计以下航行器、飞机、船、水上飞机等4个类。

CRAFT类为航行器类，是公共基类，提供航行器的基本特性。包括：

一个保护数据成员：speed(速度)。

三个公有成员函数：构造函数(初始化速度)、析构函数和Show函数(显示速度)。

PLANE类为飞机类，以公有方式继承CRAFT类，在航行器类的基础上增加飞机的特性。包括：

一个保护数据成员：width(翼展)。 三个公有成员函数：构造函数(初始化速度和翼展)、析构函数和Show函数(显示速度和翼展)。

SHIP类为船类，以公有方式继承CRAFT类，在航行器类的基础上增加船的特性。包括：

一个保护数据成员：depth(吃水深度)。 三个公有成员函数：构造函数(初始化速度和吃水深度)、析构函数和Show函数(显示速度和吃水深度)。

SEAPLANE类为水上飞机类，同时以公有方式继承PLANE类和SHIP类，兼具飞机和船的特性。包括：

三个公有成员函数：构造函数(初始化速度、翼展、吃水深度)、析构函数和Show函数(显示速度、翼展和吃水深度)。
*/
/* 你提交的代码将被嵌在这里 */
#include <bits/stdc++.h>

class CRAFT {
 public:
  CRAFT(double s) : speed(s) {
    printf("创建航行器(速度: %.1f)\n", s);
  }
  virtual ~CRAFT() {
    printf("销毁航行器(速度: %.1f)\n", speed);
  }
  virtual void Show() {
    printf("航行(速度: %.1f)\n", speed);
  }
 protected:
  double speed;
};

class PLANE : virtual public CRAFT {
 public:
  PLANE(double s, double w) : CRAFT(s), width(w) {
    printf("创建飞机(翼展: %.1f)\n", width);
  }
  ~PLANE() {
    printf("销毁飞机(翼展: %.1f)\n", width);
  }
  void Show() {
    printf("航行(速度: %.1f, 翼展: %.1f)\n", speed, width);
  }
 protected:
  double width;
};

class SHIP : virtual public CRAFT {
 public:
  SHIP(double s, double d) : CRAFT(s), depth(d) {
    printf("创建船(吃水: %.1f)\n", depth);
  }
  ~SHIP() {
    printf("销毁船(吃水: %.1f)\n", depth);
  }
  void Show() {
    printf("航行(速度: %.1f, 吃水: %.1f)\n", speed, depth);
  }
 protected:
  double depth;
};

class SEAPLANE : public PLANE, public SHIP {
 public:
  SEAPLANE(double s, double w, double d) : CRAFT(s), PLANE(s, w), SHIP(s, d) {
    puts("创建水上飞机");
  }
  ~SEAPLANE() {
    puts("销毁水上飞机");
  }
  void Show() {
    printf("航行(速度: %.1f, 翼展: %.1f, 吃水: %.1f)\n", speed, width, depth);
  }
};

int main()
{
    CRAFT *p;
p = new PLANE(613.5, 45.3);
p->Show();
delete p;
}