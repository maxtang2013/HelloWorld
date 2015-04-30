#!/bin/bash

if ./test.sh ; then
    echo OK
else
    echo Bad!
fi

user="compilers"
if [ $USER = $user ]; then 
    echo Welcome, $user.
fi

if [ -z "" ]; then
    echo Yes.
fi

if [ -z $user ]; then
    echo Id user is empty
fi

if [ -z $hello]; then
    echo undefined identity [hello]
fi

if (( 1 + 2 )) ; then
    echo ===============
fi

date
if [  $? ]; then
    echo $?
fi

if [ 0 ]; then
    echo zero is OK
fi

cp x y

if [ $? -eq 0 ]; then
    echo cp done successfull
else
    echo cp exit code: $?
fi

hello=hell
if [[ $hello = he* ]]; then
    echo "he* matches hell"
fi

if [[ $hello = h.* ]]; then
    ehco "h.* matches hell"
fi

name="max"

echo Could you please tell me your name:
read name

case $name in
    max)
        echo Welcome;;
    tony)
        echo Long time no see;;
    linda)
        echo Hi, darling;;
    *)
        echo who are you?;;
esac


