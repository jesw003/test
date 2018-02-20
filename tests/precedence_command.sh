#1/bin/sh
cd ..
make
cd bin
./a.out << EOF
(echo "worms" && echo "wordondastreet") && (ls)
ls ; (echo "hi" && echo "what are we doing")
echo "blue" || (ech "incorrect")
exit
EOF
