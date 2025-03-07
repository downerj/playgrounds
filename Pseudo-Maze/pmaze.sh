#!/usr/bin/env bash

# Clear screen.
printf '\ec'
# Clear scrollback.
#printf '\e[3J'
# Reset colors & set bold foreground.
printf '\e[0;1m'
# Colors: R/Y/G/C/B/M.
colors=(1 3 2 6 4 5)
# Unicode: Fullwidth Solidus & Reverse Solidus.
characters=('\uff0f' '\uff3c')
count=0
while true
do
  colorIndex=$((${count} % 6))
  color=${colors[colorIndex]}
  printf "\e[9${color}m"
  choice=$((RANDOM % 2))
  character=${characters[choice]}
  printf "${character}"
  count=$((count + 1))
  sleep 0.05
done
