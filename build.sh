#!/bin/bash

TARGET=
ROOT_DIR=$(pwd)
COMPILE_CMD="make"

CONFIGURE=false
NINJA=false

SLN=procgen2d.sln

echo "ROOT_DIR: $ROOT_DIR"

while getopts "cnt:" option; do
    case $option in
        c)
            CONFIGURE=true
            ;;
        n)
            NINJA=true
            ;;
        t)
            TARGET=$OPTARG
            ;;
    esac
done

if [ $CONFIGURE = true ]; then
    cd ${ROOT_DIR}/build
    cmake ..
fi

if [ $NINJA = true ]; then
    cd $ROOT_DIR/ninja/
    cmake -G"Ninja" ..
    mv compile_commands.json ..
fi

if [ -z $TARGET ]; then
    exit 0
fi

EXE_NAME=./$TARGET
if [ "$OSTYPE" = "msys" ]; then
    EXE_NAME=${EXE_NAME}.exe
    if [ $TARGET != $SLN ]; then
        TARGET=${TARGET}.vcxproj
    fi
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release"
fi

echo "COMPILE_CMD: ${COMPILE_CMD}"
echo "EXE_NAME: ${EXE_NAME}"

cd ${ROOT_DIR}/build
echo "BUILD: $TARGET"
$COMPILE_CMD $TARGET
if [ $? -gt 0 ]; then
    exit 1
fi

if [ $TARGET != $SLN ] && [ $TARGET != all ]; then
    cd ${ROOT_DIR}/bin
    echo "EXECUTE: $TARGET"
    ./$EXE_NAME
fi
