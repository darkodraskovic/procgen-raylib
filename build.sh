#!/bin/bash

TARGET=
DEFAULT_TARGET=00_hello_world
ROOT_DIR=$(pwd)
echo "ROOT_DIR: $ROOT_DIR"

while getopts "t:" option; do
    case $option in
        t)
            TARGET=$OPTARG
            ;;
    esac
done

if [ -z "$TARGET" ]; then
    echo "WARN: No target specified, using $DEFAULT_TARGET"
    TARGET=$DEFAULT_TARGET
fi

cd ${ROOT_DIR}/build
echo "BUILD: $TARGET"
make $TARGET
if [ $? -gt 0 ]; then
    exit 1
fi

cd ${ROOT_DIR}/bin
echo "EXECUTE: $TARGET"
./$TARGET
