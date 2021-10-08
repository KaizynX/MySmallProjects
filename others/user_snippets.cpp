/*
 * @Author: Kaizyn
 * @Date: 2021-03-03 11:00:03
 * @LastEditTime: 2021-08-23 15:53:31
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

/*
  "C++DEBUG" : {
    "prefix": "DEBUG",
    "body": [
      "#ifdef DEBUG",
      "#endif"
    ],
    "description": "for debug"
  },
*/
string s, res;

signed main() {
  cout << "name:";
  cin >> s;
  res += "  \""+s+"\" : {\n";
  cout << "prefix:";
  cin >> s;
  res += "    \"prefix\": \""+s+"\",\n";
  res += "    \"body\": [\n";
  getline(cin, s); // read '\n'
  while (getline(cin, s)) {
    for (int p = 0; (p = s.find("\"", p)) != s.npos; p += 2) {
      s.replace(p, 1, "\\\"");
    }
    res += "      \""+s+"\",\n";
  }
  res += "    ],\n";
  res += "    \"description\": \"template\"\n";
  res += "  },\n";
  cout << "*****************\n" << res;
  system("pause");
  return 0;
}