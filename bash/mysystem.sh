#!/bin/bash
clear 
echo " This information is provided by mysystem.sh "
echo ""

echo " The program starts now ... "
echo 

echo "Hello $USER"
echo 
echo " Todays date is: `date` , this is week `date +"%V"`. "
echo 

echo " Theese are the curremtly connected users :"
w | cut -d " " -f 1 - | grep -v USER | sort -u 
echo 

echo " This is `uname -s` running on a `uname -m` processor "
echo 

echo " The PC is on since :"
uptime 
echo 

echo " That is all the info required "



