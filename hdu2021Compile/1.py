'''
Author: Kaizyn
Date: 2021-06-15 11:10:23
LastEditTime: 2021-06-15 23:41:50
'''
# coding = utf-8

import re

key_words = ["const", "int", "void", "if", "else", "while", "continue", "break"]
operator = ["=", "+", "-", "%", "*", "/", "!", "<", ">", "<=", ">=", "==", "!=", "&&", "||"]
delimiter = ",;(){}[]"

def Ident(s) :
  i = re.match("[a-zA-Z_]\w*", s)
  # return i and i.span()[1] == len(s)
  return i

def IntConst(s) :
  i = re.match("([1-9]\d*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*)", s)
  # return i and i.span()[1] == len(s)
  return i

if __name__ == '__main__' :
  # file_name = input('输入文件名：')
  file_name = "data.txt"
  file = open(file_name, mode='r')
  s = file.readlines()
  # 行注释
  for i in range(len(s)) :
    p = s[i].find('//')
    if p != -1 : s[i] = s[i][:p]+'\n'
  # print('行注释后',s)
  # 块注释
  s = ''.join(s)
  # print('块注释前', s)
  while s.find('/*') != -1 :
    head = s.find('/*')
    tail = s.find('*/', head+2)
    if tail == -1 :
      print("Error:块注释不匹配 at line ", s[:head].count('\n'))
      break
    else :
      # 替换成空格防止行号改变
      result, number = re.subn('[^\n]', ' ', s[head:tail+2])
      s = s[:head]+result+s[tail+2:]
  s = ''.join(s).split('\n')
  # print('块注释后','\n'.join(s))
  # print(s)
  # 词法分析
  for line in range(len(s)) :
    str = s[line]
    i = 0
    while i < len(str) :
      # print("begin:", i)
      if re.search("[\W_]", str[i:]) :
        j = i+re.search("[\W_]", str[i:]).span()[0]
      else :
        j = len(str)
      word = str[i:j]
      # print(i, word, '$')

      if len(word) == 0 or re.match('\s+', word) :
        pass
      elif word in key_words :
        print("<关键词,", word, ">")
      elif Ident(word) :
        print("<标识符,", word, ">")
      elif IntConst(word) :
        print("<数值常量,", word, ">")
      else :
        print("Error:未知符号 at line", line+1, ":", word)

      if j < len(str) :
        if re.match('\s+', str[j]) :
          pass
        elif j+1 < len(str) and str[j:j+2] in operator:
          print("<运算符,", str[j:j+2], ">")
          j += 1
        elif str[j] in operator :
          print("<运算符,", str[j], ">")
        elif str[j] in delimiter :
          print("<分隔符,", str[j], ">")
        else :
          print("Error:未知符号 at line", line+1, ":", str[j])
        j += 1

      i = j
      
  print("结束")