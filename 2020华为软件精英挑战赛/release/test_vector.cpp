/*
 * @Author: Kaizyn
 * @Date: 2020-04-18 11:31:48
 * @LastEditTime: 2020-04-18 19:56:09
 */
#include <bits/stdc++.h>

using namespace std;

struct Timer{
	double start,pre;
	Timer(){start=pre=clock();}
	void operator()(const string &s){
		double now=clock();
		cerr<<"["<<s<<"] ";
		cerr<<"Interval: "<<(now-pre)/1000<<"s | ";
		cerr<<"Total:"<<(now-start)/1000<<"s"<<endl;
		pre=now;
	}
}timer;

const int N = 1e7;
const int T = 1e7;

int a[N];
vector<int> v(N);

signed main()
{
    for (int i = 0; i < N; ++i) a[i] = v[i] = i;
    int tmp;
    timer("start");
    //
    for (int i = 0; i < T; ++i)
    for (int *it = a, *ed = a+N; it != ed; ++it) {
        tmp = *it;
        *it = i+1;
    }
    timer("array pointer");
    //
    for (int i = 0; i < T; ++i)
    for (int j = 0; j < N; ++j) {
        tmp = a[j];
        a[j] = i;
    }
    timer("array at");
    /*
    for (int i = 0; i < T; ++i)
    for (int *it = v.data(), *ed = it+v.size(); it != ed; ++it) {
        tmp = *it;
        *it = i;
    }
    timer("vector data");
    //
    for (int i = 0; i < T; ++i)
    for (vector<int>::iterator it = v.begin(), ed = v.end(); it != ed; ++it) {
        tmp = *it;
        *it = i;
    }
    timer("vector iterator");
    */
    return 0;
}