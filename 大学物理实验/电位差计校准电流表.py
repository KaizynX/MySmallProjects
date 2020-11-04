'''
14.523 29.824 45.361 60.485 75.390 90.865 105.304 120.243 135.196 150.196
14.598 29.582 44.980 60.056 74.923 90.196 105.431 120.525 135.396 150.562
'''
import math

if __name__ == "__main__":
  I = []
  for i in range(10) :
    I.append(0.5*i+0.5)
  # U01 = list(map(float, input().split()))
  # U02 = list(map(float, input().split()))
  U01 = [14.523, 29.824, 45.361, 60.485, 75.390, 90.865, 105.304, 120.243, 135.196, 150.196]
  U02 = [14.598, 29.582, 44.980, 60.056, 74.923, 90.196, 105.431, 120.525, 135.396, 150.562]
  U0 = [round((U01[i]+U02[i])/2, 3) for i in range(10)]
  R0 = 30
  I0 = [round(U/R0, 3) for U in U0]
  dI = [round(I[i]-I0[i], 3) for i in range(10)]
  print(I)
  print(U01)
  print(U02)
  print(U0)
  print(I0)
  print(dI)