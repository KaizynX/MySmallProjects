#include <bits/stdc++.h>
using namespace std;

int main()
{
	int s, t;
	string name, style;
	cout << "输入文件名: ";
	cin >> name;
	cout <<endl<< "输入文件格式: ";
	cin >> style;
	cout <<endl<< "输入文件序号: N ~ M" << endl;
	cin >> s >> t;
	for(int i = s; i <= t; ++i)
	{
		ostringstream stream;
		stream << i;
		string cmd = "echo \0 >" + name + stream.str()+"." + style + '\n';
		cout << "生成:" << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}
