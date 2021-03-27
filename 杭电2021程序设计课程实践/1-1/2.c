/*
 * @Author: Kaizyn
 * @Date: 2021-03-21 13:36:25
 * @LastEditTime: 2021-03-21 13:42:23
 */
#include <stdio.h>
#include "SequenceList.c"

void ListInsert(SqList *L, LElemType_Sq e) {
  int i = 1;
  for (LElemType_Sq val; i <= ListLength_Sq(*L); ++i) {
    GetElem_Sq(*L, i, &val);
    if (val >= e) break;
  }
  ListInsert_Sq(L, i, e);
}

void ReverseSqList(SqList *L) {
  for (int i = 0, j = ListLength_Sq(*L)-1; i != j; ++i, --j) {
    LElemType_Sq tmp = L->elem[i];
    L->elem[i] = L->elem[j];
    L->elem[j] = tmp;
  }
}

void ListPrint(SqList L) {
  int len = ListLength_Sq(L);
  for (int i = 1; i <= len; ++i) {
    LElemType_Sq a;
    GetElem_Sq(L, i, &a);
    printf("%d%c", a, " \n"[i==len]);
  }
}

void ListMerge(SqList La, SqList Lb, SqList *Lc) {
  int lena = ListLength_Sq(La), lenb = ListLength_Sq(Lb);
  LElemType_Sq a, b;
  for (int i = 1, j = 1, k = 1; i <= lena || j <= lenb; ++k) {
    i <= lena ? GetElem_Sq(La, i, &a) : a = INT_MAX;
    j <= lenb ? GetElem_Sq(Lb, j, &b) : b = INT_MAX;
    if (a < b) ListInsert_Sq(Lc, k, a), ++i;
    else ListInsert_Sq(Lc, k, b), ++j;
  }
}

int main() {
  SqList La, Lb, Lc;
  InitList_Sq(&La);
  InitList_Sq(&Lb);
  InitList_Sq(&Lc);

  for (int a; scanf("%d", &a) == 1; ) {
    if (a > 0) ListInsert(&La, a);
    if (a < 0) ListInsert(&Lb, a);
  }
  puts("合并前");
  printf("La:");
  ListPrint(La);
  printf("Lb:");
  ListPrint(Lb);
  puts("合并后");
  ListMerge(La, Lb, &Lc);
  ListPrint(Lc);
  DestroyList_Sq(&La);
  DestroyList_Sq(&Lb);
  DestroyList_Sq(&Lc);
  return 0;
}