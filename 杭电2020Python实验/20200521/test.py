# coding = utf-8

def hb(names):
  for name in names :
    print("Happy birthday to you")
    print("Happy birthday to you")
    print("Happy birthday, dear ", name)
    print("Happy birthday to you")

def dis(x1 = 1, y1 = 1, x2 = 1, y2 = 2):
  print((x1-x2)**2+(y1-y2)**2)

def pt(a, *b):
  print(a)
  print(b)

def add(a, b, f):
  return f(a)+f(b)

def fac(n):
  if n == 1 : return 1
  else : return n*fac(n-1)

def hnt(a, b, c, n):
  if n == 0: return 0
  cnt = 1
  cnt += hnt(a, c, b, n-1)
  print(a, "->", c)
  cnt += hnt(b, a, c, n-1)
  return cnt

if __name__ == "__main__":
  # hb(["frank"])
  # hb(["a", "b"])
  # dis(x2 = 2)
  # pt(1)
  # pt(1, 2, 3, 4)
  # print(add(-1, 1, abs))
  # f = lambda a, b = 1, c = 2 : a*b+c
  # print(f(1))
  # print(fac(10))
  print(hnt('A', 'B', 'C', 3))