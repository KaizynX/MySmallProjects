/*
 * @Author: Kaizyn
 * @Date: 2020-10-25 22:13:02
 * @LastEditTime: 2020-10-26 18:53:08
 */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #define DEBUG // 调试用

/* 状态码识别类型 */
typedef int Status;
/* 状态码 */
#define	TRUE		1			//真 
#define	FALSE		0			//假
#define YES			1			//是
#define NO          0			//否 
#define	OK			1			//通过
#define	ERROR		0			//错误
#define SUCCESS		1			//成功 
#define UNSUCCESS	0			//失败 
#define	INFEASIBLE	-1			//不可行

#ifndef _MATH_H_ 				//系统中已有此状态码定义，要避免冲突 
#define	OVERFLOW	-2			//堆栈上溢
#define UNDERFLOW	-3			//堆栈下溢
#endif 

#ifndef NULL
#define NULL ((void*)0)
#endif

/* 数据类型 */
typedef double CType;
typedef int PType;
/* 数据大小 */
#define N 100

struct LNode {
  CType c;
  PType p; // c*x^p
  struct LNode *next;
};
typedef struct LNode LNode;
typedef LNode* LinkList;

/* 链表初始化 */
Status ListInit(LinkList *L) {
  *L =  (LinkList)malloc(sizeof(LNode));
  if (!(*L)) exit(OVERFLOW);
  (*L)->next = NULL;
  return OK;
}

/* 在链表第i位插入(表头为0) */
Status ListInsert(LinkList L, int i, CType c, PType p) {
  if (!L || i <= 0) return ERROR;
  int cur = 0;
  while (L && cur < i-1) {
    L = L->next;
    ++cur;
  }
  if (!L || cur != i-1) return ERROR;
  LinkList s = (LinkList)malloc(sizeof(LNode));
  if (!s) exit(OVERFLOW);
  s->c = c;
  s->p = p;
  s->next = L->next;
  L->next = s;
  return OK;
}

/* 把字符串多项式转化为链表多项式 */
LinkList StringToList(char *s) {
  LinkList L;
  CType c, tag;
  PType p;
  ListInit(&L);
  int i = 0;
  do {
    // 系数符号
    if (*s == '-') {
      tag = -1;
      ++s; // 读入'-'
    } else {
      tag = 1;
      if (*s == '+') ++s; // 读入'+'
    }
    // 系数
    if (*s == 'x') {
      c = 1;
    } else {
      sscanf(s, "%lf", &c);
      while (*s == '.' || (*s >= '0' && *s <= '9')) ++s;
    }
    // 指数
    if (*s == 'x') {
      ++s; // 读入'x'
      if (*s == '^') {
        ++s; // 读入'^'
        sscanf(s, "%d", &p);
        if (*s == '-') ++s;
        while (*s >= '0' && *s <= '9') ++s;
      } else {
        p = 1;
      }
    } else {
      p = 0;
    }
    ListInsert(L, ++i, tag*c, p);
  } while (*s);
  return L;
}

/* 多项式加法 */
LinkList PolynomialAddition(LinkList lhs, LinkList rhs) {
  LinkList sum;
  int i = 0;
  ListInit(&sum);
  lhs = lhs->next;
  rhs = rhs->next;
  while (lhs || rhs) {
    if (lhs && rhs && lhs->p == rhs->p) {
      ListInsert(sum, ++i, lhs->c+rhs->c, lhs->p);
      lhs = lhs->next;
      rhs = rhs->next;
    } else if (!rhs || (lhs && lhs->p < rhs->p)) {
      ListInsert(sum, ++i, lhs->c, lhs->p);
      lhs = lhs->next;
    } else if (!lhs || (rhs && lhs->p > rhs->p)) {
      ListInsert(sum, ++i, rhs->c, rhs->p);
      rhs = rhs->next;
    }
  }
  return sum;
}

/* 多项式减法 */
LinkList PolynomialSubtraction(LinkList lhs, LinkList rhs) {
  LinkList sum;
  int i = 0;
  ListInit(&sum);
  lhs = lhs->next;
  rhs = rhs->next;
  while (lhs || rhs) {
    if (lhs && rhs && lhs->p == rhs->p) {
      ListInsert(sum, ++i, lhs->c-rhs->c, lhs->p);
      lhs = lhs->next;
      rhs = rhs->next;
    } else if (!rhs || (lhs && lhs->p < rhs->p)) {
      ListInsert(sum, ++i, lhs->c, lhs->p);
      lhs = lhs->next;
    } else if (!lhs || (rhs && lhs->p > rhs->p)) {
      ListInsert(sum, ++i, -rhs->c, rhs->p);
      rhs = rhs->next;
    }
  }
  return sum;
}

int LNodePrint(LNode L) {
  if (L.c == 0) return 0;
  putchar(L.c > 0 ? '+' : '-');
  if (!L.p || fabs(L.c) != 1) printf("%.1f", fabs(L.c)); // 保留小数位数
  if (L.p) putchar('x');
  if (L.p != 0 && L.p != 1) printf("^%d", L.p);
  return 1;
}

void ListPrint(LinkList L) {
  int not_zero = 0;
  L = L->next;
  while (L) {
    not_zero += LNodePrint(*L);
    L = L->next;
  }
  if (!not_zero) putchar('0');
  putchar('\n');
}

int ListReversePrint(LinkList L, int is_head) {
  if (!L) return 0;
  int not_zero = ListReversePrint(L->next, 0);
  if (is_head) {
    if (!not_zero) putchar('0');
    putchar('\n');
    return not_zero;
  } else {
    return not_zero+LNodePrint(*L);
  }
}

char CutString(char *str, char *lstr, char *rstr) {
  char add_or_minus;
  for (int i = 0, l = 0, flag = 0; str[i]; ++i) {
    if (str[i] == '(') {
      l = i+1;
      if (i) add_or_minus = str[i-1];
    } else if (str[i] == ')') {
      char *cur = flag ? rstr : lstr;
      flag = 1;
      strncpy(cur, str+l, i-l);
      cur[i-l] = '\0';
    }
  }
  return add_or_minus;
}

int main() {
  static char str[N], lstr[N], rstr[N];
  LinkList lhs, rhs, sum;
  while (~scanf("%s", str)) {
    char add_or_minus = CutString(str, lstr, rstr);
#ifdef DEBUG
    printf("lhs:%s\n", lstr);
    printf("rhs:%s\n", rstr);
#endif
    lhs = StringToList(lstr);
    rhs = StringToList(rstr);
#ifdef DEBUG
    printf("lhs:"); ListPrint(lhs);
    printf("rhs:"); ListPrint(rhs);
#endif
    sum = add_or_minus == '+' ?
        PolynomialAddition(lhs, rhs) :
        PolynomialSubtraction(lhs, rhs);
    ListReversePrint(sum, 1);
  }
  return 0;
}
/*
(2x+5x^8—3.1x^11)+(7-5x^8+11x^9)

(6x^-3-x+4.4x^2-1.2x^9)-(-6x^-3+5.4x^2-x^2+7.8x^15)

(1+x+x^2+x^3+x^4+x^5)+(-x^3-x^4)

(x+x^3)+(-x-x^3)

(x+x^100)+(x^100+x^200)

(x+x^2+x^3)+(0)
*/