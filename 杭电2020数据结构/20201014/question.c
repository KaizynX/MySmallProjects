/*
 * @Author: Kaizyn
 * @Date: 2020-10-16 09:10:19
 * @LastEditTime: 2020-10-16 09:18:57
 */
#include <stdio.h>
#define bool int
#define true 1
#define false 0
#define N (100)

char s[N];

bool check() {
  int top = 0;
  for (int i = 0; s[i]; ++i) {
    if (s[i] == 'I') {
      ++top;
    } else {
      if (--top < 0) return false;
    }
  }
  return top == 0;
}

int main() {
  while (~scanf("%s", s)) {
    puts(check() ? "true" : "false");
  }
  return 0;
}
/*
IOIIOIOO
IOOIOIIO
IIIOIOIO
IIIOOIOO
*/
/*
IOIIOIOO
true
IOOIOIIO
false
IIIOIOIO
false
IIIOOIOO
true
*/