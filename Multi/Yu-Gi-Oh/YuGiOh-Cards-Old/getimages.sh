#!/usr/bin/env bash

api="https://db.ygoprodeck.com/api/v7/cardinfo.php"
curl -L -o "cardinfo.json" -R "${api}"
py collectids.py
readarray ids < ids.txt
for ((i = 0; i < ${#ids[@]}; i++))
do
  id="${ids[$i]}"
  url="https://images.ygoprodeck.com/images/cards/${id}.jpg"
  curl -L -o "images/${id}.jpg" -R "${url}"
  sleep 0.25
done
