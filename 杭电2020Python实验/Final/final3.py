'''
@Author: Kaizyn
@Date: 2020-06-15 20:13:39
@LastEditTime: 2020-06-15 20:39:48
'''
# coding = utf-8

import time
from bs4 import BeautifulSoup

if __name__ == "__main__":
  import requests
  print('读取杭电党委宣传部(新闻中心)党委教师工作部要闻')
  print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())) 
  url = 'http://www.hdu.edu.cn/news/important'
  web_data = requests.get(url)
  web_data.encoding = 'utf-8'
  soup = BeautifulSoup(web_data.text, 'html.parser')
  # print(soup)
  for news in soup.select('.title'):
    if str(news)[20] == '<' : continue
    print(str(news)[19:-6])