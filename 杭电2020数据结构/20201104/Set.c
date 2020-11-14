/*
 * @Author: Kaizyn
 * @Date: 2020-11-04 17:41:09
 * @LastEditTime: 2020-11-04 18:36:01
 */
#include <stdio.h>
#include <stdlib.h>
// #define DEBUG

#define N 100

typedef struct Set {
  int bit;
} Set;

void SetInit(Set *s) {
  s->bit = 0;
}

void SetInsert(Set *s, char c) {
  s->bit |= 1<<(c-'a');
}

int SetFind(Set s, char c) {
  return s.bit>>(c-'a')&1;
}

void SetErase(Set *s, char c) {
  s->bit &= ((1<<26)-1)-(1<<(c-'a'));
}

Set SetUnion(Set s1, Set s2) {
  Set s;
  s.bit = s1.bit|s2.bit;
  return s;
}

Set SetIntersection(Set s1, Set s2) {
  Set s;
  s.bit = s1.bit&s2.bit;
  return s;
}

Set SetDifference(Set s1, Set s2) {
  Set s;
  s.bit = s1.bit^(s1.bit&s2.bit);
  return s;
}

void SetPrint(Set s) {
#ifdef DEBUG
  printf("SetPrint:%d ", s.bit);
#endif
  putchar('{');
  for (int i = 0, first = 1; i < 26; ++i) {
    if ((s.bit>>i)&1) {
      if (!first) putchar(',');
      putchar('a'+i);
      first = 0;
    }
  }
  putchar('}');
  putchar('\n');
}

void SetRead(Set *s) {
  SetInit(s);
  char c;
  while ((c = getchar()) != '\n') {
    if (c >= 'a' && c <= 'z') SetInsert(s, c);
  }
#ifdef DEBUG
  printf("SetRead:%d ", s->bit);
#endif
}

int main() {
  Set s1, s2;
  printf("请在一行内输入集合1的各个元素：");
  SetRead(&s1);
  printf("请在一行内输入集合2的各个元素：");
  SetRead(&s2);
  printf("集合1与集合2的并为：");
  SetPrint(SetUnion(s1, s2));
  printf("集合1与集合2的交为：");
  SetPrint(SetIntersection(s1, s2));
  printf("集合1与集合2的差为：");
  SetPrint(SetDifference(s1, s2));
  printf("集合2与集合1的差为：");
  SetPrint(SetDifference(s2, s1));
  return 0;
}