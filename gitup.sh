#!/bin/bash
#this need expanding to cmds, and selecting builds.and tuilizes branches, 
#wrape in a lager bash programe, onver this to procedure.
currentDate=`date +%s`
if [ $# -eq 0 ];
  then
  echo "No arguments supplied to commitee name"

  else
  git add .
  git commit -m "$1:: $currentDate"
  git push -u origin master
  echo gitupdated at $currentDate
fi
