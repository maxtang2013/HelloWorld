#!/bin/bash

while getopts xf:o: opt
do
    case $opt in
        x) echo Found option -x;;
        f) echo Found option -f with value $OPTARG;;
        o) echo Found option -o with value $OPTARG;;  
        *) echo Unknow option $opt;;
    esac
done

shift $[ $OPTIND - 1 ]

for param in $@; do
    echo Parameter $param
done

