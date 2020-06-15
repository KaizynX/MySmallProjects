/*
 * 写在前面，中文字符未知处理
 */ 
#include <bits/stdc++.h>

using namespace std;

/**********************************
 * file_name        文件存储位置
 * kind_name[0][i]  ai类别代码对应的类别名称
 * kind_name[1][i]  bi类别代码对应的类别名称
 * day[i]           对应i月份的天数
 **********************************/
const string file_name = "data.txt";
const string kind_name[2][4] = {
  {"", "生活费", "奖学金", "稿费"},
  {"", "学习用品", "生活用品", "游戏"}
};
const int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Time {
  int y, m, d;
  Time(const int &_y = 0, const int &_m = 0, const int &_d = 0) : y(_y), m(_m), d(_d) {}
  // 检测日期的合法性
  bool check() {
    bool flag = true;
    if (m < 1 || m > 12 || d < 1) flag = 0;
    else {
      if (m == 2) {
        if (d > day[2]+((y%4 == 0 && y%100 != 0) || (y%400 == 0))) flag = 0;
      } else {
        if (d > day[m]) flag = 0;
      }
    }
    if (!flag) cerr << "傻逼，日期输错了" << endl;
    return flag;
  }
  void chinese_print() {
    if (y != 0) cout << y << "年";
    if (m != 0) cout << m << "月";
    if (d != 0) cout << d << "日";
  }
  friend bool operator ==(const Time &t1, const Time &t2) {
    return (t1.y == t2.y || t1.y == 0 || t2.y == 0) &&
        (t1.m == t2.m || t1.m == 0 || t2.m == 0) &&
        (t1.d == t2.d || t1.d == 0 || t2.d == 0);
  }
  friend bool operator !=(const Time &t1, const Time &t2) {
    return !(t1 == t2);
  }
  // 重载时间的格式化输入输出
  friend istream& operator >>(stringstream &ss, Time &time) {
    static char ch;
    return ss >> time.y >> ch >> time.m >> ch >> time.d;
  }
  friend istream& operator >>(istream &is, Time &time) {
    static stringstream ss;
    static string str;
    is >> str;
    ss.clear();
    ss << str;
    ss >> time;
    return is;
  }
  friend ostream& operator <<(ostream &os, Time &time) {
    return os << time.y << "-" << time.m << "-" << time.d;
  }
};

/*
ostream& operator <<(ostream &os, Time &time) {
  return os << time.y << "-" << time.m << "-" << time.d;
}
*/

struct Record {
  char in_or_out;
  int kind;
  Time time;
  double money;
  string comment;
  friend ostream& operator <<(ostream &os, Record &rec) {
    return os << kind_name[rec.in_or_out-'a'][rec.kind]
        << " " << (rec.in_or_out == 'a' ? "收入" : "支出")
        << " " << rec.time
        << " " << fixed << setprecision(2) << rec.money // 保留2位小数
        << " " << rec.comment;
  }
};

vector<Record> records;

/**********************************
 * add_data     添加一条记录,返回记录是否合法
 * file_write   将记录写入文件
 * file_read    从文件中读入记录
 * input        输入收支明细
 * output       查询统计
 **********************************/

bool add_data(const string&);
void file_write(const string&);
void file_read();
void input();
void output();

int main() {
  file_read();
  input();
  output();
  return 0;
}

bool add_data(const string &str) {
  static stringstream ss;
  static Record rec;
  ss.clear();
  ss << str;
  if (!(ss >> rec.in_or_out)) return false;
  if (!(ss >> rec.kind)) return false;
  if (!(ss >> rec.time) || !rec.time.check()) return false;
  if (!(ss >> rec.money)) return false;
  // 备注可以为空吧?不会真的有人天天写备注吧不会吧
  getline(ss, rec.comment);
  // 如果不允许备注为空启动下面这条语句
  // if (!(getline(ss, rec.comment))) return false;
  records.push_back(rec);
  return true;
}

void file_write(const string &str) {
  static ofstream f;
  // 以追加模式打开
  f.open(file_name, ios::app);
  f << str << endl;
  f.close();
}

void file_read() {
  static ifstream f;
  static string str;
  // 以只读模式打开文件
  f.open(file_name, ios::in);
  while (getline(f, str)) {
    add_data(str);
  }
  f.close();
}

void input() {
  static string str;
  while (true) {
    cout << "输入收支明细：" << flush;
    // 输入为空行，输入结束
    if (!getline(cin, str)) return;
    if (str.empty()) break;
    // 输入出错或格式错误,否则写入文件
    if (cin.fail() || add_data(str) == 0) {
      cerr << "智障，你输入的数据有误，cnmlgjb!" << endl;
    } else {
      file_write(str);
    }
  }
}

void output() {
  static string str;
  static Time time;
  static double sum_money[2][4], sum_sum_money[2];
  while (true) {
    time = Time();
    cout << "请输入对收支类别数据进行汇总的月份：" << flush;
    cin >> time;
    cout << time << endl;
    // 遍历全部数据统计金额
    memset(sum_money, 0, sizeof sum_money);
    memset(sum_sum_money, 0, sizeof sum_sum_money);
    for (int i = 0; i < (int)records.size(); ++i) {
      Record rec = records[i];
      if (rec.time == time) {
        sum_money[rec.in_or_out-'a'][rec.kind] += rec.money;
        sum_sum_money[rec.in_or_out-'a'] += rec.money;
      }
    }
    // 输出
    time.chinese_print();
    cout << "收支类别数据的汇总" << endl
        << "收入/支出 明细类别 金额" << endl;
    for (int i = 0; i < 2; ++i) {
      for (int j = 1; j <= 3; ++j) {
        cout << (i == 0 ? "收入 " : "支出 ");
        cout << kind_name[i][j] << " " << sum_money[i][j] << endl;
      }
    }
    time.chinese_print();
    cout << "的总收入为：" << sum_sum_money[0]
        << ", 总支出为：" << sum_sum_money[1] << endl;
    
    cout << "是否输出该时间段的各笔明细（y 为输出，其他为不输出）：" << flush;
    // 使用 string 防止输入多个字符
    cin >> str;
    if (str[0] != 'y') continue;
    time.chinese_print();
    cout << "收支类别数据的明细" << endl
        << "类别 收入/支出 发生日期 金额 备注" << endl;
    for (int i = 0; i < (int)records.size(); ++i) {
      Record rec = records[i];
      if (rec.time == time) cout << rec << endl;
    }
  }
}