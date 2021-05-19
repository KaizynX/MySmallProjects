/*
 * @Author: Kaizyn
 * @Date: 2021-05-19 10:15:13
 * @LastEditTime: 2021-05-19 10:23:48
 */
#include <iostream>
using namespace std;

/* 请在这里填写答案 */
#include <bits/stdc++.h>

template <class T>
class MyArray {
  size_t size;
  T *data;
public:
  MyArray(size_t size) : size(size) {    
    data = new T[size];
    for (int i = 0; i < (int)size; ++i) cin >> data[i];
  }
  ~MyArray();
  bool check();
  void sort() {
    std::sort(data, data+size);
  }
  void display() {
    for (int i = 0; i < (int)size; ++i) {
      cout << data[i] << " \n"[i+1==(int)size];
    }
  }
};

template<class T>
MyArray<T>::~MyArray(){ delete[] data;}

template<class T>
bool MyArray<T>::check(){
    int i;
    for(i=0;i<(int)size-1;i++)
        if(data[i]>data[i+1]) { cout<<"ERROR!"<<endl;return false;}
    return true;
}
int main( )
{
    MyArray<int> *pI;
    MyArray<float> *pF;
    MyArray<char> *pC;
    int ty, size;
    cin>>ty;
    while(ty>0){
        cin>>size;
        switch(ty){
            case 1: pI = new MyArray<int>(size);   pI->sort(); pI->check(); pI->display(); delete pI; break;
            case 2: pF = new MyArray<float>(size); pF->sort(); pF->check(); pF->display(); delete pF; break;
            case 3: pC = new MyArray<char>(size);  pC->sort(); pC->check(); pC->display(); delete pC; break;
        }
        cin>>ty;
    }
    return 0;
}