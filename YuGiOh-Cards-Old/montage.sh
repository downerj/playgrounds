#!/usr/bin/env bash

files=(
  "2P Starter S"
  "2P Starter X"
  "Crystal Beasts"
  "Freezing Chains Alt"
  "Link Strike Alt"
  "Obelisk Tormentor"
  "Synchron Extreme Alt"
)

for ((i = 0; i < ${#files[@]}; i++))
do
  stub="${files[$i]}"
  file="Exports/$stub.ydk"
  echo "Processing file '$file'..."
  awk '$0==($0+0)' "$file" > "Exports/$stub.txt"
  readarray ids < "Exports/$stub.txt"
  rm -f "Exports/$stub.txt"
  count=${#ids[@]}
  for j in $(seq 0 $((count - 1)))
  do
    ids[$j]=${ids[$j]//$'\r'}
    ids[$j]=$(printf "images/%09d.jpg" ${ids[$j]})
  done
  montage ${ids[*]} -geometry 813x1185 -tile 5x "Exports/$stub.jpg"
done
