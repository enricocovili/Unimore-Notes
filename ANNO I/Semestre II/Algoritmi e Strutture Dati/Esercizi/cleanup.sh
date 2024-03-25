# remove all files without extension

find . -type f ! -name "*.*" -exec rm -f {} \;