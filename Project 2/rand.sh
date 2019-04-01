#! /bin/bash

grep -E "<td>.+</td>" |
sed "1~2d" |
sed "s/<[^>]*>//g" |
tr [:upper:] [:lower:] |
tr "\`" "\'"  |
sed -E "s/,\s|\s/\n/g" |
#sed "s/[^pkmnwlhaeiou \']//g" |
grep "^[pk\' mnwlhaeiou]\{1,\}$" |
#tr -cs "a-z'" "[\n*]" |
sort -u |
#tr "#" "\'"
sed '/ ^$/d'