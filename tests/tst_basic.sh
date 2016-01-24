#!/bin/sh


export PATH=../src/:$PATH


export TESTFILEPATH='test.ini'

cat > ${TESTFILEPATH} << EOF
[First]
String=noot # trailing commment
Val=1

[Second]
Val = 2
#comment=3
String = mies
EOF


