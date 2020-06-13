'''
@Author: Kaizyn
@Date: 2020-03-03 20:27:32
@LastEditTime: 2020-03-27 11:37:22
'''
# coding = utf-8

import math

m1 = float(input('输入m1:'))
m2 = float(input('输入m2:'))
x = float(input('输入x:'))
n = int(input('输入测量次数:'))
t10 = [float(i) for i in input('输入%d组t10(空格分隔):' % (n)).split()]
t2 = [float(i) for i in input('输入%d组t2(空格分隔):' % (n)).split()]
t1 = [float(i) for i in input('输入%d组t1(空格分隔):' % (n)).split()]

v10 = [x/t for t in t10]
v2 = [x/t for t in t2]
v1 = [x/t for t in t1]
m1v10 = [m1*v for v in v10]
m1v1_m2v2 = [m1*v1[i]+m2*v2[i] for i in range(n)]
e = [(v2[i]-v1[i])/(v10[i]-0) for i in range(n)]
R = [(m1+m2*pow(ee, 2))/(m1+m2) for ee in e]
E = [100*abs(m1v1_m2v2[i]-m1v10[i])/m1v10[i] for i in range(n)]

dot_num = 2 # 保留小数位数
v10 = [round(i*100, dot_num) for i in v10]
v2 = [round(i*100, dot_num) for i in v2]
v1 = [round(i*100, dot_num) for i in v1]
m1v10 = [round(i, dot_num) for i in m1v10]
m1v1_m2v2 = [round(i, dot_num) for i in m1v1_m2v2]
e = [round(i, dot_num) for i in e]
R = [round(i, dot_num) for i in R]
E = [round(i, dot_num) for i in E]

print('v10x10^-2: ', v10)
print('v2x10^-2: ', v2)
print('v1x10^-2: ', v1)
print('m1v10: ', m1v10)
print('m1v1_m2v2: ', m1v1_m2v2)
print('e: ', e)
print('R: ', R)
print('E%: ', E)