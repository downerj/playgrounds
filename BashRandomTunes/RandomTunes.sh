#!/usr/bin/env bash

# https://shkspr.mobi/blog/2016/04/generating-random-chiptunes-on-linux/

notes="-7,-6,-5,-2,0,3,5,6,7,10,12"
#notes="-7,-5,-3,0,2,5,7,9,12"
format=S32_LE
rate=24000
numChannels=2

cat /dev/urandom | \
  hexdump -v -e '/1 "%u\n"' | \
  awk "{\
      split(\"$notes\", a, \",\"); \
      for (i = 0; i < 1; i+= 0.0001) {\
        printf(\"%08X\\n\", 100*sin(1382*exp((a[\$1 % 8]/12)*log(2))*i)) \
      }\
  }" | \
  xxd -r -p | \
  aplay -c $numChannels -f $format -r $rate

