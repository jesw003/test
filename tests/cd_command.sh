#!/bin/sh

cd ..
make
./a.out << EOF
cd -
ls
cd src
ls
cd
ls
pwd
exit
EOF
