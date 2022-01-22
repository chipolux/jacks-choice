#!/usr/bin/env bash
set -e

mkdir -p build
pushd build > /dev/null
cmake ..
cmake --build .
popd > /dev/null

if [[ "$*" == *run* ]]; then
    if [[ "$(uname -m)" == *arm* ]]; then
        sudo ./build/jacks-choice
    else
        ./build/jacks-choice
    fi
fi
