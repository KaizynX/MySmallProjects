/*
 * @Author: Kaizyn
 * @Date: 2021-03-21 13:34:13
 * @LastEditTime: 2021-03-27 23:13:14
 */
#include <stdio.h>
#include "DualCycleLinkedList.c"

void play(int n, DuLinkList La, DuLinkList Lb) {
  LElemType_DC e;
  for (int i = 1, p = 1, m = ListLength_DuL(La); i <= m; ++i) {
    p += n-1;
    while (p > m-i+1) p -= m-i+1;
    ListDelete_DuL(La, p, &e);
    ListInsert_DuL(Lb, i, e);
  }
}

int main() {
  int m, n;
  scanf("%d", &m);
  DuLinkList L[2];
  InitList_DuL(L+0);
  InitList_DuL(L+1);
  for (int i = 1; i <= m; ++i) {
    ListInsert_DuL(L[0], i, i);
  }
  int l = 0;
  while (scanf("%d", &n) == 1) {
    play(n, L[l], L[l^1]);
    l ^= 1;
  }
  for (int i = 1; i <= m; ++i) {
    LElemType_DC e;
    GetElem_DuL(L[l], i, &e);
    printf("%4d", e);
  }
  DestroyList_DuL(L+0);
  DestroyList_DuL(L+1);
  return 0;
}