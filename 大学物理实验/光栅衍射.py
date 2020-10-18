'''
Author: Kaizyn
Date: 2020-10-13 23:12:49
LastEditTime: 2020-10-13 23:35:22
'''
# coding = utf-8

'''
546.1
9°37′	28°22′	189°37′	208°22′
546.1
9°36′	28°24′	189°36′	208°24′
546.1
9°37′	28°23′	189°37′	208°23′
435.8
11°30′	26°58′	191°30′	206°59′
577.0
9°05′	28°55′	189°05′	208°55′
579.1
9°02′	28°58′	189°02′	208°58′
'''

import math

def print_theta (x) :
    x = math.ceil(x)
    print('%d°%d′ ' % (x/60, x%60), end='')

if __name__ == "__main__":
    while True :
        l = float(input())
        s = input()
        s = s.replace('°', ' ')
        s = s.replace('′', ' ')
        s = list(map(int, s.split()))
        t = [0 for i in range(4)]
        for i in range(4) :
            t[i] = s[i*2]*60+s[i*2+1]
        print(s)
        print(t)
        dt1 = abs(t[0]-t[1])/2
        dt2 = abs(t[2]-t[3])/2
        dt = (dt1+dt2)/2
        d = l/math.sin(dt/120/math.pi)
        print_theta(dt1)
        print_theta(dt2)
        print_theta(dt)
        print(d)
