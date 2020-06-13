'''
@Author: Kaizyn
@Date: 2020-03-03 20:27:32
@LastEditTime: 2020-03-20 14:45:20
'''
# coding = utf-8

import math

def get_dot_num(num) :
    i = 0
    j = len(num)-1
    while i <= j and (num[i] == '0' or num[i] == '.') :
        i += 1
    while i <= j and num[j] == '0' :
        j -= 1
    return j-i+1

n = int(input('输入测量次数:'))
yiqi = float(input('输入仪器误差:'))
'''
x = input('输入%d组测量值(空格分隔):' % (n)).split()
dot_num = get_dot_num(x[0])
x = [float(i) for i in x]
'''
l = [float(i) for i in input('输入%d组左读数(空格分隔):' % (n)).split()]
r = [float(i) for i in input('输入%d组右读数(空格分隔):' % (n)).split()]
x = [r[i]-l[i] for i in range(n)]

ave = sum(x)/n
ave = round(ave, 3) # set the dot_num
print([round(i, 3) for i in x])
lave = round(sum(l)/n, 3)
rave = round(sum(r)/n, 3)
ua = math.sqrt(sum([pow(i-ave, 2) for i in x])/n/(n-1))
ub = yiqi/math.sqrt(3)
ux = math.sqrt(pow(ua, 2)+pow(ub, 2))
E = ux/ave

print('左读数平均值: ', lave)
print('左读数平均值: ', rave)
print('平均值: ', ave)
print('A类不确定度UA: ', ua)
print('B类不确定度UB: ', ub)
print('合成不确定度U: ', ux)
print('结果表达式: %f+-%f' % (ave, ux))
print('相对不确定度E: ', E*100)