#!/bin/sh

cd ..
make
./a.out << EOF
echo hi || ls && cal
echo Hello World && date && ls -a; echo Bye World
l || echo Hello World
echo Hello; echo World
ls && ls -a
l || echo Error
echo I am a loser; ls -a && cal && date
exit
EOF