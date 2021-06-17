/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 11:21:58
 * @LastEditTime: 2021-04-28 11:39:28
 */
#include<bitsdc++.h>
using namespace std;
char ch[101];
class mystring
{
	public:
		mystring();
		mystring(const char *str);
		~mystring()
		{
			delete[] buf;
			cout<<"destruct"<<endl;
		}
		mystring & operator=(const mystring &rhs);
		friend ostream & operator<<(ostream &os,const mystring &rhs);
	private:
		explicit mystring(int len)
		{
			buf=new char[len+1];
		}
		char *buf;
};
mystring::mystring()
{
	buf=new char[1];
	buf[0]='\0';
	cout<<"construct 0"<<endl;
}
mystring::mystring(const char *str)
{
	buf=new char[strlen(str)+1];
	strcpy(buf,str);
	cout<<"construct 1"<<endl;
}
mystring & mystring::operator=(const mystring &rhs)
{
	buf=new char[strlen(rhs.buf)+4];
	strcpy(buf,"c++");
	strcat(buf,rhs.buf);
	return *this;
}
ostream & operator<<(ostream &os,const mystring &rhs)
{
	os<<rhs.buf<<endl;
	return os;
}
int main()
{
	cin>>ch;
	mystring str1(ch);
	cout<<str1;
	mystring str2;
	str2=str1;
	cout<<str2;
	return 0;
}