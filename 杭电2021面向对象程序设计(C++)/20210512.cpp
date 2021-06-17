/*
 * @Author: Kaizyn
 * @Date: 2021-05-12 10:29:16
 * @LastEditTime: 2021-05-12 13:05:25
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

class CPoint {
 public:
  CPoint(int x, int y) : x(x), y(y) {}
  int x, y;
};

class CShape {
 public:
  virtual ~CShape() {}
  virtual bool Hitin(const CPoint &) = 0;
};

class CRectangle : public CShape {
 public:
  CRectangle(CPoint pos, int x, int y)
      : m_pos(pos), m_iWidth(x), m_iHeight(y) {}
  bool Hitin(const CPoint &pos) {
    return pos.x >= m_pos.x && pos.x <= m_pos.x+m_iWidth
        && pos.y >= m_pos.y && pos.y <= m_pos.y+m_iHeight;
  }
 private:
  CPoint m_pos;
  int m_iWidth, m_iHeight;
};

class CCircle : public CShape {
 public:
  CCircle(CPoint center, double dRadius) 
      : m_center(center), m_dRadius(dRadius) {}
  bool Hitin(const CPoint &pos) {
    return sqrt((pos.x-m_center.x)*(pos.x-m_center.x)
        +(pos.y-m_center.y)*(pos.y-m_center.y)) <= m_dRadius;
  }
 private:
  CPoint m_center;
  double m_dRadius;
};

class CUIControl {
 public:
  bool HitTest(CPoint pos) {
    return m_pShape->Hitin(pos);
  }
  void SetShape(CShape *pShape) {
    m_pShape = pShape;
  }
  virtual void click() {}
  ~CUIControl() {}
 private:
  CShape *m_pShape;
};

class CButton : public CUIControl {
 public:
  CButton(string strName) : m_strName(strName) {}
  void click() {
    cout << "button-" << m_strName << " Clicked\n";
  }
 private:
  string m_strName;
};

class CMenu : public CUIControl {
 public:
  CMenu(string strName) : m_strName(strName) {}
  void click() {
    cout << "menu-" << m_strName << " Clicked\n";
  }
 private:
  string m_strName;
};

signed main() {
  int n;
  cin >> n;
  vector<CUIControl*> vec(n, nullptr);
  for (int i = 0; i < n; ++i) {
    static string str_type, str_title, str_shape;
    static int x, y, w, h;
    static double r;
    static CShape *shape;
    cin >> str_type >> str_title >> str_shape >> x >> y;
    if (str_type == "menu") {
      vec[i] = new CMenu(str_title);
    } else {
      vec[i] = new CButton(str_title);
    }
    if (str_shape == "rectangle") {
      cin >> w >> h;
      shape = new CRectangle(CPoint(x, y), w, h);
    } else {
      cin >> r;
      shape = new CCircle(CPoint(x, y), r);
    }
    vec[i]->SetShape(shape);
  }
  for (string _; cin >> _; ) {
    assert(_ == "click");
    static int x, y, flag;
    cin >> x >> y;
    flag = 0;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
      if ((**it).HitTest(CPoint(x, y))) {
        flag = 1;
        (**it).click();
        break;
      }
    }
    if (!flag) cout << "none hit\n";
  }
  return 0;
}
/*
5 

menu File rectangle  1 1  3 2

menu Edit rectangle  5 1  3 2

menu View   circle     9 1  1.5

button Build    circle    1   6  2.5

button Run     rectangle  7 6 4 3    

click  2 2

click  8 2

click 8 8

click  1 5

click  9 5
*/