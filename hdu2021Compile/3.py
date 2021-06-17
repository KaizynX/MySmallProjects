'''
Author: Kaizyn
Date: 2021-05-25 10:12:54
LastEditTime: 2021-06-17 16:11:22
'''
# coding = utf-8

import re

s = ""
message = []

def Ident(p):
  i = re.match("[a-zA-Z_]\w*", s[p:])
  if i:
    p += i.span()[1]
    return p
  else:
    print("Error:in i, at {}'th char".format(p))
    # message.append("Error:in i, at {}'th char".format(p))
    return -1

def E(p):
  print("E->TE'")
  p = T(p)
  if p == -1: return -1
  p = E_(p)
  if p == -1: return -1
  # message.append("E->TE'")
  return p

def E_(p):
  tmp = p
  print("E'->ATE'")
  p = A(p)
  if ~p:
    p = T(p)
    if ~p:
      p = E_(p)
      if ~p:
        # message.append("E'->ATE'")
        return p
  print("E'->ε")
  # message.append("E'->ε")
  return tmp
  

def T(p):
  print("T->FT'")
  p = F(p)
  if p == -1 : return -1
  p = T_(p)
  if p == -1 : return -1
  # message.append("T->FT'")
  return p

def T_(p):
  tmp = p
  print("T'->MFT'")
  p = M(p)
  if ~p:
    p = F(p)
    if ~p:
      p = T_(p)
      if ~p:
        # message.append("T'->MFT'")
        return p
  print("T'->ε")
  # message.append("T'->ε")
  return tmp

def F(p):
  global s
  tmp = p
  print("F->(E)")
  if p < len(s) and s[p] == '(' :
    p = E(p+1)
    if ~p and p < len(s) and s[p] == ')' :
      # message.append("F->(E)")
      return p+1
  p = Ident(tmp)
  if p == -1 : return -1
  print("F->i")
  # message.append("F->i")
  return p

def A(p):
  global s
  if p < len(s):
    if s[p] == '+':
      print("A->+")
      # message.append("A->+")
    if s[p] == '-':
      print("A->-")
      # message.append("A->-")
    return p+1
  print("Error:in A, at {}'th char".format(p))
  # message.append("Error:in A, at {}'th char".format(p))
  return -1

def M(p):
  global s
  if p < len(s):
    if s[p] == '*':
      print("M->*")
      # message.append("M->*")
    if s[p] == '/':
      print("M->/")
      # message.append("M->/")
    return p+1
  print("Error:in M, at {}'th char".format(p))
  # message.append("Error:in M, at {}'th char".format(p))
  return -1

if __name__ == "__main__":
  s = input()
  message.clear()
  p = E(0)
  while len(message) :
    print(message[-1])
    message.pop()
  if len(s) != p : print("failed")
  else : print("success")