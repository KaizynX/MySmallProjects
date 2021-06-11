/*
 * @Author: Kaizyn
 * @Date: 2021-03-11 14:11:45
 * @LastEditTime: 2021-03-18 15:00:31
 */
#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include <stdio.h>

typedef int DataElem;

struct SeqList {
  DataElem *pDatas;
  int iSize, iLength; // 存储空间大小，元素个数
};

SeqList Create(int size) {
  SeqList list;
  if (size <= 0) {
    puts("\n\t空间要>=0");
  }
  list.iSize = size;
  list.iLength = 0;
  list.pDatas = new DataElem[size];
  if (list.pDatas == nullptr) {
    puts("\n\t空间分配失败.");
  }
  return list;
}

// 2.清空线性表
void Clear(SeqList &pList) {
  pList.iLength = 0;
}

// 3.销毁线性表
void Destroy(SeqList &pList) {
  delete[] pList.pDatas;
  pList.pDatas = nullptr;
  pList.iLength = 0;
  pList.iSize = 0;
}

// 4.判断线性表是否为空
bool IsEmpty(const SeqList &pList) {
  return pList.iLength;
}

// 5.
int Length(const SeqList &pList) {
  return pList.iLength;
}

// 6.获取元素值

DataElem GetElem(SeqList &pList, int loc) {
  if (loc < 1 || loc > pList.iLength) {
    puts("\n\t位置越界，获取元素失败");
  }
  return pList.pDatas[loc-1];
}

// 7.修改元素值
bool GetElem(SeqList &pList, int loc, DataElem e) {
  if (loc < 1 || loc > pList.iLength) {
    puts("\n\t位置越界，修改元素失败");
    return false;
  }
  pList.pDatas[loc-1] = e;
  return true;
}

// 8.查找元素返回位置
int LocateElem(SeqList pList, DataElem e) {
  for (int i = 0; i < pList.iLength; ++i) {
    if (pList.pDatas[i] == e) {
      return i+1;
    }
  }
  return -1;
}

// 扩展空间
bool doubleSpace(SeqList &pList) {
  ;
}

// 9.插入元素
bool InsertBefore(SeqList &pList, int loc, DataElem e) {
  if (loc < 1 || loc > pList.iLength) {
    puts("\n\t位置越界，插入元素失败");
    return false;
  }
  if (pList.iSize == pList.iLength) {
    doubleSpace(pList);
  }
  for (int i = pList.iLength; i >= loc; --i) {
    pList.pDatas[i] = pList.pDatas[i-1];
  }
  pList.iLength++;
  pList.pDatas[loc-1] = e;
  return true;
}

// 10.打印线性表
void PrintList(SeqList pList) {
  printf("\n\n");
  if (pList.iLength == 0) {
    puts("\n\t当前线性表为空");
  }
  for (int i = 0; i < pList.iLength; ++i) {
    printf("%d\t", pList.pDatas[i]);
  }
}