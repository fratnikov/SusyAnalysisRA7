#!/bin/bash
export PATH=`pwd`/..:`pwd`/../LandS/test:$PATH
echo $PATH
maxsignal=75
channels=10
basenm=SUSY_scan_v1

if [ -z "$SGE_TASK_ID" ] 
   then 
   echo runRa7LimitLands $1 $maxsignal $channels
   runRa7LimitLands $1 $maxsignal $channels
else 
   echo runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal $channels
   runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal $channels
fi