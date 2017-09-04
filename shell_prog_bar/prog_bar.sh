#!/bin/bash

i=0
label=('|' '\\' '-' '/')
str=''
while [ $i -le 100 ]
do
	let index=i%4
	printf "[\e[1;31;1m%-100s\e[0m][%2d%%][%c]\r" "$str" "$i" "${label[$index]}"
	str="#"$str
	sleep 0.1
	let i++
done
echo""


  
