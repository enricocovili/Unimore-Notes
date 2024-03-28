#!/bin/bash

IFS=$'\n'

for file in $(find $(git root) -type f -name "*.xopp")
do
    if [ -f "${file%.xopp}.pdf" ]; then
        # echo "File ${file%.xopp}.pdf already exists. Skipping ${file}"
        continue
    fi
    # echo $file >> test.txt
    xournalpp -p "${file%.xopp}.pdf" "${file}"
done
