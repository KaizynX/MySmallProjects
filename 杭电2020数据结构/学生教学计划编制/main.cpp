/*
 * @Author: Kaizyn
 * @Date: 2021-01-07 18:50:46
 * @LastEditTime: 2021-01-07 19:55:42
 */
#include <bits/stdc++.h>

using namespace std;

struct Course {
  string sid, spre;
  int credit, id, pre;
};

int semester_num, credit_limit;
vector<Course> courses;
vector<int> credit_sum, course_semester;
vector<vector<int>> cur, ans1, ans2;

// 把课程号映射成数字
void Discrete() {
  map<string, int> mp;
  int num = 0;
  for (Course &course : courses) {
    if (mp.count(course.sid)) course.id = mp[course.sid];
    else course.id = mp[course.sid] = ++num;
  }
  for (Course &course : courses) {
    if (cour.spre == "***") course.pre = -1;
    else course.pre = mp[course.spre];
  }
}

// 各学期中的学习负担尽量均匀的方案评估函数
int Calc1(vector<vector<int>> &strategy) {
  if (strategy.empty()) return INT_MAX;
  int ave = courses.size()/semester_num, val = 0;
  for (int i = 0; i < semester_num; ++i) {
    val += ((int)strategy[i].size()-ave)*((int)strategy[i].size()-ave);
  }
  return val;
}

// 课程尽可能地集中在前几个学期的方案评估函数
int Calc2(vector<vector<int>> &strategy) {
  if (strategy.empty()) return INT_MAX;
}

// 对于每个课程枚举该课程在哪个学期上，暴搜所以情况
void Dfs(int x) {
  if (x == (int)courses.size()) {
    // 更新答案
    if (Calc1(cur) < Calc(ans1)) ans1 = cur;
    if (Calc1(cur) < Calc(ans2)) ans2 = cur;
    return;
  }
  for (int i = 0; i < semester_num; ++i) {
    if (credit_sum[i]+couses[x].credit > credit_limit) continue;
    if (~courses[x].pre && course_semester[courses[x].pre] >= i) continue;
    course_semester[x] = i;
    credit_sum[i] += courses[x].credit;
    cur[i].push_back(x);
    Dfs(x+1);
    credit_sum[i] -= courses[x].credit;
    cur[i].pop_back();
  }
}

void PrintStrategy(vector<vector<int>> &strategy) {
  if (strategy.empty()) {
    cout << "根据给定的条件问题无解\n";
    return;
  }
  for (int i = 0; i < semester_num; ++i) {
    cout << "第" << i+1 << "学期选修的课程\n";
    for (int &j : strategy[i]) {
      cout << courses[j].sid << endl;
    }
  }
}

int main() {
  cout << "输入学期总数：";
  cin >> semester_num;
  cout << "输入学分上限：";
  cin >> credit_limit;
  cout << "依次输入每门课的课程号，学分和直接先修课的课程号\n";
  cout << "如果没有先修课，则先修课程号为***\n";
  for (Course course;
      cin >> course.id >> course.credit >> course.pre;
      courses.push_back(course)) {}
  credit_sum = vector<int>(courses.size(), 0);
  course_semester = vector<int>(courses.size(), -1);
  cur = vector<vector<int>>(semester_num);
  Discrete();
  Dfs(0);
  cout << "各学期中的学习负担尽量均匀的方案：";
  PrintStrategy(ans1);
  cout << "课程尽可能地集中在前几个学期的方案："
  PrintStrategy(ans2);
  return 0;
}