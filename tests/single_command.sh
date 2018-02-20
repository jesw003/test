#!/bin/sh

cd ..
make
./a.out << EOF
echo hi
ls
ls -a
date
git --version
mkdir random
touch love
exit
EOF