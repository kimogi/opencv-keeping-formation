#!/bin/sh

base="`basename $1 .cpp`"
g++ -ggdb `pkg-config opencv --cflags --libs` $base.cpp -o $base
