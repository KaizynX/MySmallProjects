/*
 * @Author: Kaizyn
 * @Date: 2020-09-26 16:28:23
 * @LastEditTime: 2020-09-26 16:32:13
 */
#include <stdio.h>

struct Node{
  int a;
};

int main() {
  struct Node nd;
  // Node nd;
  nd.a = 1;
  printf("%d\n", nd.a);
  return 0;
}