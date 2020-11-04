/*
 * @Author: Kaizyn
 * @Date: 2020-10-28 17:56:41
 * @LastEditTime: 2020-10-28 19:21:33
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int page_length,
    page_wedth,
    left_margin,
    heading_length,
    footing_length,
    starting_page_number;
char in_file_name[20], out_file_name[20];

typedef struct Formator {
  char buf[200];
  int len, line, page;
} Formator;

/* 初始化 */
void FormatorInit(Formator *formator) {
  memset(formator->buf, ' ', left_margin);
  formator->buf[left_margin] = '\0';
  formator->len = left_margin;
  formator->line = 1;
  formator->page = starting_page_number;
}

/* 另起一页 */
void FormatorNewPage(Formator *formator) {
  // 如果所要求页底空行数不少于3,则将页号印在页底空行中第二行的中间位置
  if (page_length-formator->line+1 >= 3) {
    puts("");
    for (int i = 0; i < (page_wedth-3)/2; ++i) putchar(' ');
    printf("%3d\n", formator->page);
  }
  for ( ; formator->line <= page_length; ++formator->line) puts("");
  formator->line = 1;
  formator->page++;
}

/* 输出一行 */
void FormatorPrint(Formator *formator) {
  // 每页页底空行
  if (formator->line+footing_length > page_length) FormatorNewPage(formator);
  // 每页页顶空行
  for ( ; formator->line <= heading_length; ++formator->line) puts("");
  puts(formator->buf);
  memset(formator->buf, ' ', left_margin);
  formator->buf[left_margin] = '\0';
  formator->len = left_margin;
  formator->line++;
}

/* 输入一个单词 */
void FormatorAdd(Formator *formator, char *word) {
  static const char *space = " ";
  int word_len = strlen(word);
  // 另起一行
  if (formator->len+1+word_len > page_wedth) FormatorPrint(formator);
  if (formator->len) strcat(formator->buf, space); // 加上空格
  strcat(formator->buf, word);                   // 加上单词
  formator->len += word_len;                     // 更新长度
}

int main() {
  Formator formator;
  static char word[200];

  printf("请输入页长："); scanf("%d", &page_length);
  printf("请输入页宽："); scanf("%d", &page_wedth);
  printf("请输入左空白："); scanf("%d", &left_margin);
  printf("请输入头长："); scanf("%d", &heading_length);
  printf("请输入脚长："); scanf("%d", &footing_length);
  printf("请输入起始页号："); scanf("%d", &starting_page_number);
  printf("请输入输入文件名："); scanf("%s", in_file_name);
  printf("请输入输出文件名："); scanf("%s", out_file_name);
  freopen(in_file_name, "r", stdin);
  freopen(out_file_name, "w", stdout);

  FormatorInit(&formator);
  while (~scanf("%s", word)) FormatorAdd(&formator, word);
  FormatorPrint(&formator);
  FormatorNewPage(&formator);
  return 0;
}
/*
10
50
2
1
3
1
testdata.txt
ans.txt
*/