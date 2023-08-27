#!/usr/bin/env bash

python=/usr/bin/env python3
sqlite=/usr/bin/env sqlite3

mkdir -p chip_images
$python request.py

# If the following fails, then modify the chips.html file to include only the tables and redo the remaining steps.
$python scrape.py

$sqlite chips.db < add_csv_to_db.sql
