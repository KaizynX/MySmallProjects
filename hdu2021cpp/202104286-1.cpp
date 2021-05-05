/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 11:03:56
 * @LastEditTime: 2021-04-28 11:05:26
 */
#include <iostream>
using namespace std;
class People{
private:
    string id;
    string name;
public:
    People(string id, string name){
        this->id = id;
        this->name = name;
    }
    string getId(){
        return this->id;
    }
    string getName(){
        return name;
    }
};
class Student : public People{
private:
    string sid;
    int score;
public:
    Student(string id, string name, string sid, int score)
        : People(id, name), sid(sid), score(score) {
      ;
    }
    friend ostream& operator <<(ostream &o, Student &s);
};
ostream& operator <<(ostream &o, Student &s){
    o << "(Name:" << s.getName() << "; id:"
      << s.getId() << "; sid:" << s.sid
      << "; score:" << s.score << ")";
    return o;
}
int main(){
    Student zs("370202X", "Zhang San", "1052102", 96);
    cout << zs  << endl;
    return 0;
}
// (Name:Zhang San; id:370202X; sid:1052102; score:96)