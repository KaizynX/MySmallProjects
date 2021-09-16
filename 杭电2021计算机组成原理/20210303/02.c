/*
 * @Author: Kaizyn
 * @Date: 2021-03-05 14:40:20
 * @LastEditTime: 2021-03-05 14:40:23
 */
#include <stdio.h>

int main()

{

int a = 1;

int b = 2147483647;

int d = -1;

int e = -2147483648;

int c = a+b;

int f = e+d;

printf("c=a+b=%d+%d=%d \n",a,b,c);

printf("f=e+d=%d+%d=%d \n",d,e,f);

return 0;

}