#!/bin/sh
cd ..
make
cd bin
./a.out << EOF
test -e /home/csmajs/nseth001/rshell
test -e /home/csmajs/nseth001/rshell/src/EC.h
[ -e /home/csmajs/nseth001/rshell ]
[ -e /home/csmajs/nseth001/rshell/src/EC.h ]
test -e /home/csmajs/nseth001/rshell/ && echo "worm"
[ -e /home/csmaks/nseth001/rshell/ ] && echo "worm"
test -e /home/csmajs/nseth001/rshell/src/EC.h || echo "worm"
[ -e /home/csmaks/nseth001/rshell/src/EC.h ] || echo "worm"
exit
EOF
