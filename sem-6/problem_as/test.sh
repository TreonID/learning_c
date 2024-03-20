#!/bin/bash
#for i in *.dat; do echo "======="; ./a.out < $i; cat $i.result; done
for i in *.dat; do echo "======="; ./a.out < $i; done
