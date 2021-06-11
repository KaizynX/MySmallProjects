/*
 * @Author: Kaizyn
 * @Date: 2021-06-04 14:16:33
 * @LastEditTime: 2021-06-10 14:48:48
 */
#ifndef BITS
#define BITS
#include <bits/stdc++.h>
using namespace std;
#endif

#include <tchar.h>

string buf; // 全局字符缓冲区

// 去除首尾空字符
string trim(string str)
{
  str.erase(0, str.find_first_not_of(_T(" \n\r\t")));
  str.erase(str.find_last_not_of(_T(" \n\r\t")) + 1);
  return str;
}

// 输入函数,如果输入不符合要求就一直输入直到正确为止
template <class T>
void input(istream &is, T &obj)
{
  for (bool ok = false; !ok; )
  {
    getline(is, buf);
    try
    {
      ok = obj.check();
    }
    catch (const char* msg)
    {
      cerr << "错误:" << msg << "请重新输入:" << endl;
    }
  }
}

class Gender
{
 public:
  friend istream& operator >>(istream &is, Gender &g)
  {
    cout << "男|女|第三性别 格式:(male|female|third)" << endl;
    input(is, g);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Gender &g)
  {
    if (g.gender == 0) os << "男";
    if (g.gender == 1) os << "女";
    if (g.gender == 2) os << "第三性";
    return os;
  }
  friend bool operator ==(const Gender &lhs, const Gender &rhs)
  {
      return lhs.gender == rhs.gender;
  }
  bool check()
  {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf == "male") return gender = 0, true;
    if (buf == "female") return gender = 1, true;
    if (buf == "third") return gender = 2, true;
    throw "输入了奇奇怪怪的性别";
    return false;
  }
 private:
  int gender; // 0 男 1 女 2 第三性别
};

class IdNumber
{
 public:
  friend istream& operator >>(istream &is, IdNumber &in)
  {
    cout << endl;
    input(is, in);
    return is;
  }
  friend ostream& operator <<(ostream &os, const IdNumber &in)
  {
    return os << in.id;
  }
  friend bool operator ==(const IdNumber &lhs, const IdNumber &rhs)
  {
      return lhs.id == rhs.id;
  }
  bool check()
  {
    id = trim(buf);
    if (id.empty()) return throw "输入不能为空", false;
    if (id.size() != 15u && id.size() != 18u) return throw "位数不对", false;
    if (regex_match(id, regex("^[1-9]\\d{5}\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}$")) ||
        regex_match(id, regex("^[1-9]\\d{5}(18|19|([23]\\d))\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$")))
      return true;
    throw "输入错误";
    return false;
  }
 private:
  string id;
};

class PhoneNumber
{
 public:
  friend istream& operator >>(istream &is, PhoneNumber &pn)
  {
    cout << endl;
    input(is, pn);
    return is;
  }
  friend ostream& operator <<(ostream &os, const PhoneNumber &pn)
  {
    return os << pn.number;
  }
  friend bool operator ==(const PhoneNumber &lhs, const PhoneNumber &rhs)
  {
      return lhs.number == rhs.number;
  }
  bool check()
  {
    number = trim(buf);
    if (number.empty()) return throw "输入不能为空", false;
    // if (number.size() != 11u) return throw "位数不对", false;
    if (regex_match(number, regex("^(0\\d{2}-\\d{8}(-\\d{1,4})?)|(0\\d{3}-\\d{7,8}(-\\d{1,4})?)$")) || // telephone
        regex_match(number, regex("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$"))) // cellphone
      return true;
    throw "输入错误";
    return false;
  }
 private:
  string number;
};

class NumberPlate
{
 public:
  friend istream& operator >>(istream &is, NumberPlate &np)
  {
    cout << endl;
    input(is, np);
    return is;
  }
  friend ostream& operator <<(ostream &os, const NumberPlate &np)
  {
    return os << np.number;
  }
  friend bool operator ==(const NumberPlate &lhs, const NumberPlate &rhs)
  {
      return lhs.number == rhs.number;
  }
  bool check()
  {
    number = trim(buf);
    if (number.empty()) return throw "输入不能为空", false;
    // if (regex_match(number, regex("^[京津沪渝冀豫云辽黑湘皖鲁新苏浙赣鄂桂甘晋蒙陕吉闽贵粤青藏川宁琼使领A-Z]{1}[A-Z]{1}[A-Z0-9]{4}[A-Z0-9挂学警港澳]{1}$")))
    if (regex_match(number, regex("^[A-Z]{1}[A-Z0-9]{4}[A-Z0-9]{1}$")))
      return true;
    throw "输入错误";
    return false;
  }
 private:
  string number;
};

class HealthCode
{
 public:
  friend istream& operator >>(istream &is, HealthCode &hc)
  {
    cout << "绿|黄|红 格式(g|y|r)" << endl;
    input(is, hc);
    return is;
  }
  friend ostream& operator <<(ostream &os, const HealthCode &hc)
  {
    if (hc.color == 0) cout << "绿";
    if (hc.color == 1) cout << "黄";
    if (hc.color == 2) cout << "红";
    return os << "码";
  }
  friend bool operator ==(const HealthCode &lhs, const HealthCode &rhs)
  {
      return lhs.color == rhs.color;
  }
  bool check()
  {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf[0] == 'g' || buf[0] == 'G') return color = 0, true;
    if (buf[0] == 'y' || buf[0] == 'Y') return color = 1, true;
    if (buf[0] == 'r' || buf[0] == 'R') return color = 2, true;
    throw "输入错误";
    return false;
  }
 private:
  int color; // 0 绿 1 黄 2 红
};

// 非空字符串
class String
{
 public:
  friend istream& operator >>(istream &is, String &s)
  {
    cout << endl;
    input(is, s);
    return is;
  }
  friend ostream& operator <<(ostream &os, const String &s)
  {
    return os << s.str;
  }
  friend bool operator ==(const String &lhs, const String &rhs)
  {
      return lhs.str == rhs.str;
  }
  bool check()
  {
    str = trim(buf);
    if (str.empty()) return throw "输入不能为空", false;
    return true;
  }
 private:
  string str;
};

class Bool
{
 public:
  friend istream& operator >>(istream &is, Bool &b)
  {
    cout << "是|否 格式(y|n)" << endl;
    input(is, b);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Bool &b)
  {
    return os << (b.tag ? "是" : "否");
  }
  friend bool operator ==(const Bool &lhs, const Bool &rhs)
  {
      return lhs.tag == rhs.tag;
  }
  bool check()
  {
    buf = trim(buf);
    if (buf.empty()) return throw "输入不能为空", false;
    if (buf[0] == 'y' || buf[0] == 'Y') return tag = true, true;
    if (buf[0] == 'n' || buf[0] == 'N') return tag = false, true;
    throw "输入错误";
    return false;
  }
 private:
  bool tag;
};

class Time {
 public:
  friend istream& operator >>(istream &is, Time &t)
  {
    cout << "格式(year-month-day hour:minute:second) 例如 2021-06-06 12:34:56 " << endl;
    input(is, t);
    return is;
  }
  friend ostream& operator <<(ostream &os, const Time &t)
  {
    return os << setfill('0') << setw(4) << t.year << '-'
        << setfill('0') << setw(2) << t.month << '-'
        << setfill('0') << setw(2) << t.day << ' '
        << setfill('0') << setw(2) << t.hour << ':'
        << setfill('0') << setw(2) << t.minute << ':'
        << setfill('0') << setw(2) << t.second;
  }
  friend bool operator <(const Time &lhs, const Time &rhs)
  {
    return vector<int>({lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute, lhs.second})
        <  vector<int>({rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute, rhs.second});
  }
  friend bool operator >(const Time &lhs, const Time &rhs)
  {
      return rhs < lhs;
  }
  friend bool operator <=(const Time &lhs, const Time &rhs)
  {
      return !(rhs < lhs);
  }
  friend bool operator >=(const Time &lhs, const Time &rhs)
  {
      return !(lhs < rhs);
  }
  friend bool operator ==(const Time &lhs, const Time &rhs)
  {
      return !(lhs < rhs || rhs < lhs);
  }
  friend bool operator !=(const Time &lhs, const Time &rhs)
  {
      return lhs < rhs || rhs < lhs;
  }
  bool check()
  {
    static char ch;
    static stringstream ss;
    if (!regex_match(buf, regex("^(?:(?!0000)[0-9]{4}-(?:(?:0[1-9]|1[0-2])-(?:0[1-9]|1[0-9]|2[0-8])|(?:0[13-9]|1[0-2])-(?:29|30)|(?:0[13578]|1[02])-31)|(?:[0-9]{2}(?:0[48]|[2468][048]|[13579][26])|(?:0[48]|[2468][048]|[13579][26])00)-02-29)\\s+([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$")))
      return throw "输入错误", false;
    ss.clear();
    ss << buf;
    ss >> year >> ch >> month >> ch >> day >> hour >> ch >> minute >> ch >> second;
    return true;
  }
 private:
  int year, month, day, hour, minute, second;
};

// 人员登记基本信息
class BasicInformation
{
 public:
  friend istream& operator >>(istream &is, BasicInformation &bi)
  {
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
  friend ostream& operator <<(ostream &os, const BasicInformation &bi)
  {
    os << "***************************************************" << endl;
    os << "姓名:" << bi.name << endl;
    os << "性别:" << bi.gender << endl;
    os << "联系电话:" << bi.phone_number << endl;
    os << "身份证号:" << bi.id_number << endl;
    os << "工作单位:" << bi.work_place << endl;
    os << "车牌号:" << bi.number_plate << endl;
    os << "进校事由:" << bi.reason << endl;
    os << "担保人:" << bi.guarantor << endl;
    os << "担保人电话:" << bi.guarantor_phone_number << endl;
    os << "健康码:" << bi.health_code << endl;
    os << "14天内是否去过疫区:" << bi.is_epidemic_area << endl;
    os << "是否有咳嗽发热等症状:" << bi.is_unhealthy_symptoms << endl;
    os << "申请进入时间:" << bi.enter_time_application << endl;
    os << "申请离开时间:" << bi.exit_time_application << endl;
    os << "实际进入时间:" << bi.enter_time << endl;
    os << "实际离开时间:" << bi.exit_time << endl;
    os << "***************************************************" << endl;
    return os;
  }
//  private:
  String name; // 姓名
  Gender gender; // 性别
  PhoneNumber phone_number; // 联系电话
  IdNumber id_number; // 身份证号
  String work_place; // 单位信息
  NumberPlate number_plate; // 车牌号
  String reason; // 进校事由
  String guarantor; // 担保人
  PhoneNumber guarantor_phone_number; // 担保人电话
  HealthCode health_code; // 健康码
  Bool is_epidemic_area;  // 14天内是否去过疫区
  Bool is_unhealthy_symptoms; // 是否有咳嗽发热等症状
  Time enter_time_application; // 申请进入时间
  Time exit_time_application; // 申请离开时间
  Time enter_time; // 实际进入时间
  Time exit_time; // 实际离开时间
};

class HolySystem
{
 public:
  void insert(const BasicInformation &bi)
  {
    database.emplace_back(bi);
    cout << "录入成功!" << endl;
  }
  void write()
  {
      if(vec.empty()) cout << "无记录" << endl;
      for(int i = 0;i < (int)vec.size();i++)
      {
          cout << "第" << i+1 << "条记录: \n" << vec[i] << endl;
      }
  }
  vector<BasicInformation> query_name()
  {
    vec.clear();
    String name;
    cout << "请输入要查询的人员姓名:"; cin >> name;
    for (auto &p : database)
        if (p.name == name)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_gender()
  {
    vec.clear();
    Gender gender;
    cout << "请输入要查询的人员性别:"; cin >> gender;
    for (auto &p : database)
        if (p.gender == gender)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_phone_number()
  {
    vec.clear();
    PhoneNumber phone_number;
    cout << "请输入要查询的人员联系电话:"; cin >> phone_number;
    for (auto &p : database)
        if (p.phone_number == phone_number)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_id_number()
  {
    vec.clear();
    IdNumber id_number;
    cout << "请输入要查询的人员身份证号:"; cin >> id_number;
    for (auto &p : database)
        if (p.id_number == id_number)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_work_place()
  {
    vec.clear();
    String work_place;
    cout << "请输入要查询的人员工作单位:"; cin >> work_place;
    for (auto &p : database)
        if (p.work_place == work_place)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_number_plate()
  {
    vec.clear();
    NumberPlate number_plate;
    cout << "请输入要查询的人员车牌号:"; cin >> number_plate;
    for (auto &p : database)
        if (p.number_plate == number_plate)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_reason()
  {
    vec.clear();
    String reason;
    cout << "请输入要查询的人员进校事由:"; cin >> reason;
    for (auto &p : database)
        if (p.reason == reason)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_guarantor()
  {
    vec.clear();
    String guarantor;
    cout << "请输入要查询的人员担保人:"; cin >> guarantor;
    for (auto &p : database)
        if (p.guarantor == guarantor)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_guarantor_phone_number()
  {
    vec.clear();
    PhoneNumber guarantor_phone_number;
    cout << "请输入要查询的人员担保人电话:"; cin >> guarantor_phone_number;
    for (auto &p : database)
        if (p.guarantor_phone_number == guarantor_phone_number)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_is_epidemic_area()
  {
    vec.clear();
    Bool is_epidemic_area;
    cout << "请输入要查询的人员14天内是否去过疫区:"; cin >> is_epidemic_area;
    for (auto &p : database)
        if (p.is_epidemic_area == is_epidemic_area)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_is_unhealthy_symptoms()
  {
    vec.clear();
    Bool is_unhealthy_symptoms;
    cout << "请输入要查询的是否有咳嗽发热等症状:"; cin >> is_unhealthy_symptoms;
    for (auto &p : database)
        if (p.is_unhealthy_symptoms == is_unhealthy_symptoms)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_health_code()
  {
    vec.clear();
    HealthCode health_code;
    cout << "请输入要查询的人员健康码:"; cin >> health_code;
    for (auto &p : database)
        if (p.health_code == health_code)
            vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_enter_time_application()
  {
    vec.clear();
    Time head, tail;
    cout << "请输入要查询的人员申请进入时间段:\n";
    cout << "请输入开始时间:"; cin >> head;
    cout << "请输入结束时间:"; cin >> tail;
    for (auto &p : database)
      if (p.enter_time_application >= head && p.enter_time_application <= tail)
        vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_exit_time_application()
  {
    vec.clear();
    Time head, tail;
    cout << "请输入要查询的人员申请离开时间段:\n";
    cout << "请输入开始时间:"; cin >> head;
    cout << "请输入结束时间:"; cin >> tail;
    for (auto &p : database)
      if (p.exit_time_application >= head && p.exit_time_application <= tail)
        vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_enter_time()
  {
    vec.clear();
    Time head, tail;
    cout << "请输入要查询的人员实际进入时间段:\n";
    cout << "请输入开始时间:"; cin >> head;
    cout << "请输入结束时间:"; cin >> tail;
    for (auto &p : database)
      if (p.enter_time >= head && p.enter_time <= tail)
        vec.emplace_back(p);
    return vec;
  }
  vector<BasicInformation> query_exit_time()
  {
    vec.clear();
    Time head, tail;
    cout << "请输入要查询的人员实际离开时间段:\n";
    cout << "请输入开始时间:"; cin >> head;
    cout << "请输入结束时间:"; cin >> tail;
    for (auto &p : database)
      if (p.exit_time >= head && p.exit_time <= tail)
        vec.emplace_back(p);
    return vec;
  }
 private:
  vector<BasicInformation> database, vec;
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
    HolySystem holy_system;
    BasicInformation basic_information;
    while(1)
    {
        system("cls");
        cout<<"\n***************************菜单********************************\n";
        cout << "*           1.添加记录                                        *\n";
        cout << "*           2.按姓名查询出入人员信息                          *\n";
        cout << "*           3.按性别查询出入人员信息                          *\n";
        cout << "*           4.按联系电话查询出入人员信息                      *\n";
        cout << "*           5.按身份证查询出入人员信息                        *\n";
        cout << "*           6.按工作单位查询出入人员信息                      *\n";
        cout << "*           7.按车牌号查询出入人员信息                        *\n";
        cout << "*           8.按进校事由查询出入人员信息                      *\n";
        cout << "*           9.按担保人查询出入人员信息                        *\n";
        cout << "*           10.按担保人电话查询出入人员信息                   *\n";
        cout << "*           11.按14天内是否去过疫区查询出入人员信息           *\n";
        cout << "*           12.按是否有咳嗽发热等症状查询出入人员信息         *\n";
        cout << "*           13.按健康码查询出入人员信息                       *\n";
        cout << "*           14.按申请进入时间段查询出入人员信息               *\n";
        cout << "*           15.按申请离开时间段查询出入人员信息               *\n";
        cout << "*           16.按实际进入时间段查询出入人员信息               *\n";
        cout << "*           17.按实际离开时间段查询出入人员信息               *\n";
        cout << "*           18.退出程序                                       *\n";
        cout << "***************************************************************\n";
        cout << "                      请选择(1—18):                            \n";
        int choose;
        cin >> choose;
        getchar();
        if(choose<1||choose>18)
        {
            cout << "输入错误，请重新输入:\n";
            cin.clear();
            while(cin.get()!='\n') continue;
        }
        else
        {
            switch(choose)
            {
                case 1:
                    cin >> basic_information;
                    holy_system.insert(basic_information);
                    break;
                case 2:
                    holy_system.query_name();
                    break;
                case 3:
                    holy_system.query_gender();
                    break;
                case 4:
                    holy_system.query_phone_number();
                    break;
                case 5:
                    holy_system.query_id_number();
                    break;
                case 6:
                    holy_system.query_work_place();
                    break;
                case 7:
                    holy_system.query_number_plate();
                    break;
                case 8:
                    holy_system.query_reason();
                    break;
                case 9:
                    holy_system.query_guarantor();
                    break;
                case 10:
                    holy_system.query_guarantor_phone_number();
                    break;
                case 11:
                    holy_system.query_is_epidemic_area();
                    break;
                case 12:
                    holy_system.query_is_unhealthy_symptoms();
                    break;
                case 13:
                    holy_system.query_health_code();
                    break;
                case 14:
                    holy_system.query_enter_time_application();
                    break;
                case 15:
                    holy_system.query_exit_time_application();
                    break;
                case 16:
                    holy_system.query_enter_time();
                    break;
                case 17:
                    holy_system.query_exit_time();
                    break;
                default:
                    return 0;
            }
            if (choose != 1) holy_system.write();
        }

        system("pause");
    }
    return 0;
}