#!/bin/bash

for testfile in ./test/test*.in; do
  result=$(./game -s < $testfile)
  
  echo $testfile
  cat $testfile
  cat $testfile.out
  echo $result
  if [ "$result" = "$(cat $testfile.out)" ]; 
  then 
    echo "OK"
    echo
  else 
    echo "ERROR"
    echo
  fi
done
