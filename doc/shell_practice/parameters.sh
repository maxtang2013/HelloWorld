#!/bin/bash

if [ $# -ge 1 ]; then
    echo \$1 is $1
fi

if [ $# -ge 2 ]; then
    echo \$2 is $2
    echo Total is $[ $1*$2 ]
fi

for p in $*
do
    echo $p
done


set -- `getopt af: "$@"`
process_all=0
while [ -n $1 ]; do
    case $1 in
        -a) echo Found option -a
            process_all=1
            ;;
        -f) echo Found option -f
            if [ $# -lt 2 ]; then
                echo Usage: parameters \[-a\] \[-f file\]
            else
                echo "\t with parameter $2"
            fi
            shift;;
        --)
            shift
            break;;
        *)  echo Unkown option $1
    esac
    shift
done



