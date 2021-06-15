#!/bin/bash

result="$(javac -version 2>&1 | grep 1.8)"
if [ "$result" == "" ]
then
    echo "no jdk 1.8, start installing"
    cd /usr/local
    mkdir java
    cd java
    sudo wget https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html#license-lightbox
    tar -xzvf jdk-8u241-linux-x64.tar.gz
    rm jdk-8u241-linux-x64.tar.gz
    chmod 700 /etc/profile
    echo "#jdk config" >>/etc/profile
    echo "export JAVA_HOME=/usr/jdk" >>/etc/profile
    echo "export JRE_HOME=$JAVA_HOME/jre" >>/etc/profile
    echo "export CLASSPATH=$CLASSPATH:$JAVA_HOME/lib:$JRE_HOME/lib" >>/etc/profile
    echo "export PATH=$PATH:$JAVA_HOME/bin:$JRE_HOME/bin" >>/etc/profile
    source /etc/profile
    echo "installing complete"
else
    echo "jdk 1.8 installed"
fi
echo ""
