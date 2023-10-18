#!/bin/bash

mv *.png imgs/
find . -name '*.md' -exec sed -i -e 's/\[\[/\[placeholder\]\(/g' {} \;
# ![placeholder](imgs/Pasted image 20231010155631.png]]
find . -name '*.md' -exec sed -i -e 's/\]\]/\)/g' {} \;
# ![placeholder](imgs/Pasted image 20231010155631.png)
find . -name '*.md' -exec sed -i -e 's/imgs\/Pasted image /\.\/imgs\/Pasted\%20image\%20/g' {} \;
# ![placeholder](./imgs/Pasted%20image%2020231010155631.png)
