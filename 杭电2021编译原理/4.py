'''
Author: Kaizyn
Date: 2021-06-14 23:00:52
LastEditTime: 2021-06-17 16:17:05
'''
# coding = utf-8

import re

terminals = ['i','(','+','-','*','/',')','$']
non_terminals = ["E","E'","T","T'","F","A","M"]
parsing_table = [
  [["T", "E'"],["T", "E'"],[],[],[],[],[],[]],
  [[],[],["A", "T", "E'"],["A", "T", "E'"],[],[],[""],[""]],
  [["F", "T'"],["F", "T'"],[],[],[],[],[],[]],
  [[],[],[""],[""],["M", "F", "T'"],["M", "F", "T'"],[""],[""]],
  [["i"],["(", "E", ")"],[],[],[],[],[],[]],
  [[],[],["+"],["-"],[],[],[],[]],
  [[],[],[],[],["*"],["/"],[],[]]
]

def my_index(s) :
  if s[0] in terminals :
    i = terminals.index(s[0])
    if i > 0 : return i
  if re.match("[a-zA-Z_]\w*", s) : return 0
  print("错误：输入串没有匹配项")
  return -1

if __name__ == '__main__' :
  s = input()
  s += '$'
  stk = ["E"]
  while len(stk) :
    action = parsing_table[non_terminals.index(stk[-1])][my_index(s)]
    if len(action) == 0 :
      print("错误：没有匹配动作")
      break
    else :
      if len(action[0]) :
        print(stk[-1], "->", ''.join(action))
        stk.pop()
        stk += list(reversed(action))
      else :
        print(stk[-1], "->", "ε")
        stk.pop()
    if len(stk) and stk[-1] in terminals :
      if (stk[-1] == 'i') :
        i = re.match("[a-zA-Z_]\w*", s)
        if i :
          print("匹配i")
          s = s[i.span()[1]:]
          stk.pop()
          pass
        else :
          print("错误：终结符不匹配")
          break
      else :
        if (s[0] == stk[-1]) :
          print("匹配", s[0])
          s = s[1:]
          stk.pop()
        else :
          print("错误：终结符不匹配")
          break
  if len(stk) == 0 and s == '$' : print("匹配成功")
  else : print("匹配失败")