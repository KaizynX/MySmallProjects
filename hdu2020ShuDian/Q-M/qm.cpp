#include <bits/stdc++.h>

using namespace std;

bool comp(int n, char *a, char *b) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i] && (a[i] != '-' && b[i] != '-')) return false;
  }
  return true;
}

int implicant(int n, char *a, char *b) {
  int count = 0, temp;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      count++;
      temp = i;
    }
  }
  if (count == 1) return temp;
  else return -1;
}

bool cointain(int n, char *a, char *b) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i] && (a[i] != '-')) return false;
  }
  return true;
}

signed main() {
  int n, count, tmp;
  char *temp;
  bool flag[2];
  vector<char*> v[10];
  vector<char*> relative;
  vector<char*> prime;
  vector<char*> result;

  cout << "输入变量数：\n";
  cin >> n;

  temp = new char[n];
  cout << "请输入最小项(2结束)\n";
  flag[0] = true;
  while (flag[0]) {
    for (int i = 0; i < n; ++i) {
      cin >> temp[i];
      if (temp[i] != '0' && temp[i] != '1') {
        flag[0] = false;
        break;
      }
    }
    if (flag[0]) {
      v[0].emplace_back(new char[n]);
      relative.emplace_back(new char[n]);
      strcpy(v[0].back(), temp);
      strcpy(relative.back(), temp);
    }
  }
  cout << "请输入无关项(2结束)\n";
  flag[0] = true;
  while (flag[0]) {
    for (int i = 0; i < n; ++i) {
      cin >> temp[i];
      if (temp[i] != '0' && temp[i] != '1') {
        flag[0] = false;
        break;
      }
    }
    if (flag[0]) {
      v[0].emplace_back(new char[n]);
      strcpy(v[0].back(), temp);
    }
  }
  for (int i = 0; i < 10; ++i) {
    if (v[i].empty()) break;
    for (int j = 0; j < (int)v[i].size(); ++j) {
      flag[0] = false;
      for (int k = 0; k < (int)v[i].size(); ++k) {
        if (implicant(n ,v[i][j], v[i][k]) != -1) {
          strcpy(temp, v[i][j]);
          temp[implicant(n, v[i][j], v[i][k])] = '-';
          flag[1] = true;
          flag[0] = true;
          for (int l = 0; l < (int)v[i+1].size(); ++l) {
            if (!strcmp(v[i+1][l], temp)) flag[1] = false;
          }
          if (flag[1]) {
            v[i+1].emplace_back(new char[n]);
            strcpy(v[i+1].back(), temp);
          }
        }
      }
      if (!flag[0]) {
        prime.emplace_back(new char[n]);
        strcpy(prime.back(), v[i][j]);
      }
    }
  }
  for (int i = 0; i < (int)relative.size() && !relative.empty(); ++i) {
    count = 0;
    for (int j = 0; j < (int)prime.size() && !prime.empty(); ++j) {
      if (comp(n, relative[i], prime[j])) {
        count++;
        tmp = j;
      }
    }
    if (count == 1) {
      result.emplace_back(new char[n]);
      strcpy(result.back(), prime[tmp]);
      for (int j = 0; j < (int)relative.size(); ++j) {
        if (comp(n, relative[j], prime[tmp])) {
          relative.erase(relative.begin()+j);
          --j;
        }
      }
      prime.erase(prime.begin()+tmp);
      --i;
    }
  }
  while (!relative.empty()) {
    strcpy(temp, prime.back());
    prime.pop_back();
    count = 0;
    for (int i = 0; i < (int)relative.size(); ++i) {
      if (comp(n, relative[i], temp)) {
        relative.erase(relative.begin()+i);
        --i;
        ++count;
      }
    }
    if (count > 0) {
      result.emplace_back(new char[n]);
      strcpy(result.back(), temp);
    }
  }
  while (result.size()) {
    for (int i = 0; i < 4; ++i) {
      cout << *(result.back()+i);
    }
    cout << ' ';
    result.pop_back();
  }
  cout << '\n';
  system("pause");
  return 0;
}
/*
4
0100
0101
0110
1000
1001
1010
1101
2
0000
1111
0111
2

1-01 -1-1 10-0 01--
*/