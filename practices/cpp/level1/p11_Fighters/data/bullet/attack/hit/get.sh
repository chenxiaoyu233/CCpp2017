#!/bin/bash
read
for((i = 0; i <= 14; i++))
do
	echo "$REPLY/$i.png" >> setting
	echo "$REPLY/info$i" >> setting
done
