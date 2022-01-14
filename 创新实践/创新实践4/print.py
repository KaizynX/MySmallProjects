'''
Author: Kaizyn
Date: 2021-12-22 15:22:21
LastEditTime: 2022-01-14 15:29:55
'''
import turtle as t

def print1(file) : # 绘画过程
  t.title("路径绘制")#建立标题
  t.setup(800,600,0,0)#设置大小为800*600的窗口，python坐标原点默认设置在窗口中心
  pen=t.Turtle()#通过turtle()建立画笔pen,其默认位置是窗口原点
  pen.color("black")#设置画笔颜色
  pen.width(3)#设置画笔宽度为5
  pen.shape("turtle")#设置画笔形状为turtle
  pen.speed(10)#设置绘画速度为5
  pen.penup()
  for line in file:
    mesg = line.split()
    if mesg[0] == 0 and mesg[1] == 0 and mesg[2] == 0 :
      break
    x = float(mesg[0]) * 10
    y = float(mesg[1]) * 10
    m = int(mesg[2])
    pen.goto(x, y)#画笔移动
    if m < 0 :
      pen.pendown()#落笔
    elif m > 0 :
      pen.penup()#起笔

def print2(file) : # 空程显示为红色
  t.title("路径绘制")#建立标题
  t.setup(800,600,0,0)#设置大小为800*600的窗口，python坐标原点默认设置在窗口中心
  pen=t.Turtle()#通过turtle()建立画笔pen,其默认位置是窗口原点
  pen.color("red")#设置画笔颜色
  pen.width(3)#设置画笔宽度为5
  pen.shape("turtle")#设置画笔形状为turtle
  pen.speed(10)#设置绘画速度为5
  for line in file:
    mesg = line.split()
    if mesg[0] == 0 and mesg[1] == 0 and mesg[2] == 0 :
      break
    x = float(mesg[0]) * 10
    y = float(mesg[1]) * 10
    m = int(mesg[2])
    pen.goto(x, y)
    if m < 0 :
      pen.color("black")#设置画笔颜色
    elif m > 0 :
      pen.color("red")#设置画笔颜色


if __name__ == "__main__":
  filename = input("请输入文件名:")
  file = open(filename, "r")
  print1(file)
  # print2(file)

  t.mainloop()