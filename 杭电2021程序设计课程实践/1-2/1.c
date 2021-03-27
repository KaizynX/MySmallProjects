/*
 * @Author: Kaizyn
 * @Date: 2021-03-21 13:34:13
 * @LastEditTime: 2021-03-21 13:35:50
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

int main() {
  SqList La, Lb;
  InitList_Sq(&La);
  InitList_Sq(&Lb);

  for (int a; scanf("%d", &a) == 1; ) {
    if (a > 0) ListInsert(&La, a);
    if (a < 0) ListInsert(&Lb, a);
  }

  printf("La:");
  ListPrint(La);
  printf("Lb:");
  ListPrint(Lb);
  DestroyList_Sq(&La);
  DestroyList_Sq(&Lb);
  return 0;
}