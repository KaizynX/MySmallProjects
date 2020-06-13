'''
@Author: Kaizyn
@Date: 2020-03-03 20:27:32
@LastEditTime: 2020-03-27 10:50:37
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
zero = float(input('输入零点读数:'))
yiqi = float(input('输入仪器误差:'))
'''
x = input('输入%d组测量值(空格分隔):' % (n)).split()
dot_num = get_dot_num(x[0])
x = [float(i) for i in x]
'''
x = [float(i) for i in input('输入%d组测量值(空格分隔):' % (n)).split()]

ave = sum(x)/n
ave = round(ave, 3) # set the dot_num
ua = math.sqrt(sum([pow(i-ave, 2) for i in x])/n/(n-1))
ub = yiqi/math.sqrt(3)
ux = math.sqrt(pow(ua, 2)+pow(ub, 2))
E = ux/(ave-zero)

print('平均值: ', ave)
print('修正后平均值: ', ave-zero)
print('A类不确定度UA: ', ua)
print('B类不确定度UB: ', ub)
print('合成不确定度U: ', ux)
print('结果表达式: %f+-%f' % (ave-zero, ux))
print('相对不确定度E: ', E*100)

'''
dot_num = 2 # 有效数字位数
n = int(input('输入测量次数:'))
zero = float(input('输入零点读数:'))
yiqi = float(input('输入仪器误差:'))
x = [float(i) for i in input('输入%d组测量值(空格分隔):' % (n)).split()]

ave = sum(x)/n
ua = math.sqrt(sum([pow(i-ave, 2) for i in x])/n/(n-1))
ub = yiqi/math.sqrt(3)
ux = math.sqrt(pow(ua, 2)+pow(ub, 2))
E = ux/(ave-zero)

print('平均值: ', round(ave, dot_num))
print('修正后平均值: ', round(ave-zero, dot_num))
print('A类不确定度UA: ', round(ua, dot_num))
print('B类不确定度UB: ', round(ub, dot_num))
print('合成不确定度U: ', round(ux, dot_num))
print('结果表达式: %f+-%f' % (round(ave-zero, dot_num), round(ux, dot_num)))
print('相对不确定度E: ', round(E*100, dot_num))
'''