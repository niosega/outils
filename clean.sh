#!/bin/bash
rm -rf bin

for dir in `ls -d -- nico*/`
do
    here=`pwd`
    cd $dir
    echo "# Cleaning " $dir
    make clean
    echo ""
    cd $here
done