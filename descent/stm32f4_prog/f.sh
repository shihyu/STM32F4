#!/bin/sh
if [ "$1" == "" ]; then
  echo usage:
  echo   $0 filename
  exit -1
fi

sudo st-flash write $1 0x8000000
