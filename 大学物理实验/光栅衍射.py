'''
Author: Kaizyn
Date: 2020-10-13 23:12:49
LastEditTime: 2020-11-04 23:16:47
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
    all_t = []
    all_l = []
    all_d = []
    for i in range(6) :
        l = float(input())
        s = input()
        s = s.replace('°', ' ')
        s = s.replace('′', ' ')
        s = list(map(int, s.split()))
        t = []
        for i in range(4) :
            t.append(s[i*2]*60+s[i*2+1])
        dt1 = abs(t[0]-t[1])/2
        dt2 = abs(t[2]-t[3])/2
        dt = (dt1+dt2)/2
        print_theta(dt1)
        print_theta(dt2)
        print_theta(dt)
        dt = dt/60/180*math.pi
        d = l/math.sin(dt)
        print(d)
        all_l.append(l)
        all_t.append(dt)
        all_d.append(d)
    print(all_d[0], all_d[1], all_d[2])
    ad = (all_d[0]+all_d[1]+all_d[2])/3
    dt = 2/60/180*math.pi
    dd = 0
    for i in range(3) :
        dd += math.cos(all_t[i])/(math.sin(all_t[i])**2)
    dd = dd*all_l[0]*dt/3
    print('d=', ad, '+-', dd)
    for i in range(3, 6) :
        al = ad*math.sin(all_t[i])
        dl = dd*math.sin(all_t[i])
        print(al, '+-', dl, ' ', abs(al-all_l[i])/all_l[i]*100, '%')
    print('光栅角色散率', abs(all_t[4]-all_t[5])/abs(all_l[4]-all_l[5]))
    for i in range(4, 6) :
        print('光栅角色散率', 1/all_d[i]/math.cos(all_t[i]))
        print('光栅分辨本领', all_l[4]/abs(all_l[4]-all_l[5]))
