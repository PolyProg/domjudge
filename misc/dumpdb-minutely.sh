#!/bin/bash
MINUTE=$(date +"%M")
MOD3=$(expr $MINUTE "%" 3)
FILE="/home/ubuntu/dumps/latest${MOD3}.db"
echo $FILE >> /home/ubuntu/dumps/minutely.log
mysqldump -u root domjudge -p6MPafaaH > $FILE
