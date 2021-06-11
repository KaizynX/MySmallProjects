/*
 * @Author: Kaizyn
 * @Date: 2021-03-11 14:11:45
 * @LastEditTime: 2021-03-18 15:00:10
 */
#include <bits/stdc++.h>
#include "SeqList.h"

void showMenu() {
  printf("菜单");
}

void CreateList(SeqList &pList) {
  for (int i = 1; i <= 60; ++i) {
    InsertBefore(pList, i, i);
  }
  PrintList(pList);
}

int main() {
  int choice = 0;
  SeqList list;
  do {
    showMenu();
    printf("\n\t请选择：");
    while (!scanf("%d", &choice) || choice < 0 || choice > 16) {
      printf("\n\t输入无效，请重新输入：");
      fflush(stdin);
    }
    switch (choice) {
      case 1:
        printf("\n\t您选择了%d.....\n", choice);
        CreateList(list);
        break;
      case 2:
        break;
      case 3:
        break;
      case 16:
        printf("谢谢使用\n");
        break;
      default:
        break;
    }
    fflush(stdin);
    printf("\n\t按任意键返回主菜单。");
    getchar();
  } while (choice != 16);
  return 0;
}