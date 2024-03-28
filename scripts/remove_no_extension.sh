# remove all files without extension

find . -type f -path "*[Ee]sercizi*" ! -name "*.*" -exec rm -f {} \;