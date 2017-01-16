manini
===============

MANipulating INI files

Manini is a small command line utility to get or set values from/to .ini
files, intended to use in shell scripts. It's based on (in fact: a thin wrapper around)
the minIni library provided by CompuPhase, and which is bundled with this source tree. 
Consequently the only external dependency is a recent libc implementation, which suits
well for using in embedded systems.


Examples
============

Let your ini file be:

    echo "akey = avalue" > /tmp/test.ini
    echo "[bsection]" >> /tmp/test.ini
    echo "bkey = bvalue" >> /tmp/test.ini


and in your shell script:

    #!/bin/sh

    AKEY=`manini --get --file /tmp/test.ini akey`
    BKEY=`manini --get --file /tmp/test.ini bsection bkey`
    echo "A: $AKEY"
    echo "B: $BKEY"


or, if you work on only one ini file at a time, in your scripts, to save same
typing just can just export the MANINI_INIFILEPATH environment variable, and forget
about the --file argument:


    #!/bin/sh

    export MANINI_INIFILEPATH="/tmp/test.ini"

    AKEY=`manini --get akey`
    BKEY=`manini --get bsection bkey`
    echo "A: $AKEY"
    echo "B: $BKEY"
