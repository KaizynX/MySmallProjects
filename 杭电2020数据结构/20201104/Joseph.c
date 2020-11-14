/*
 * @Author: Kaizyn
 * @Date: 2020-11-04 17:40:43
 * @LastEditTime: 2020-11-04 19:30:25
 */
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct List {
  ElemType e;
  struct List *pre, *nex;
} List, *LinkList;

void ListInit(LinkList *l) {
  *l = (LinkList)malloc(sizeof(List));
  if (!l) exit(0);
  (*l)->e = -1;
  (*l)->pre = (*l)->nex = *l;
}

void ListClear(LinkList *l) {
  if (!l) return;
  LinkList p = *l, t;
  do {
    t = p->nex;
    free(p);
    p = t;
  } while (p != *l);
}

LinkList ListFind(LinkList l, ElemType e) {
  if (!l) return NULL;
  LinkList p = l;
  do {
    if (p->e == e) return p;
    p = p->nex;
  } while (p != l);
  return NULL;
}

// 在 pre 前插入 cur
void ListInsert(LinkList *l, ElemType pre, ElemType cur) {
  LinkList p = ListFind(*l, pre);
  if (!p) {
    ListClear(l);
    ListInit(l);
    (*l)->e = cur;
    return;
  }
  LinkList u = (LinkList)malloc(sizeof(List));
  if (!u) exit(0);
  u->e = cur;
  u->pre = p;
  u->nex = p->nex;
  p->nex->pre = u;
  p->nex = u;
}

void ListErase(LinkList l, ElemType e) {
  LinkList p = ListFind(l, e);
  if (!p) return;
  p->pre->nex = p->nex;
  p->nex->pre = p->pre;
  free(p);
}

void Joseph(int n, int k) {
  LinkList l;
  ListInit(&l);
  for (int i = 1; i <= n; ++i) ListInsert(&l, i-1, i);

  for (int t = 1; t <= n; ++t) {
    for (int i = 1; i < k; ++i) l = l->nex;
    printf("第%d轮退出的人的编号是%d\n", t, l->e);
    l = l->nex;
    ListErase(l, l->pre->e);
  }
}

int main() {
  int n, k;
  printf("请输入总人数和退出的人所报数字：");
  scanf("%d %d", &n, &k);
  Joseph(n, k);
  return 0;
}