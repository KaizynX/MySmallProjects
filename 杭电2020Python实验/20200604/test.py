# coding = utf-8

import tkinter as tk
import time

def fun():
  print("pressed")

'''
def get_time():
  timestr = time.strftime("%H:%M:%S")
  # timelb.config(text=timestr)
  var.set(timestr)
  root.after(1000,get_time)
'''
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
  root.title("title")
  root.geometry("480x360")
  root.config(bg='black')
  '''
  label = tk.Label(root, text="label")
  button = tk.Button(root, text="button", command=fun)
  lb2 = tk.Label(root, bitmap="error", cursor="cross")
  label.pack()
  button.pack()
  lb2.pack()
  '''
  enstr = tk.StringVar()
  tk.Entry(root, textvariable=enstr, fg='black', font=('仿宋', 32), justify=tk.RIGHT,\
      width=20).grid(row=0, column=0, rowspan=1, columnspan=4)
  tk.Button(root, text="1", width=5, height=3, command=lambda:f('1')).grid(row=1, column=0)
  tk.Button(root, text="2", width=5, height=3, command=lambda:f('2')).grid(row=1, column=1)
  tk.Button(root, text="3", width=5, height=3, command=lambda:f('3')).grid(row=1, column=2)
  tk.Button(root, text="+", width=5, height=3, command=lambda:f('+')).grid(row=1, column=3)
  tk.Button(root, text="4", width=5, height=3, command=lambda:f('4')).grid(row=2, column=0)
  tk.Button(root, text="5", width=5, height=3, command=lambda:f('5')).grid(row=2, column=1)
  tk.Button(root, text="6", width=5, height=3, command=lambda:f('6')).grid(row=2, column=2)
  tk.Button(root, text="-", width=5, height=3, command=lambda:f('-')).grid(row=2, column=3)
  tk.Button(root, text="7", width=5, height=3, command=lambda:f('7')).grid(row=3, column=0)
  tk.Button(root, text="8", width=5, height=3, command=lambda:f('8')).grid(row=3, column=1)
  tk.Button(root, text="9", width=5, height=3, command=lambda:f('9')).grid(row=3, column=2)
  tk.Button(root, text="*", width=5, height=3, command=lambda:f('*')).grid(row=3, column=3)
  tk.Button(root, text="0", width=5, height=3, command=lambda:f('0')).grid(row=4, column=0)
  tk.Button(root, text=".", width=5, height=3, command=lambda:f('.')).grid(row=4, column=1)
  tk.Button(root, text="=", width=5, height=3, command=lambda:f('=')).grid(row=4, column=2)
  tk.Button(root, text="/", width=5, height=3, command=lambda:f('/')).grid(row=4, column=3)
  '''
  var = tk.StringVar()
  timelb = tk.Label(root, textvariable=var, fg='white', font=("黑体", 36))
  timelb.pack()
  get_time()
  '''
  '''
  var1 = tk.StringVar()
  var2 = tk.StringVar()
  tk.Label(root, text="账号").grid(row=0, sticky=W)
  tk.Label(root, text="密码").grid(row=1, sticky=W)
  en1 = tk.Entry(root, textvariable=var1)
  en2 = tk.Entry(root, textvariable=var2, show='*')
  var1.set('admin')
  en2.focus_set()
  # ...
  '''
  root.mainloop()