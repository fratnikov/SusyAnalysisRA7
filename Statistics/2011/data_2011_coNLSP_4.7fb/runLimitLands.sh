#!/bin/bash
export PATH=`pwd`/..:`pwd`/../LandS/test:$PATH
echo $PATH
maxsignal=30
basenm=SUSY_scan_coNLSP

if [ -z "$SGE_TASK_ID" ] 
   then 
   echo runRa7LimitLands $1 $maxsignal
   runRa7LimitLands $1 $maxsignal
else 
   echo runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal
   runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal
fi
