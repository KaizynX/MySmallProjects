/*
 * @Author: Kaizyn
 * @Date: 2021-04-08 14:21:17
 * @LastEditTime: 2021-04-08 14:43:52
 */
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n, k;
  vector<string> a;
  cout << "输入单位总人数：";
  cin >> n;
  a.resize(n);
  cout << "输入每位员工的名字：";
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    cout << a[i] << endl;
  }
  cout << "输入执行任务所需人数：";
  cin >> k;
  int s=(1<<k)-1;
  while(s<(1<<n)){
    for (int i = 0; i < n; ++i) if ((s>>i)&1) {
      cout << a[i] << ' ';
    }
    cout << endl;
    int x=s&-s,y=s+x;
    s=((s&~y)/x>>1)|y;
  }
  return 0;
}
/*
3
zhangsan lisi wangwu
2
*/