/*
 * @Author: Kaizyn
 * @Date: 2021-03-21 13:34:13
 * @LastEditTime: 2021-03-27 23:07:39
 */
#include <stdio.h>
#include "DualCycleLinkedList.c"

int main() {
  int m, n, k;
  scanf("%d%d%d", &m, &n, &k);
  DuLinkList La, Lb;
  InitList_DuL(&La);
  InitList_DuL(&Lb);
  for (int i = 1; i <= m; ++i) {
    ListInsert_DuL(La, i, i);
  }
  for (int i = 1, p = 1; i <= m; ++i) {
    LElemType_DC e;
    p += n-1;
    while (p > m-i+1) p -= m-i+1;
    ListDelete_DuL(La, p, &e);
    ListInsert_DuL(Lb, i, e);
    // printf("%d%c", e, " \n"[i==m]);
  }
  for (int i = 1, p = 1; i <= m; ++i) {
    LElemType_DC e;
    p += k-1;
    while (p > m-i+1) p -= m-i+1;
    ListDelete_DuL(Lb, p, &e);
    printf("%4d", e);
  }
  DestroyList_DuL(&La);
  DestroyList_DuL(&Lb);
  return 0;
}