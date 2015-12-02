#!/bin/sh
if test -f .fnumbers; then
  grep " $1" .fnumbers |sed -e 's/\.lo//g'
else
  echo $1 |sed -e 's/\.lo//g'
fi
exit 0
