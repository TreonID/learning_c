#!/bin/bash
for i in *.dat; do ./a.out < $i; cat $i.result; done