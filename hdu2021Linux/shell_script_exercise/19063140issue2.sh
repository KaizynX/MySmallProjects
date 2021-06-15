#!/bin/bash
bar=''
for ((i=0;i<=100;i=i+2))
do
    printf "[%-50s]%d%%\n" $bar $i
    sleep 0.1
    printf "\033[A";
    bar=#$bar
done
echo ""
