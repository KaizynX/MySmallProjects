/*
 * @Author: Kaizyn
 * @Date: 2020-09-26 16:28:23
 * @LastEditTime: 2020-10-26 13:40:36
 */
#include <stdio.h>
#include <string.h>

struct Node{
  int a;
};

int main() {
  char s1[30] = "3.1x^11)+(7-5x^8+11x^9)";
  char s2[10] = "1x";
  double a1, a2;
  sscanf(s1, "%lf", &a1);
  printf("%f\n", a1);
  sscanf(s2, "%lf", &a2);
  printf("%f\n", a2);
  float b1, b2;
  sscanf(s1, "%f", &b1);
  printf("%f\n", b1);
  sscanf(s2, "%f", &b2);
  printf("%f\n", b2);
  return 0;
}