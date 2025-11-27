#!/bin/bash

ROOT_DIR=$(git rev-parse --show-toplevel)
echo "executing $0 at $ROOT_DIR"
cd "$ROOT_DIR"

find . -type d | while IFS= read -r d
do
    cd "$ROOT_DIR"
    cd "$d"
    if [ ! -d "imgs" ]; then
        continue
    fi
    mv *.png imgs/ > /dev/null 2>&1
    # replace all spaces in imgs folder with underscores
    cd imgs
    find . -depth -name '* *' \
    | while IFS= read -r f ; do mv -i "$f" "$(dirname "$f")/$(basename "$f"|tr ' ' _)" ; done
    cd ..

    # regex da ricordare
    # \.png\]\] -> .png)                                                .png]] -> .png)
    # !\[\[Pasted image -> ![placeholder](./imgs/Pasted_image_          ![[Pasted image  -> ![placeholder](./imgs/Pasted_image_

    # replace all .png]] with .png)
    sed -i 's/\.png\]\]/.png)/g' *.md
    # replace all ![[Pasted image with ![placeholder](./imgs/Pasted_image_
    sed -i 's/!\[\[Pasted image /![placeholder](\.\/imgs\/Pasted_image_/g' *.md
done
