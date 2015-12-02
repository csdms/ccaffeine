#!/bin/sh
if ! test -f .counter; then
echo 1 > .counter
fi
counter=`cat .counter`
echo "$counter"
y="$(($counter+1))"
echo $y > .counter
