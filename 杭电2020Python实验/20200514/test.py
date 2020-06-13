# coding = utf-8

import os

if __name__ == "__main__" :
  file1 = open("text.txt", "rt")
  # file1 = open("D:\\tmp\\pythonclass\\text.txt", "rt")
  # file1 = open("..\\碰撞.txt", "rt")
  # file1 = open("D:\\tmp\\pythonclass\\碰撞.txt", "rt")
  '''
  text = file1.read()
  file1.close()
  print(text)
  os.system('pause')
  '''
  x = file1.readline()
  print(x)
  x = file1.readlines(2)
  print(x)
  file1.seek(0, 0)
  x = file1.readlines()
  print(x)
  