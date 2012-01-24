#!/bin/bash
export PATH=$HOME/cms/SUSY/stat/RA7:$HOME/cms/SUSY/stat/RA7/LandS/test:$PATH
if [ -z "$SGE_TASK_ID" ] 
   then 
   echo runRa7LimitLands $1
   runRa7LimitLands $1
else 
   echo runRa7LimitLands SUSY_scan_coNLSP_$SGE_TASK_ID.txt
   runRa7LimitLands SUSY_scan_coNLSP_$SGE_TASK_ID.txt
fi