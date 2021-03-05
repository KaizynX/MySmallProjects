/*
 * @Author: Kaizyn
 * @Date: 2021-03-03 11:00:03
 * @LastEditTime: 2021-03-03 11:37:21
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
    res += "      \""+s+"\",\n";
  }
  res += "    ],\n";
  res += "    \"description\": \"template\"\n";
  res += "  },\n";
  cout << "*****************\n" << res;
  return 0;
}