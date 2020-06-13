# coding = utf-8

import os
import math

if __name__ == "__main__" :
# question 1
  file_score = open(r".\20200514\score.txt", "rt")
  lists_score = [list(map(int, l.split()[1:])) for l in file_score.readlines()[1:]]
  file_score.close()
  n = len(lists_score)
  score_max = [0 for i in range(6)]
  score_min = [100 for i in range(6)]
  score_sum = [0 for i in range(6)]
  score_D = [0 for i in range(6)]
  number_A = [0 for i in range(6)]
  number_B = [0 for i in range(6)]
  number_C = [0 for i in range(6)]
  number_P = [0 for i in range(6)]
  number_F = [0 for i in range(6)]
  D = [0 for i in range(n)]
  stu_sum = [0 for i in range(n)]
  stu_D = [0 for i in range(n)]

  for i in range(n) :
    stu_score = lists_score[i]
    for j in range(6) :
      score = stu_score[j]
      stu_sum[i] += score
      score_max[j] = max(score_max[j], score)
      score_min[j] = min(score_min[j], score)
      score_sum[j] += score
      if score <  60 : number_F[j] += 1
      if score >= 60 : number_P[j] += 1
      if score >= 70 : number_C[j] += 1
      if score >= 80 : number_B[j] += 1
      if score >= 90 : number_A[j] += 1

  score_ave = [x/n for x in score_sum]
  number_A = [x/n for x in number_A]
  number_B = [x/n for x in number_B]
  number_C = [x/n for x in number_C]
  number_P = [x/n for x in number_P]
  number_F = [x/n for x in number_F]
  stu_ave = [x/6 for x in stu_sum]

  for i in range(n) :
    stu_score = lists_score[i]
    for j in range(6) :
      score = stu_score[j]
      score_D[j] += pow(score-score_ave[j], 2)
      stu_D[i] += pow(score-stu_ave[i], 2)
  
  score_D = [math.sqrt(x/n) for x in score_D]
  stu_D = [math.sqrt(x/n) for x in stu_D]

  print('  最高分 最低分 平均分 优秀占比 良好占比 中等占比 及格占比 不及格占比 成绩均方差')
  for i in range(6) :
    print('D{:d}'.format(i+1), end='')
    print('{:6d}'.format(score_max[i]), end='')
    print('{:7d}'.format(score_min[i]), end='')
    print('{:7.3f}'.format(score_ave[i]), end='')
    print('{:9.3f}'.format(number_A[i]), end='')
    print('{:9.3f}'.format(number_B[i]), end='')
    print('{:9.3f}'.format(number_C[i]), end='')
    print('{:9.3f}'.format(number_P[i]), end='')
    print('{:11.3f}'.format(number_F[i]), end='')
    print('{:11.3f}'.format(score_D[i]))

  rk_id = sorted(range(n), key=lambda k: (-stu_sum[k], stu_D[k]))
  print('排名前10强：')
  for i in range(10) :
    print("No{}[{:.3f}]".format(rk_id[i], stu_D[rk_id[i]]))
    # print(stu_sum[rk_id[i]])
  rk_id = sorted(range(n), key=lambda k: (stu_sum[k], -stu_D[k]))
  print('排名后10强：')
  for i in range(10) :
    print("No{}[{:.3f}]".format(rk_id[i], stu_D[rk_id[i]]))
    # print(stu_sum[rk_id[i]])

# question 2
  file_name = open(r".\20200514\name.txt", "rt", encoding='UTF-8')
  lists_name = [name.rstrip('\n') for name in file_name.readlines()[1:]]
  file_name.close()
  n = len(lists_name)
  last_count = {}
  first_count = {}
  for name in lists_name :
    last_name = (name[:1] if len(name) <= 3 else name[:2])
    last_count[last_name] = last_count.get(last_name, 0)+1
    first_name = (name[-2:] if len(name) >= 3 else name[-1:])
    for ch in first_name :
      first_count[ch] = first_count.get(ch, 0)+1

  last_rank = sorted(last_count.keys(), key= lambda k: last_count[k], reverse=True)
  first_rank = sorted(first_count.keys(), key= lambda k: first_count[k], reverse=True)
  print('姓氏前5分别是:')
  for i in range(5) :
    print("{},占比{:.3f}%".format(last_rank[i], last_count[last_rank[i]]/n*100))
  print('名中，常用字(不含姓氏）前5为：')
  for i in range(5) :
    print("{},出现{}次".format(first_rank[i], first_count[first_rank[i]]))

  os.system('pause')