#!/bin/bash

mv *.png imgs/ > /dev/null 2>&1
# replace all spaces in imgs folder with underscores
cd imgs
find . -depth -name '* *' \
| while IFS= read -r f ; do mv -i "$f" "$(dirname "$f")/$(basename "$f"|tr ' ' _)" ; done
cd ..
# replace all occurences of ![[Pasted Image XXX.png]] with ![placeholder](./imgs/Pasted_Image_XXX.png)
find . -name "*.md" -type f -exec sed -i '' -e 's/\!\[\[Pasted Image [0-9]*\.png\]\]/\!\[placeholder\]\(\.\/imgs\/Pasted_Image_[0-9]*\.png\)/g' {} \;
# the above command is giving me an error: sed: can't read : No such file or directory. please fix it
