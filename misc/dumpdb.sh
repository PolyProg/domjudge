#!/bin/bash
FILE=$(date +"/home/ubuntu/dumps/%Y%m%d%H%M%S.db")
echo $FILE >> /home/ubuntu/dumps/dumps.log
mysqldump -u root domjudge -p6MPafaaH > $FILE
gzip $FILE
