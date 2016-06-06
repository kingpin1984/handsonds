#!/bin/bash

echo "ARGS:"$#
if [ $# -ne 0 ];then
  cscope $1
  exit
fi
find `pwd` -type f -regex ".*\.\(c\|h\|py\|cc\|cpp\|hh\)" -print > ./cscope.files
export CSCOPE_DB=./cscope.out
export CSCOPE_EDITOR=vim
cscope -u
