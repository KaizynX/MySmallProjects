'''
@Author: Kaizyn
@Date: 2020-06-15 17:11:19
@LastEditTime: 2020-06-15 19:57:38
'''
# coding = utf-8

import os
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from pylab import mpl

if __name__ == "__main__" :
  # 读入文件
  file_name = open("name.txt", "rt", encoding='UTF-8')
  lists_name = [name.rstrip('\n') for name in file_name.readlines()[1:]]
  file_name.close()

  # 题1
  n = 1880
  dic = {}
  for name in lists_name :
    # 狗屎数据有空行
    if len(name) > 0 :
      dic[name[0]] = dic.get(name[0], 0)+1
  lis = list(dic.items())
  lis.sort(key=lambda k : k[1], reverse=True)
  # 标签
  labels = [lis[i][0] for i in range(5)]
  labels.append('其他')
  # 占比
  sizes = [lis[i][1]/n*100 for i in range(5)]
  sizes.append(100.0)
  for i in range(5) : sizes[5] -= sizes[i]
  # 分离
  explode = [0 for i in range(5)]
  explode.append(0.05)
  # 设置中文字体
  mpl.rcParams['font.sans-serif']=['SimHei']
  fig = plt.figure()
  ax = fig.gca()
  # 1位小数
  ax.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%')
  plt.title('前5大姓氏及其他姓氏')
  plt.show()

  # 题2
  dic = {}
  for name in lists_name :
    for i in range(1, len(name)) :
      dic[name[i]] = dic.get(name[i], 0)+1
  lis = list(dic.items())
  lis.sort(key=lambda k : k[1], reverse=True)
  x_data = [lis[i][0] for i in range(10)]
  y_data = [lis[i][1] for i in range(10)]
  plt.bar(x=x_data, height=y_data)
  plt.xlabel('字')
  plt.ylabel('出现次数')
  plt.title('名字中前10个最常用字')
  plt.show()

  # 题4
  dic2 = {}
  x_data = [lis[i][0] for i in range(10)]
  y_data = []
  for grade in range(0, 4) :
    # 清空字典
    for i in range(10) :
      dic2[lis[i][0]] = 0
    names = lists_name[grade*470:grade*470+470]
    for name in names :
      for i in range(1, len(name)) :
        if name[i] in dic2 :
          dic2[name[i]] += 1
    y_data = list(dic2.values())
    plt.plot(x_data, y_data, label=str(2015+grade))
  plt.legend()
  plt.show()

  # 题3
  for grade in range(0, 4) :
    # represent 2015+grade
    names = lists_name[grade*470:grade*470+470]
    dic = {}
    for name in names :
      # 狗屎数据有空行
      if len(name) > 0 :
        dic[name[0]] = dic.get(name[0], 0)+1
    lis = list(dic.items())
    lis.sort(key=lambda k : k[1], reverse=True)
    print(str(2015+grade)+'级： ', end='')
    for i in range(5) :
      print(lis[i][0], end=' ')
    print()
  
  # 题5
  '''
  我要这名单有何用?
  '''
  cnt = 0
  for name in lists_name :
    if len(name) > 0 :
      cnt += 1
  print('已知1880个同学中，共有', 1880-cnt, '个无名氏')
  # os.system('pause')