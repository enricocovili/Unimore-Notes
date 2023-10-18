mv *.png imgs/
find . -name '*.md' -exec sed -i -e 's/imgs\/imgs/imgs/g' {} \;
