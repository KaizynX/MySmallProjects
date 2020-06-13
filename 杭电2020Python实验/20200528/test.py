# coding = utf-8

# from fun1 import fun
# import fun1
# import fun2
import random

class Student(object):
  def __init__(self, name, number):
    self.name = name
    self.number = number
    self.score = 0
  def get_info(self):
    print("{} {} {}".format(self.name, self.number, self.score))
  def set_info(self, score):
    self.score = score

class Dog(object):
  def __init__(self, name, month_age, kind):
    self.__name = name
    self.month_age = month_age
    self.kind = kind
  def bark(self):
    print("fuck!")
  @property
  def name(self):
    return self.__name

def calc_pi(t = 100000):
  cnt = 0
  # square 0,1 circle (.5, .5) r = .5
  for i in range(t):
    x = random.random()
    y = random.random()
    if pow(x-.5, 2)+pow(y-.5, 2) <= .25:
      cnt += 1
  return (cnt/t)*4

def is_prime(x):
  return not any([1 if x%i == 0 else 0 for i in range(2, x)])

if __name__ == "__main__":
  # print(fun1.fun())
  # print(fun2.fun())
  # for i in range(10):
    # print(random.randint(0, 49)*2+1)
  # print(calc_pi())
  # print(is_prime(17))
  # print(is_prime(16))
  stu = Student('fack', 123)
  stu.set_info(99)
  stu.get_info()