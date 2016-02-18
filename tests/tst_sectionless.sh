#!/bin/sh
export PATH=../src/:$PATH

testGetValue()
{
    assertEquals 'foobar' `manini -f ${TESTFILEPATH} -g '' value`
}

testGetValueWithWhiteSpace()
{
    assertEquals "example" `manini -f ${TESTFILEPATH} -g '' "key with whitespace"`
}

testGetKeyWithWhiteSpace()
{
    assertEquals "foobar barfoo" "`manini -f ${TESTFILEPATH} -g '' valuewithspace`"
}

oneTimeSetUp()
{
    echo "manini version:  `manini -V 2>&1`"
    export TESTFILEPATH="${SHUNIT_TMPDIR}/test.ini"
    cat > ${TESTFILEPATH} << EOF
    value = foobar
    valuewithspace = foobar barfoo
    key with whitespace = example
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
