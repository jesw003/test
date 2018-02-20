#!/bin/sh

cd ..
make
./a.out << EOF
echo Hello #World
echo Hello World; cal; #date
ls -a || #echo Hello World && cal
cal && git --version && #mkdir remove
#ls && echo Does this work
git --version && echo Hi Mom && #ls - a
exit
EOF