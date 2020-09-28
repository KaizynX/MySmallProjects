/*
 * @Author: Kaizyn
 * @Date: 2020-09-27 08:26:26
 * @LastEditTime: 2020-09-27 08:38:34
 */
/****************************
 * 单链表实现两个一元多项式的相加
 ***************************/
#include <stdio.h>
#include "../lib/SinglyLinkedList.c"

LinkList Add(LinkList La, LinkList Lb) {
  LinkList Lc, la = La->next, lb = Lb->next;
  InitList_L(&Lc);
  for (int i = 0; la || lb; ++i) {
    LElemType_L val = 0;
    if (la) val += la->data, la = la->next;
    if (lb) val += lb->data, lb = lb->next;
    ListInsert_L(Lc, i+1, val);
  }
  return Lc;
}

void Print_E(LElemType_L e) {
  printf("%d ", e);
}

void Print_L(LinkList L) {
  ListTraverse_L(L, Print_E);
}

void Input(LinkList L, int id) {
  int len;
  printf("输入第%d个一元多项式最高次幂:", id);
  scanf("%d", &len);
  printf("从低到高输入一元多项式各次幂的系数:");
  for (int i = 0, a; i <= len; ++i) {
    scanf("%d", &a);
    ListInsert_L(L, i+1, a);
  }
}

int main() {
  LinkList La, Lb, Lc;
  InitList_L(&La);
  InitList_L(&Lb);
  Input(La, 1);
  Input(Lb, 2);
  Lc = Add(La, Lb);
  printf("两个多项式相加的结果为:");
  Print_L(Lc);
  return 0;
}