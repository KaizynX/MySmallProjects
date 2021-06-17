'''
Author: Kaizyn
Date: 2021-06-15 11:10:23
LastEditTime: 2021-06-17 18:24:32
'''
# coding = utf-8

import re

key_words = ["const", "int", "void", "if", "else", "while", "continue", "break"]
operator = ["=", "+", "-", "%", "*", "/", "!", "<", ">", "<=", ">=", "==", "!=", "&&", "||"]
delimiter = ",;(){}[]"

def Ident(s) :
  i = re.match("[a-zA-Z_]\w*", s)
  return i and i.span()[1] == len(s)

def IntConst(s) :
  i = re.match("([1-9]\d*)|(0[0-7]+)|(0[xX][0-9a-fA-F]+)|0", s)
  return i and i.span()[1] == len(s)

if __name__ == '__main__' :
  # file_name = input('输入文件名：')
  file_name = "test.sy"
  file = open(file_name, mode='r')
  s = file.readlines()
  
  s = ''.join(s)
  while ~s.find('/*') or ~s.find('//') :
    i1 = s.find('/*')
    i2 = s.find('//')
    # 块注释
    if i2 == -1 or i1 < i2 :
      j1 = s.find('*/', i1+2)
      if j1 == -1 :
        print("Error:块注释不匹配 at line ", s[:i1].count('\n'))
        break
      else :
        # 替换成空格防止行号改变
        result, number = re.subn('[^\n]', ' ', s[i1:j1+2])
        s = s[:i1]+result+s[j1+2:]
    # 行注释
    else :
      j2 = s.find('\n', i2)
      s = s[:i2]+s[j2:]

  # 词法分析
  s = s.split('\n')
  for line in range(len(s)) :
    str = s[line]
    i = 0
    while i < len(str) :
      if re.search("[\W_]", str[i:]) :
        j = i+re.search("[\W_]", str[i:]).span()[0]
      else :
        j = len(str)
      word = str[i:j]

      if len(word) == 0 or re.match('\s+', word) :
        pass
      elif word in key_words :
        print("<关键词,", word, ">")
      elif Ident(word) :
        print("<标识符,", word, ">")
      elif IntConst(word) :
        print("<数值常量,", word, ">")
      else :
        print("Error:未知符号 at line", line+1, "char", i, ":", word)

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
          print("Error:未知符号 at line", line+1, "char", j, ":", str[j])
        j += 1

      i = j
      
  print("结束")