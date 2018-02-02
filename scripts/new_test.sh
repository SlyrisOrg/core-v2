#!/bin/bash

function fatal()
{
    echo "$@"
    exit 1
}

[ $# -ne 1 ] && fatal "Usage: ./scripts/new_test.sh <testname>"

TEST=$1
mkdir -p tests/${TEST}-test

TESTSOURCE=tests/${TEST}-test/${TEST}-test.cpp
touch $TESTSOURCE
echo '//' >> $TESTSOURCE
echo '// Created by '$USER' on '$(date +%d/%m/%y) >> $TESTSOURCE
echo '//' >> $TESTSOURCE

CMAKEFILE=tests/${TEST}-test/CMakeLists.txt
touch $CMAKEFILE
echo "set(SOURCES ${TEST}-test.cpp)" >> $CMAKEFILE
echo 'CREATE_UNIT_TEST('${TEST}'-test Core: "${SOURCES}")' >> $CMAKEFILE
