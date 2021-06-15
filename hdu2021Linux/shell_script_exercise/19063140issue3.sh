#!/bin/bash

for((i=0;i<7;++i))
do
    a[i]=1
    for((j=i-1;j>0;--j))
    do
        a[j]=$((a[j]+a[j-1]))
    done
    echo ${a[*]}
done
