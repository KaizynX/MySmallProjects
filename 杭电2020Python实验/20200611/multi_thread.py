'''
@Author: Kaizyn
@Date: 2020-06-11 14:20:46
@LastEditTime: 2020-06-11 14:29:06
'''
# coding = utf-8

import os
import time
import threading

def task(t):
  for i in range(10):
    time.sleep(t)
    print(str(t), end='')


if __name__ == "__main__":
  th1 = threading.Thread(target=lambda : task(1))
  th1.start()
  th2 = threading.Thread(target=lambda : task(2))
  th2.start()
  # os.system('pause')