'''
Author: Kaizyn
Date: 2021-05-09 20:57:15
LastEditTime: 2021-05-09 21:13:24
'''
# coding = utf-8
from math import cos
from math import sin
from math import sqrt
from math import atan2
from math import pi

if __name__ == "__main__":
  while True :
    print("输入模式0j|1°")
    mode = int(input())
    if mode == 0 :
      a = float(input())
      b = float(input())
      print('{}∠{}°'.format(sqrt(a**2+b**2), atan2(b, a)/pi*180))
    elif mode == 1 :
      a = float(input())
      b = float(input())/180*pi
      print(a*cos(b), '+j', a*sin(b))
    else :
      break
