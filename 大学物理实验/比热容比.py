'''
@Author: Kaizyn
@Date: 2020-03-03 20:27:32
@LastEditTime: 2020-06-16 20:51:25
'''
# coding = utf-8

import math

if __name__ == "__main__":
  p0 = float(input('P0:'))
  r = []
  n = 0
  while True :
    p1, p2 = map(float, input('delta p1, p2:').split())
    if p1 == 0 and p2 == 0 : break
    n += 1
    p1 = p0+p1*50
    p2 = p0+p2*50
    r.append(math.log10(p1/p0)/math.log10(p1/p2))
    print('p1={:.0f},p2={:.0f},r={}'.format(p1, p2, r[n-1]))
  
  rr = sum(r)/n
  ur = math.sqrt(sum([pow(i-rr, 2) for i in r])/(n-1))
  er = ur/rr*100
  print('rr={},Ur={},Er={}%'.format(rr, ur, er))
'''
108000
108.6 26.4
107.1 26.1
105.9 25.7
108.8 26.1
102.3 25.7
108.5 26.1
106.9 26.3
0 0
'''