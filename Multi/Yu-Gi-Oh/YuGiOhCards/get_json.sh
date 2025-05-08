#!/usr/bin/env bash
mkdir json
curl -R -o json/all_cards.json https://db.ygoprodeck.com/api/v7/cardinfo.php
