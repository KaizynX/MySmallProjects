/*
 * @Author: Kaizyn
 * @Date: 2021-04-21 13:36:22
 * @LastEditTime: 2021-04-21 14:23:53
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353; // 1e9+7;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
const int N = 1e6+7;
// const int TLE = 5*60*1000; // 五分钟 单位 ms
const int TLE = 10*1000; // 10s

struct Timer {
  clock_t s, t;
  void start() {
    s = clock();
  }
  void stop() {
    t = clock();
  }
  int current_time() {
    return (clock()-s)*1000/CLOCKS_PER_SEC;
  }
  int total_time() {
    return (t-s)*1000/CLOCKS_PER_SEC;
  }
} timer;

int n;
int a[N];

void generate(int sz, int spj = 0) {
  iota(a+1, a+sz+1, 1);
  for (int i = 1; i <= n; ++i) {
    if (!spj || rand()%2) {
      swap(a[i], a[rand()%i+1]);
    }
  }
}

void check() {
  cout << "check:" << (is_sorted(a+1, a+n+1) ? "successful" : "failed");
}

void MaoPao() {
  for (int i = 1; i < n; ++i) {
    for (int j = n; j > i; --j) {
      if (a[j] < a[j-1]) {
        swap(a[j], a[j-1]);
      }
    }
    if (timer.current_time() > TLE) return cout << "Time Limit Exceeded\n", void();
  }
}

void XuanZe() {
  for (int i = 1, j, k; i < n; ++i) {
    for (j = i+1, k = i; j <= n; ++j) {
      if (a[j] < a[k]) {
        k = j;
      }
    }
    swap(j, k);
    if (timer.current_time() > TLE) return cout << "Time Limit Exceeded\n", void();
  }
}

void ChaRu() {
  for (int i = 2, j, k; i <= n; ++i) {
    k = a[i];
    for (j = i-1; j; --j) {
      if (a[j] > k) {
        a[j+1] = a[j];
      } else {
        a[j] = k;
        break;
      }
    }
    if (timer.current_time() > TLE) return cout << "Time Limit Exceeded\n", void();
  }
}

void MergeSort(int l = 1, int r = n) {
  static int b[N];
  if (l >= r) return;
  int mid = (l+r)/2;
  MergeSort(l, mid);
  MergeSort(mid+1, r);
  for (int i = l, j = mid+1, k = l; i <= mid || j <= r; ) {
    if (j > r || (i <= mid && a[i] < a[j])) {
      b[k++] = a[i++];
    } else {
      b[k++] = a[j++];
    }
  }
  memcpy(a+l, b+l, sizeof(int)*(r-l+1));
}

void Qsort(int l = 1, int r = n) {
  if(l >= r) return;
  swap(a[l], a[l+rand()%(r-l)]);
  int i = l, j = r, mid = a[l];
  while(i < j) {
    while(i < j && a[j] >= mid) --j;
    swap(a[i], a[j]);
    while(i < j && a[i] < mid) ++i;
    swap(a[i], a[j]);
  }
  Qsort(l, i-1);
  Qsort(i+1, r);
}

signed main() {
  freopen("output.txt", "w", stdout);
  for (n = 100; n <= 1000000; n *= 10) {
    cout << "数据规模" << n << '\n';
    for (int spj : {0, 1}) {
      cout << (!spj ? "随机数组" : "几乎有序数组") << '\n';
      generate(n, spj);

      timer.start();
      MaoPao();
      timer.stop();
      check();
      cout << "冒泡排序:" << timer.total_time() << "ms\n";

      timer.start();
      XuanZe();
      timer.stop();
      check();
      cout << "选择排序:" << timer.total_time() << "ms\n";

      timer.start();
      ChaRu();
      timer.stop();
      check();
      cout << "插入排序:" << timer.total_time() << "ms\n";

      timer.start();
      MergeSort();
      timer.stop();
      check();
      cout << "归并排序:" << timer.total_time() << "ms\n";

      timer.start();
      Qsort();
      timer.stop();
      check();
      cout << "快速排序:" << timer.total_time() << "ms\n";
    }
  }
  return 0;
}