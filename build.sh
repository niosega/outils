#!/bin/bash
rm -rf bin
mkdir bin

export CC=clang

for dir in `ls -d -- nico*/`
do
    here=`pwd`
    cd $dir
    echo "# Building " $dir
    make clean
    make all
    echo ""
    cd $here
done