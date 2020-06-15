'''
@Author: Kaizyn
@Date: 2020-06-15 20:13:39
@LastEditTime: 2020-06-15 22:11:19
'''
# coding = utf-8

import threading

x = []
q = []
p = []

def my_find(num) :
  for i in range(len(x)) :
    if x[i] == num :
      return i
  return -1

def my_fun(l, r) :
  for i in range(l, r) :
    p[i] = my_find(q[i])

if __name__ == "__main__":
  thread_count = 2
  x = list(map(int, input('输入原始数据:').split()))
  q = list(map(int, input('输入要查询的数据:').split()))
  n = len(q)
  p = [-1 for i in range(n)]
  t = n//thread_count
  threads = []
  for i in range(thread_count) :
    l = i*t
    r = max(l+t, n)
    threads.append(threading.Thread(target=my_fun, args=[l, r]))
    threads[i].start()
  for i in range(thread_count) :
    threads[i].join()
  print('查询的数据的位置分别为:', ' '.join(map(str, p)))