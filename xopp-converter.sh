#!/bin/bash

for file in *.xopp
do
    if [ -f "${file%.xopp}.pdf" ]; then
        echo "File ${file%.xopp}.pdf already exists. Skipping ${file}"
        continue
    fi
    xournalpp -p "${file%.xopp}.pdf" "${file}"
done
