'''
@Author: Kaizyn
@Date: 2020-06-11 13:33:28
@LastEditTime: 2020-06-11 14:20:12
'''
# coding = utf-8

import os
import turtle as t

def sq(c):
  t.pu()
  t.goto(-c//2, c//2)
  t.pd()
  for i in range(4):
    t.fd(c)
    t.right(90)

def switch():
  if t.isdown():
    t.pu()
  else :
    t.pd()

def right():
  t.seth(0)
  t.fd(10)

def up():
  t.seth(90)
  t.fd(10)

def left():
  t.seth(180)
  t.fd(10)

def down():
  t.seth(270)
  t.fd(10)

if __name__ == "__main__":
  # t.setup(width = 500, height = 500, 5, 5)
  # t.setup(500, 500, 5, 5)
  '''
  for c in range(100, 501, 100):
    t.pensize(c//20)
    t.pencolor(c/500, 1-c/500, 0.1)
    sq(c)
  '''
  t.shape('turtle')
  t.color('darkgreen')
  t.pu()
  '''
  screen = t.getscreen()
  screen.onkey(right, 'Right')
  screen.onkey(up, 'Up')
  screen.onkey(left, 'Left')
  screen.onkey(down, 'Down')
  screen.onkey(switch, 'Space')
  screen.listen()
  '''

  # os.system('pause')