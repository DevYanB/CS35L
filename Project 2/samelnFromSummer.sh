#!/bin/bash

#find the directory's files with .* * for inclusivity of hidden files
cd "$1"

for file1 in .* *
do
    for file2 in .* *
    do

        #Checks if two files are the same name - if so continue
        if [ "$file1" == "$file2" ]; then
        continue
        fi

        #Checks if the file1 or file2 is NOT a file, then continue
        if [[ ! ( -f "$file1") || ! ( -f "$file2" ) ]]; then
        continue
        fi

        cmp -s "$file1" "$file2"
        if [ $? -eq 0 ] ; then
                if [[ ${file1:0:1} == '.'  && ${file2:0:1} != '.' ]] ; then
                rm "$file2"
                ln "$file1" "$file2"
                elif [[ ${file1:0:1} != '.'  && ${file2:0:1} == '.' ]] ; then
                rm "$file1"
                ln "$file2" "$file1"
            elif [[ "$file1" > "$file2" ]] ; then
            rm "$file1"
            ln "$file2" "$file1"
            else
            rm "$file2"
            ln "$file1" "$file2"
            fi
        fi
    done
done





#! /bin/bash
grep -E "<td>.+</td>" #|
#sed -n '2~2p' |
#sed "s/<[^>]*>//g" |
#tr [:upper:] [:lower:] |
#tr "\`" "\'" |
#sed -E "s/[ \t]*//g" |
#sed -E "s/,\s|\s/\n/g" |
#grep "^[pk\' mnwlhaeiou]\{1,\}$" |
#sort -u
