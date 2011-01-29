#!/bin/sh
mkdir $1
cp hello/hello.cpp $1/$1.cpp
cp hello/hello.pro $1/$1.pro
sed -i "s/hello/$1/g" $1/$1.pro
# add subdir
echo "    $1 \\" >> basics.pro
