#!/bin/bash

function fatal()
{
    echo "$@"
    exit 1
}

[ $# -ne 1 ] && fatal "Usage: ./scripts/new_module.sh <modulename>"

MODULE="$1"

mkdir -p core/$MODULE

SOURCESFILE=core/$MODULE/CMakeSources.cmake
touch $SOURCESFILE
echo "### Sources for the $MODULE module" >> $SOURCESFILE
echo >> $SOURCESFILE
echo 'set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/'$MODULE')' >> $SOURCESFILE
echo >> $SOURCESFILE
echo 'set(MODULE_PUBLIC_HEADERS "")' >> $SOURCESFILE
echo >> $SOURCESFILE
echo 'set(MODULE_PRIVATE_HEADERS "")' >> $SOURCESFILE
echo >> $SOURCESFILE
echo 'set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})' >> $SOURCESFILE

CMAKEFILE=core/$MODULE/CMakeLists.txt
touch $CMAKEFILE
echo "include(CMakeSources.cmake)" >> $CMAKEFILE
echo 'set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})' >> $CMAKEFILE
echo 'CREATE_MODULE(Core::'${MODULE^}' "${MODULE_SOURCES}" ${MODULE_PATH})' >> $CMAKEFILE
