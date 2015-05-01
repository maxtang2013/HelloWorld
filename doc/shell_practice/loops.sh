list_var=("x" "y" "z")
echo ${list_var[*]}
for x in ${list_var[*]}
do
    echo $x
done

places="Tianjin Beijing Wuhan Shanghai Shenzhen"
for place in $places
do
    echo "I'v been to $place"
done


IFS=$'\n'
for food in `cat filelist`
do
    echo "I like to eat $food"
done


for f in ./*
do
    if [ -d  "$f" ]; then
        echo $f is a directory
    elif [ -f "$f" ]; then
        echo $f is a file
    fi
done

index=10
while [ $index -ge 0 ]
do
    echo Index is $index
    
    index=$[$index-1]
    
    # weird sytle.
    (( index=$index-1 ))

    (( ++index ))
done

number2=4
number=6
if [ $number -gt $number2 ]; then
    echo $number is greater then 4 
fi

if (( $number > 4 )); then
    echo "(( \$number > 4 )) stands"
fi


