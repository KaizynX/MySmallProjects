/*
 * @Author: Kaizyn
 * @Date: 2020-09-23 18:43:22
 * @LastEditTime: 2020-09-24 18:32:59
 */
// p18 2.21 2.25
#include <stdio.h>
#include "../lib/SequenceList.c"

void ReverseSqList(SqList *L) {
  for (int i = 0, j = ListLength_Sq(*L)-1; i != j; ++i, --j) {
    LElemType_Sq tmp = L->elem[i];
    L->elem[i] = L->elem[j];
    L->elem[j] = tmp;
  }
}

void MergeSqList(SqList La, SqList Lb, SqList *Lc) {
  for (int i = 0, j = 0, k = 0;
      i < ListLength_Sq(La) && j < ListLength_Sq(Lb);
      La.elem[i] <= Lb.elem[j] ? ++i : ++j) {
    if (La.elem[i] == Lb.elem[j]) ListInsert_Sq(Lc, ++k, La.elem[i]);
  }
}

int main() {
  int lena, lenb, lenc;
  SqList La, Lb, Lc;
  InitList_Sq(&La);
  InitList_Sq(&Lb);
  InitList_Sq(&Lc);

  printf("2.21逆置\n");
  printf("输入顺序表元素个数:");
  scanf("%d", &lena);
  printf("输入顺序表的%d个元素:", lena);
  for (int i = 1, a; i <= lena; ++i) {
    scanf("%d", &a);
    ListInsert_Sq(&La, i, a);
  }
  ReverseSqList(&La);
  printf("顺序表逆置后结果:");
  for (int i = 1; i <= lena; ++i) {
    LElemType_Sq a;
    GetElem_Sq(La, i, &a);
    printf("%d%c", a, " \n"[i==lena]);
  }
  ClearList_Sq(&La);

  printf("2.25交集\n");
  printf("输入顺序表A元素个数:");
  scanf("%d", &lena);
  printf("输入顺序表A的%d个元素:", lena);
  for (int i = 1, a; i <= lena; ++i) {
    scanf("%d", &a);
    ListInsert_Sq(&La, i, a);
  }
  printf("输入顺序表B元素个数:");
  scanf("%d", &lenb);
  printf("输入顺序表B的%d个元素:", lenb);
  for (int i = 1, b; i <= lenb; ++i) {
    scanf("%d", &b);
    ListInsert_Sq(&Lb, i, b);
  }
  MergeSqList(La, Lb, &Lc);
  printf("A与B的交集C为:");
  lenc = ListLength_Sq(Lc);
  for (int i = 1; i <= lenc; ++i) {
    LElemType_Sq c;
    GetElem_Sq(Lc, i, &c);
    printf("%d%c", c, " \n"[i==lenc]);
  }
  return 0;
}