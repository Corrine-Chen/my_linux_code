#!/bin/bash

i=1
cpunt=0

while [ $i  -le 254 ]
do
	if [ $count -gt 20 ];then
		count=0
		sleep 2
	fi
	ping -c1 "192.168.0.$i" &
	let i++
	let count++
done
