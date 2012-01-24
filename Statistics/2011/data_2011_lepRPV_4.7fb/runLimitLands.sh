#!/bin/bash
export PATH=$HOME/cms/SUSY/stat/RA7:$HOME/cms/SUSY/stat/RA7/LandS/test:$PATH
maxsignal=35
basenm=SUSY_scan

if [ -z "$SGE_TASK_ID" ] 
   then 
   echo runRa7LimitLands $1 $maxsignal
   runRa7LimitLands $1 $maxsignal
else 
   echo runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal
   runRa7LimitLands $basenm.$SGE_TASK_ID.txt $maxsignal
fi