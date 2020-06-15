'''
@Author: Kaizyn
@Date: 2020-06-15 19:25:04
@LastEditTime: 2020-06-15 20:56:27
'''
# coding = utf-8

import tkinter as tk
import time

ls = []
def f(x):
  global ls
  if x == '=':
    if '+' in ls or '-' in ls or '*' in ls or '/' in ls:
      res = str(eval(enstr.get()))
      enstr.set(res)
      ls = [res]
    else:
      enstr.set('0')
      ls = ['0']
  else:
    ls.append(x)
    enstr.set(''.join(ls))

if __name__ == "__main__":
  root = tk.Tk()
  root.title("tk计算器")
  root.geometry("360x310")
  # root.config(bg='black')
  enstr = tk.StringVar()
  tk.Entry(root, textvariable=enstr, fg='black', font=('仿宋', 32), justify=tk.RIGHT,\
      width=16).grid(row=0, column=0, rowspan=1, columnspan=4)
  tk.Button(root, text="1", width=10, height=3, command=lambda:f('1')).grid(row=1, column=0)
  tk.Button(root, text="2", width=10, height=3, command=lambda:f('2')).grid(row=1, column=1)
  tk.Button(root, text="3", width=10, height=3, command=lambda:f('3')).grid(row=1, column=2)
  tk.Button(root, text="+", width=10, height=3, command=lambda:f('+')).grid(row=1, column=3)
  tk.Button(root, text="4", width=10, height=3, command=lambda:f('4')).grid(row=2, column=0)
  tk.Button(root, text="5", width=10, height=3, command=lambda:f('5')).grid(row=2, column=1)
  tk.Button(root, text="6", width=10, height=3, command=lambda:f('6')).grid(row=2, column=2)
  tk.Button(root, text="-", width=10, height=3, command=lambda:f('-')).grid(row=2, column=3)
  tk.Button(root, text="7", width=10, height=3, command=lambda:f('7')).grid(row=3, column=0)
  tk.Button(root, text="8", width=10, height=3, command=lambda:f('8')).grid(row=3, column=1)
  tk.Button(root, text="9", width=10, height=3, command=lambda:f('9')).grid(row=3, column=2)
  tk.Button(root, text="*", width=10, height=3, command=lambda:f('*')).grid(row=3, column=3)
  tk.Button(root, text="0", width=10, height=3, command=lambda:f('0')).grid(row=4, column=0)
  tk.Button(root, text=".", width=10, height=3, command=lambda:f('.')).grid(row=4, column=1)
  tk.Button(root, text="=", width=10, height=3, command=lambda:f('=')).grid(row=4, column=2)
  tk.Button(root, text="/", width=10, height=3, command=lambda:f('/')).grid(row=4, column=3)
  root.mainloop()