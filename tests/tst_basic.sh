#!/bin/sh
export PATH=../src/:$PATH


testInSectionWithComment()
{
    assertEquals 'noot' `manini -f ${TESTFILEPATH} -g First String`
}

testInSectionWithoutComment()
{
    assertEquals '1' `manini -f ${TESTFILEPATH} -g First Val`
}

oneTimeSetUp()
{
    echo "manini version:  `manini -V 2>&1`"
    export TESTFILEPATH="${SHUNIT_TMPDIR}/test.ini"
    cat > ${TESTFILEPATH} << EOF
    [First]
    String=noot # trailing commment
    Val=1

    [Second]
    Val = 2
    #comment=3
    String = mies
EOF

}

oneTimeTearDown()
{
  rm -fr "${SHUNIT_TMPDIR}"
}

if ! [ -x "$(command -v shunit2)" ]; then
  echo 'shunit2 is not installed.' >&2
  echo 'you need to install shunit2 to run tests.' >&2
  echo 'exiting...' >&2
  exit 1
fi

. shunit2
