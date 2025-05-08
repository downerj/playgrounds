#!/bin/bash

// https://unix.stackexchange.com/a/72299
find $target -type f -exec md5sum '{}' + | sort | uniq --all-repeated=separate --check-chars=32 | cut --characters=35-
