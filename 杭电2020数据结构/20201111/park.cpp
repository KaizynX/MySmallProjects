/*
 * @Author: Kaizyn
 * @Date: 2020-11-11 19:00:41
 * @LastEditTime: 2020-11-12 15:46:46
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Stack {
  T *elem; // 顺序存储
  int cnt, cap; // cnt 当前数量, cap 停车场大小
  // 初始话,传入停车场大小
  void init(int n) {
    cap = n;
    elem = new T[n];
    cnt = 0;
  }
  bool empty() {
    return !cnt;
  }
  int size() {
    return cnt;
  }
  int capacity() {
    return cap;
  }
  // 插入栈顶元素
  bool push(T x) {
    if (cnt >= cap) return false;
    return elem[cnt++] = x, true;
  }
  // 删除栈顶元素
  T pop() {
    if (!cnt) return T();
    return elem[--cnt];
  }
  // 获取栈顶元素
  T top() {
    if (!cnt) return T();
    return elem[cnt-1];
  }
  // 删除任一元素
  int erase(T x) {
    Stack<T> tmp;
    int time = -1;
    tmp.init(cap);
    while (cnt && top() != x) {
      tmp.push(pop());
    }
    if (cnt) time = pop().time;
    while (tmp.size()) push(tmp.pop());
    return time;
  }
};

template <typename T>
struct Queue {
  // 链表结构存储
  struct Node {
    T elem;
    Node *pre, *nex;
  };
  int cnt; // 队列元素数量
  Node *head, *tail;
  // 初始化
  void init() {
    cnt = 0;
    head = tail = new Node();
    head->nex = tail;
    tail->pre = head;
  }
  bool empty() {
    return !cnt;
  }
  int size() {
    return cnt;
  }
  // 在队尾插入元素
  void push_back(T x) {
    ++cnt;
    tail->nex = new Node();
    tail->nex->pre = tail;
    tail->elem = x;
    tail = tail->nex;
  }
  // 在队首插入元素
  void push_front(T x) {
    ++cnt;
    head->pre = new Node();
    head->pre->nex = head;
    head = head->pre;
    head->elem = x;
  }
  // 在队首删除元素
  T pop_front() {
    --cnt;
    T res = head->elem;
    head = head->nex;
    delete head->pre;
    head->pre = nullptr;
    return res;
  }
  // 在队尾删除元素
  T pop_back() {
    --cnt;
    T res = tail->elem;
    tail = tail->pre;
    delete tail->nex;
    tail->nex = nullptr;
    return res;
  }
  // 获取队首元素
  T front() {
    return head->elem;
  }
  // 获取队尾元素
  T back() {
    return tail->pre->elem;
  }
  // 删除任一元素
  bool erase(T x) {
    Queue<T> tmp;
    int flag = 0;
    tmp.init();
    while (cnt && back() != x) {
      tmp.push_back(pop_back());
    }
    if (cnt) flag = 1, pop_back();
    while (tmp.size()) {
      push_back(tmp.pop_back());
    }
    return flag;
  }
};

struct Car {
  string id; // 车牌信息
  int time; // 时间信息
  bool operator ==(Car &c) const {
    return c.id == id;
  }
  bool operator !=(Car &c) const {
    return c.id != id;
  }
};

Stack<Car> stk;
Queue<Car> que;

// 汽车到达，判断进入停车场还是便道
void CarArrival(Car car) {
  if (stk.size() < stk.cap) {
    stk.push(car);
    cout << car.id << "进入停车场" << endl;
  } else {
    que.push_back(car);
    cout << car.id << "进入便道" << endl;
  }
}

// 汽车离去
void CarDeparture(Car car) {
  int last = stk.erase(car);
  // 返回-1表示汽车在便道
  if (last == -1) {
    if (que.erase(car)) {
      cout << car.id << "离开便道" << endl;
    } else {
      cout << car.id << "不存在" << endl;
    }
  } else {
    cout << car.id << "离开停车场,停留时间为" << car.time-last << endl;
    // 停车场有车离去，便道的车进入停车场
    if (que.size()) {
      cout << que.front().id << "由便道进入停车场" << endl;
      stk.push(Car{que.pop_front().id, car.time});
    }
  }
}

int main() {
  int n, t;
  string id;
  char op;

  cout << "输入停车场车位：";
  cin >> n;
  stk.init(n);
  que.init();
  while (true) {
    cin >> op >> id >> t;
    if (op == 'A') {
      CarArrival(Car{id, t});
    } else if (op == 'D') {
      CarDeparture(Car{id, t});
    } else {
      break;
    }
  }
  return 0;
}