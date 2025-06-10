#!/bin/bash

for dir in */; do
    # Remove trailing slash
    dirname="${dir%/}"
    # Match format: day_month_year (e.g., 12_05_2024)
    if [[ "$dirname" =~ ^([0-9]{1,2})_([0-9]{1,2})_([0-9]{4})$ ]]; then
        day="${BASH_REMATCH[1]}"
        month="${BASH_REMATCH[2]}"
        year="${BASH_REMATCH[3]}"
        newname="${year}_$(printf "%02d" $month)_$(printf "%02d" $day)"
        # Only rename if new name is different and doesn't exist
        if [[ "$dirname" != "$newname" && ! -e "$newname" ]]; then
            mv "$dirname" "$newname"
        fi
    fi
done