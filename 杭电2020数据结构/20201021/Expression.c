/*
 * @Author: Kaizyn
 * @Date: 2020-10-26 14:04:59
 * @LastEditTime: 2020-10-26 19:04:14
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 数据范围 */
#define N 100

char priority[7][7]={ 
  {'>','>','<','<','<','>','>'},
  {'>','>','<','<','<','>','>'},
  {'>','>','>','>','<','>','>'},
  {'>','>','>','>','<','>','>'},
  {'<','<','<','<','<','=','0'}, // 此行"("=")"表示左右括号相遇，括号内运算已完成 
  {'>','>','>','>','0','>','>'}, // "=" 表示整个表达式求值完毕 
  {'<','<','<','<','<','0','='}  // "0"表示不可能出现这种情况 ( 语法错误 ) 
};

//Precede 用于判断运算符栈栈顶运算符 a1 与读入运算符 a2 之间的优先关系函数 
char Procede(char a, char b) {   // 建立 pre[][] 到 运算符间的映射关系 
  int i, j;
  switch(a) {
    case '+': i = 0; break;
    case '-': i = 1; break;
    case '*': i = 2; break;
    case '/': i = 3; break;
    case '(': i = 4; break;
    case ')': i = 5; break;
    case '#': i = 6; break; // # 是表达式的结束符 
  }
  switch(b) {
    case '+': j = 0; break;
    case '-': j = 1; break;
    case '*': j = 2; break;
    case '/': j = 3; break;
    case '(': j = 4; break;
    case ')': j = 5; break;
    case '#': j = 6; break;
  }
  return priority[i][j];
}
   
int Operate(int m, int n, char x){
  if (x == '+') {
    return m+n;
  } else if (x == '-') {
    return n-m;
  } else if (x == '*') {
    return m*n;
  } else {
    if (m == 0) {
      puts("ERROR:divisor is zero");
      exit(0);
    }
    return n/m;
  }
}

int ExpressionEvaluation(char *s){
  static int StackInt[N];
  static char StackChar[N];
  int topInt = 0, topChar = 0;
  int len = strlen(s);
  s[len] = '#'; s[len+1] = '\0';
  char c = s[0], x;
  int k = 1, m, n;
  StackChar[++topChar] = '#';
  while (c != '#' || StackChar[topChar] != '#') {  //表达式未读完或者运算未完 
    if (c >= '0' && c <= '9') {
      int y = 0;
      while (c >= '0' && c <= '9') {  // 读入连续的数字 
        y = y*10+(c-'0');
        c = s[k++];
      }
      StackInt[++topInt] = y; // 把读进的数字入数字栈 
    } else {
      switch (Procede(StackChar[topChar], c)) {
        case '<':  //栈顶元素优先权低 
          StackChar[++topChar] = c;
          c = s[k++];
          break;
        case '=':
          --topChar;  // 脱括号 
          c = s[k++];  // 读入下一个字符 
          break;
        case '>':  //退栈并将运算结果入栈 
          x = StackChar[topChar--];
          m = StackInt[topInt--];
          n = StackInt[topInt--];
          StackInt[++topInt] = Operate(m,n,x);
          break;
      } 
    }
  }
  return StackInt[topInt];
}

int main() {
  static char s[N];
  while (~scanf("%s", s)) {
    printf("%d\n", ExpressionEvaluation(s));
  }
  return 0;
}
/*
8

1+2+3+4

88-1*5

1024/4*8

1024/(4*8)

(20+2)*(6/2)

3-3-3

2*(6+2*(3+6*(6+6)))

(((6+6)*6+3)*2+6)*2

8/(9-9)
*/