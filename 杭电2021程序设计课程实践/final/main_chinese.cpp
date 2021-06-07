/*
 * @Author: Kaizyn
 * @Date: 2021-06-04 14:16:33
 * @LastEditTime: 2021-06-04 22:27:04
 */
#include <tchar.h> 
#include <bits/stdc++.h>
// #define DEBUG
using namespace std;

/*
class  {
 public:
  friend istream& operator >>(istream &is, ) {
    input(is, );
    return is;
  }
  friend ostream& operator <<(ostream &os, const ) {
    return os << ;
  }
  bool check() {
  }
 private:
};
*/

string buf; // 全局字符缓冲区

// 去除首尾空字符
string trim(string str) {
  str.erase(0, str.find_first_not_of(_T(" \n\r\t")));
  str.erase(str.find_last_not_of(_T(" \n\r\t")) + 1);
  return str;
}

// 输入函数,如果输入不符合要求就一直输入直到正确为止
template <class T>
void input(istream &is, T &obj) {
  for (bool ok = false; !ok; ) {
    getline(is, buf);
    try {
      ok = obj.check();
    } catch (const char* msg) {
      cerr << "错误:" << msg << "请重新输入:" << endl;
    }
  }
}

class Name {
 public:
  friend istream& operator >>(istream &is, Name &n) {
    cout << endl;
    input(is, n);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Name &n) {
    return os << n.name;
  }
  // 检测姓名是否合法(非空且大于一个字符)
  bool check() {
    name = trim(buf);
    if (name.empty()) return throw "输入不能为空", false;
    if (name.size() <= 1u) return throw "姓名太短", false;
    return true;
  }
 private:
  string name;
};

class Gender {
 public:
  friend istream& operator >>(istream &is, Gender &g) {
    cout << "(男|女|第三性)" << endl;
    input(is, g);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Gender &g) {
    if (g.gender == 0) os << "男";
    if (g.gender == 1) os << "女";
    if (g.gender == -1) os << "第三性";
    return os;
  }
  bool check() {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf == "男") return gender = 0, true;
    if (buf == "女") return gender = 1, true;
    if (buf == "第三性") return gender = 2, true;
    throw "输入了奇奇怪怪的性别"; return false;
  }
 private:
  int gender; // 0 男 1 女 2 第三性别
};

class IdNumber {
 public:
  friend istream& operator >>(istream &is, IdNumber &in) {
    cout << endl;
    input(is, in);
    return is;
  }
  friend ostream& operator <<(ostream &os, const IdNumber &in) {
    return os << in.id;
  }
  bool check() {
    id = trim(buf);
    if (id.empty()) return throw "输入不能为空", false;
    if (id.size() != 15u || id.size() != 18u) return throw "位数不对", false;
    if (regex_match(id, regex("/^[1-9]\\d{5}\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}$/")) ||
        regex_match(id, regex("/^[1-9]\\d{5}(18|19|([23]\\d))\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$/")))
      return true;
    throw "输入错误"; return false;
  }
 private:
  string id;
};

class PhoneNumber {
 public:
  friend istream& operator >>(istream &is, PhoneNumber &pn) {
    cout << endl;
    input(is, pn);
    return is;
  }
  friend ostream& operator <<(ostream &os, const PhoneNumber &pn) {
    return os << pn.number;
  }
  bool check() {
    number = trim(buf);
    if (number.empty()) return throw "输入不能为空", false;
    if (number.size() != 11u) return throw "位数不对", false;
    if (regex_match(number, regex("/^(13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])\\d{8}$/")))
      return true;
    throw "输入错误"; return false;
  }
 private:
  string number;
};

class NumberPlate {
 public:
  friend istream& operator >>(istream &is, NumberPlate &np) {
    cout << endl;
    input(is, np);
    return is;
  }
  friend ostream& operator <<(ostream &os, const NumberPlate &np) {
    return os << np.number;
  }
  bool check() {
    number = trim(buf);
    if (number.empty()) return throw "输入不能为空", false;
    if (regex_match(number, regex("^[京津沪渝冀豫云辽黑湘皖鲁新苏浙赣鄂桂甘晋蒙陕吉闽贵粤青藏川宁琼使领A-Z]{1}[A-Z]{1}[A-Z0-9]{4}[A-Z0-9挂学警港澳]{1}$")))
      return true;
    throw "输入错误"; return false;
  }
 private:
  string number;
};

class HealthCode {
 public:
  friend istream& operator >>(istream &is, HealthCode &hc) {
    cout << "(绿|黄|红)" << endl;
    input(is, hc);
    return is;
  }
  friend ostream& operator <<(ostream &os, const HealthCode &hc) {
    if (hc.color == 0) cout << "绿";
    if (hc.color == 1) cout << "黄";
    if (hc.color == 2) cout << "红";
    return os << "码";
  }
  bool check() {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf == "绿") return color = 0, true;
    if (buf == "黄") return color = 1, true;
    if (buf == "红") return color = 2, true;
    throw "输入错误"; return false;
  }
 private:
  int color; // 0 绿 1 黄 2 红
};

class String {
 public:
  friend istream& operator >>(istream &is, String &s) {
    cout << endl;
    input(is, s);
    return is;
  }
  friend ostream& operator <<(ostream &os, const String &s) {
    return os << s.str;
  }
  bool check() {
    str = trim(buf);
    if (str.empty()) return throw "输入不能为空", false;
    return true;
  }
 private:
  string str;
};

class Bool {
 public:
  friend istream& operator >>(istream &is, Bool &b) {
    cout << "(是/否)" << endl;
    input(is, b);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Bool &b) {
    return os << (b.tag ? "是" : "否");
  }
  bool check() {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf == "是") return tag = true, true;
    if (buf == "否") return tag = false, true;
    throw "输入错误"; return false;
  }
 private:
  bool tag;
};

class Time {
 public:
  friend istream& operator >>(istream &is, Time &t) {
    cout << "格式:hh:mm:ss 例如:12:34:56 " << endl;
    input(is, t);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Time &t) {
    return os << t.hour << ':' << t.minute << ':' << t.second;
  }
  friend bool operator <(const Time &lhs, const Time &rhs) {
    return vector<int>({lhs.hour, lhs.minute, lhs.second})
        <  vector<int>({rhs.hour, rhs.minute, rhs.second});
  }
  friend bool operator ==(const Time &lhs, const Time &rhs) {
    return lhs.hour == rhs.hour
        && lhs.minute == rhs.minute
        && lhs.second == rhs.second;
  }
  bool check() {
    static char ch;
    static stringstream ss;
    ss.clear();
    ss << buf;
    if (!(ss >> hour >> ch >> minute >> ch >> second))
      return throw "输入格式错误", false;
    if (hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59)
      return throw "输入时间错误", false;
    return true;
  }
 private:
  int hour, minute, second; // 时分秒
};

// 人员登记基本信息
class BasicInformation {
 public:
  friend istream& operator >>(istream &is, BasicInformation &bi) {
    cout << "请输入姓名:"; is >> bi.name;
    cout << "请输入性别:"; is >> bi.gender;
    cout << "请输入联系电话:"; is >> bi.phone_number;
    cout << "请输入身份证号:"; is >> bi.id_number;
    cout << "请输入工作单位:"; is >> bi.work_place;
    cout << "请输入车牌号:"; is >> bi.number_plate;
    cout << "请输入进校事由:"; is >> bi.reason;
    cout << "请输入担保人:"; is >> bi.guarantor;
    cout << "请输入担保人电话:"; is >> bi.guarantor_phone_number;
    cout << "请输入健康码:"; is >> bi.health_code;
    cout << "请输入14天内是否去过疫区:"; is >> bi.is_epidemic_area;
    cout << "请输入是否有咳嗽发热等症状:"; is >> bi.is_unhealthy_symptoms;
    cout << "请输入申请进入时间:"; is >> bi.enter_time_application;
    cout << "请输入申请离开时间:"; is >> bi.exit_time_application;
    cout << "请输入实际进入时间:"; is >> bi.enter_time;
    cout << "请输入实际离开时间:"; is >> bi.exit_time;
    return is;
  }
  friend ostream& operator >>(ostream &os, const BasicInformation &bi) {
    os << "姓名:" << bi.name << endl;
    os << "性别:" << bi.gender << endl;
    os << "联系电话:" << bi.phone_number;
    os << "身份证号:" << bi.id_number;
    os << "工作单位:" << bi.work_place;
    os << "车牌号:" << bi.number_plate;
    os << "进校事由:" << bi.reason;
    os << "担保人:" << bi.guarantor;
    os << "担保人电话:" << bi.guarantor_phone_number;
    os << "健康码:" << bi.health_code;
    os << "14天内是否去过疫区:" << bi.is_epidemic_area;
    os << "是否有咳嗽发热等症状:" << bi.is_unhealthy_symptoms;
    os << "申请进入时间:" << bi.enter_time_application;
    os << "申请离开时间:" << bi.exit_time_application;
    os << "实际进入时间:" << bi.enter_time;
    os << "实际离开时间:" << bi.exit_time;
    return os;
  }
 private:
  Name name; // 姓名
  Gender gender; // 性别
  PhoneNumber phone_number; // 联系电话
  IdNumber id_number; // 身份证号
  String work_place; // 单位信息
  NumberPlate number_plate; // 车牌号
  String reason; // 进校事由
  Name guarantor; // 担保人
  PhoneNumber guarantor_phone_number; // 担保人电话
  HealthCode health_code; // 健康码
  Bool is_epidemic_area;  // 14天内是否去过疫区
  Bool is_unhealthy_symptoms; // 是否有咳嗽发热等症状
  Time enter_time_application; // 申请进入时间
  Time exit_time_application; // 申请离开时间
  Time enter_time; // 实际进入时间
  Time exit_time; // 实际离开时间
};

class HolySystem {
 public:
  void insert(const BasicInformation &bi) {
    database.emplace_back(bi);
  }
  vector<BasicInformation> query() {
    vector<BasicInformation> vec;
    return vec;
  }
 private:
  vector<BasicInformation> database;
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  HolySystem holy_system;
  BasicInformation basic_information;
  while (cin >> basic_information) {
    holy_system.insert(basic_information);
  }
  return 0;
}