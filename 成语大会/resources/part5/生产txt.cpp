#include <bits/stdc++.h>
using namespace std;

int main()
{
	int s, t;
	string name, style;
	cout << "�����ļ���: ";
	cin >> name;
	cout <<endl<< "�����ļ���ʽ: ";
	cin >> style;
	cout <<endl<< "�����ļ����: N ~ M" << endl;
	cin >> s >> t;
	for(int i = s; i <= t; ++i)
	{
		ostringstream stream;
		stream << i;
		string cmd = "echo \0 >" + name + stream.str()+"." + style + '\n';
		cout << "����:" << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}
