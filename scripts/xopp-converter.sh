#!/bin/bash

IFS=$'\n'

if [[ "$1" != "--overwrite" ]]; then
    echo "No overwrite flag detected. Use --overwrite to overwrite existing pdf files."
fi

# print all arguments
for file in $(find $(git root) -type f -name "*.xopp")
do
    if [[ -f "${file%.xopp}.pdf" && "$1" != "--overwrite" ]]; then
        # echo "File ${file%.xopp}.pdf already exists. Skipping ${file}"
        continue
    fi
    xournalpp -p "${file%.xopp}.pdf" "${file}"
done

echo "Conversion complete."
