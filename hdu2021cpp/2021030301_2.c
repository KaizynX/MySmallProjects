/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 16:42:40
 * @LastEditTime: 2021-03-04 16:46:43
 */
#include <stdio.h>
#include <stdlib.h>

#define N 23333

int n;
int a[N];

int cmp(const void *a, const void *b)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", a+i);
  qsort(a, n, sizeof(int), cmp);
  for (int i = 0; i < n; ++i) {
    printf("%d", a[i]);
    if (i == n-1) printf("\n");
    else printf("->");
  }
  for (int i = 0; i < n/2; ++i) {
    int b = a[i];
    a[i] = a[n-i-1];
    a[n-i-1] = b;
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", a[i]);
    if (i == n-1) printf("\n");
    else printf("->");
  }
  return 0;
}