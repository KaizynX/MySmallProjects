/*
 * @Author: Kaizyn
 * @Date: 2020-09-23 18:43:22
 * @LastEditTime: 2021-03-21 13:33:06
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
  int lena, lenb;
  SqList La, Lb;
  InitList_Sq(&La);
  InitList_Sq(&Lb);

  printf("逆置\n");
  printf("输入顺序表元素个数:");
  scanf("%d", &lena);
  printf("输入顺序表的%d个元素:", lena);
  for (int i = 1, a; i <= lena; ++i) {
    scanf("%d", &a);
    ListInsert_Sq(&La, i, a);
  }
  printf("输入顺序表b元素个数:");
  scanf("%d", &lenb);
  printf("输入顺序表b的%d个元素:", lenb);
  for (int i = 1, a; i <= lenb; ++i) {
    scanf("%d", &a);
    // ListInsert(&Lb, a);
    ListInsert_Sq(&Lb, i, a);
  }

  puts("顺序表逆置前结果:");
  printf("La:");
  ListPrint(La);
  printf("Lb:");
  ListPrint(Lb);
  puts("顺序表逆置后结果:");
  ReverseSqList(&La);
  ReverseSqList(&Lb);
  printf("La:");
  ListPrint(La);
  printf("Lb:");
  ListPrint(Lb);
  DestroyList_Sq(&La);
  DestroyList_Sq(&Lb);
  return 0;
}