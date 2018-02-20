#!/bin/sh

cd ..
make
./a.out << EOF
echo Hello World!; exit
EOF
./a.out << EOF
ls -a && exit
EOF
./a.out << EOF
cal || date && exit
EOF
./a.out << EOF
#exit
EOF
./a.out << EOF
git --version && echo Will this exit || exit
EOF
./a.out << EOF
ls || exit
EOF
./a.out << EOF
date || git --version ; cal && exit
EOF