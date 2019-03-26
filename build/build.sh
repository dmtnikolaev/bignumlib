#!/usr/bin/env bash

if [ -z "$PROJECT_DIR" ]; then
    PROJECT_DIR=$(pwd)
fi

if [ -z "$BUILD_CONFIGURATION" ]; then
    BUILD_CONFIGURATION='Debug'
fi

OUT_DIR="$PROJECT_DIR/bin/$BUILD_CONFIGURATION/"
mkdir -p "$OUT_DIR"

SOURCE=$(find "$PROJECT_DIR" -name '*.c' -print)

echo "Project folder: $PROJECT_DIR"
echo "Build configuration: $BUILD_CONFIGURATION"
echo "Building..."

BUILD_CONFIGURATION=$(echo "$BUILD_CONFIGURATION" | tr a-z A-Z)

gcc -g -Wall -o "$OUT_DIR/bignumlib.out" -D$BUILD_CONFIGURATION -D'LINUX' -I$PROJECT_DIR/include -I$PROJECT_DIR/src $SOURCE

echo "Done."

