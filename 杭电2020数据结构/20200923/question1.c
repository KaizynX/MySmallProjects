/*
 * @Author: Kaizyn
 * @Date: 2020-09-24 18:32:02
 * @LastEditTime: 2020-09-27 08:26:51
 */
/****************************
 * 单链表删除其值为x的结点的前趋结点
 ***************************/
#include <stdio.h>
#include "../lib/SinglyLinkedList.c"

LinkList L;

Status ListDeletePrior(LinkList L, LElemType_L e) {
  LinkList cur = L->next;
  LElemType_L tmp;
  for (int i = 1; cur; ++i, cur = cur->next) {
    if (cur->next && cur->next->data == e) {
      ListDelete_L(L, i, &tmp);
      return OK;
    }
  }
  return ERROR;
}

void PrintElem(LElemType_L e) {
  printf("%d ", e);
}

void Print_L(LinkList L) {
  ListTraverse_L(L, PrintElem);
}

int main() {
  int len, x;
  InitList_L(&L);
  printf("输入单链表元素个数:");
  scanf("%d", &len);
  printf("输入顺序表的%d个元素:", len);
  for (int i = 1, a; i <= len; ++i) {
    scanf("%d", &a);
    ListInsert_L(L, i, a);
  }
  puts("删除单链表值为x的结点的前驱结点");
  printf("输入x:");
  while (scanf("%d", &x) == 1) {
    if (ListDeletePrior(L, x)) {
      puts("删除x前驱成功");
      printf("当前链表为:");
      Print_L(L);
      putchar('\n');
    } else {
      puts("删除x前驱失败");
    }
    if (ListLength_L(L) <= 1) break;
    printf("输入x:");
  }
  return 0;
}