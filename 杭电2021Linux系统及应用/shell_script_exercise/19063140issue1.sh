#!/bin/bash

if [ ! -e login.log ]
then
	touch login.log
fi

if [ ! -e loginerr.log ]
then
	touch loginerr.log
fi

read -p "Input unsername:" username
read -p "Input password:" -s password
echo ""

if [ "$username" = tom -a "$password" = tom ]
then 
	if [ "$(tail -1 loginerr.log)" != "" ]
	then 
		echo 'Last faild login:'`tail -1 loginerr.log`
	fi
	if [ "$(tail -1 login.log)" != "" ]
	then 
		echo 'Last login:'`tail -1 login.log`
	fi
	echo 'Welcome to ' `uname -r`
	echo `date` on `tty` >> login.log
	echo > loginerr.log
else
	echo `date` on `tty` >> loginerr.log
	echo Login incorrect.
fi

