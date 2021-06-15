'''
Author: Kaizyn
Date: 2021-06-15 11:10:23
LastEditTime: 2021-06-15 11:25:00
'''
# coding = utf-8

import re

def Ident(s):
  i = re.match("[a-zA-Z_]\w*", s)
  if i : return i.span()[1]
  return -1

if __name__ == '__main__' :
  file_name = input('输入文件名：')
  file = open(file_name, mode='r')
  s = file.readlines()
  # 行注释
  for line in s :
    p = line.find('//')
    if p != -1 : line = line[:p]
  # 块注释
  s = ' '.join(s)
  while s.find('/*') != -1 :
    head = s.find('/*')
    tail = s.find('*/', head+2)
    if tail == -1 :
      print("错误：块注释不匹配")
      break
    else :
      s = s[:head]+s[tail+2:]
  # 词法分析
  pass