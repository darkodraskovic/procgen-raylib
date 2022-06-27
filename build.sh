#!/bin/bash

TARGET=
EXE_NAME=
ROOT_DIR=/home/darko/Development/procgen-raylib/

COMPILE_CMD="make"
CONFIGURE=false
SLN=procgen.sln
WIN=false

if [ "$OSTYPE" = "msys" ]; then
    WIN=true
    ROOT_DIR=c:/Users/darko/Development/procgen-raylib/
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release"
else
    ROOT_DIR=/home/darko/Development/procgen-raylib/
fi

echo "ROOT_DIR: $ROOT_DIR"

while getopts "ct:" option; do
    case $option in
        c)
            CONFIGURE=true
            ;;
        t)
            TARGET=$OPTARG
            EXE_NAME=./$TARGET
            ;;
    esac
done

if [ $CONFIGURE = true ]; then
    cd ${ROOT_DIR}/build
    cmake ..
    if [ $? != 0 ]; then
        exit 1
    fi

    if [ $WIN == true ]; then
        cd $ROOT_DIR/ninja/
        cmake -G"Ninja" ..
        mv compile_commands.json ..
    fi

    exit 0
fi

if [ $WIN == true ]; then
    if [ $TARGET != $SLN ]; then
        TARGET=${TARGET}.vcxproj
    fi
fi

echo "COMPILE_CMD: ${COMPILE_CMD}"
echo "EXE_NAME: ${EXE_NAME}"

cd ${ROOT_DIR}/build
echo "BUILD: $TARGET"
$COMPILE_CMD $TARGET
if [ $? != 0 ]; then
    exit 1
fi

if [ $TARGET != $SLN ] && [ $TARGET != all ]; then
    cd ${ROOT_DIR}/bin
    echo "EXECUTE: $TARGET"
    $EXE_NAME
fi
